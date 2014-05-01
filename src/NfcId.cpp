#include "NfcId.hpp"

#include <QObject>
#include <QDebug.h>

#include <bps/bps.h>
#include <nfc/nfc_bps.h>

// this class will be instantiated from applicationui.cpp
NfcId::NfcId(QObject *parent) :
		QObject(parent), mFailedToInitialize(false) {
}

// SLOT
// gets signal from applicationui.cpp
void NfcId::startListening() {
	initialize();
}

// clean it all
// called from ~NfcId()
void NfcId::stopListening() {
	terminate();
}

// Setup Event handler
// any NFC event will be detected and processed by
// event(bps_event_t *event)
void NfcId::initialize() {
	qDebug() << "N F C    NfcId::initialize() starts...";

	int rc = bps_initialize();
	if (rc) {
		mFailedToInitialize = true;
		qDebug() << "N F C   Error: BPS failed to initialise. rc=" << rc;
	}

	rc = nfc_request_events();
	if (rc) {
		mFailedToInitialize = true;
		qDebug() << "N F C   Error: Failed to request NFC BPS events. rc=" << rc;
		bps_shutdown();
	} else {
		qDebug() << "N F C   Registered for NFC BPS events OK";
		subscribe(nfc_get_domain());
	}
	qDebug() << "N F C   NfcId::initialize() ends...";
}

// clean up code
void NfcId::terminate() {
	qDebug() << "N F C   NfcId::terminate entered ...";
	nfc_stop_events();
	unsubscribe(nfc_get_domain());
	bps_shutdown();
}

// check if the event is really a NFC Event
// if all is OK handle the event from
// :handleNfcEvent(bps_event_t *event)
void NfcId::event(bps_event_t *event) {
	qDebug() << "N F C   E V E N T NfcId::event() entered ...";

	int domain = bps_event_get_domain(event);
	if (nfc_get_domain() == domain) {
		handleNfcEvent(event);
	}
}

// we received a NFC Event
// we're only interested into NFC_TAG_READWRITE_EVENT
// this event means an NFC Tag has been presented to the mobile
// we're only interested into the ID and emit touchedId(id)
void NfcId::handleNfcEvent(bps_event_t *event) {
	uint16_t code = bps_event_get_code(event);

	qDebug() << "N F C   NfcId::handleNfcEvent - code: " << code;

	nfc_event_t *nfcEvent;
	nfc_target_t* target;
	nfc_result_t rc;
	uchar_t id[20];
	size_t idLength = 0;

	if (NFC_TAG_READWRITE_EVENT == code) {
		qDebug() << "N F C NfcId::handle - NFC_TAG_READWRITE_EVENT";

		CHECK(nfc_get_nfc_event(event, &nfcEvent));
		CHECK(nfc_get_target(nfcEvent, &target));

		rc = nfc_get_tag_id(target, &id[0], sizeof id, &idLength);
		if (rc == NFC_RESULT_SUCCESS) {
			QByteArray uId = QByteArray::fromRawData(
					reinterpret_cast<const char *>(&id[0]), idLength);
			qDebug() << "N F C   Tag id" << uId.toHex() << endl;
			emit touchedId(QString::fromAscii(uId.toHex()));
		} else {
			qDebug() << "N F C   nfc_get_tag_id() returned" << rc << endl;
		}
	}

	// don't forget to delete the target
	nfc_destroy_target(target);

	qDebug() << "N F C  NfcId::handleNfcEvent done";
}

void NfcId::checkReturnCode(int rc, int line, const char *file,
		const char *func) {
	if (rc != BPS_SUCCESS) {
		qDebug() << "N F C   NfcID Error code " << rc << " in function " << func
				<< " on line " << line << " in " << file;
	}
}

// will be executed if app shuts down
// parent is applicationui.cpp
NfcId::~NfcId() {
	// shut down event loop
	qDebug() << "N F C   NfcId:: SHUT DOWN";
	stopListening();
}

