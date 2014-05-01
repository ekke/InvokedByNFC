

#ifndef NFCID_HPP_
#define NFCID_HPP_

#define CHECK(rc) NfcId::checkReturnCode((rc), __LINE__, __FILE__, __PRETTY_FUNCTION__)

#include <qobject.h>
#include <bps/bps.h>
#include <nfc/nfc.h>

#include <bb/core/AbstractBpsEventHandler.hpp>
#include <bps/navigator.h>
#include <bps/navigator_invoke.h>

class NfcId: public QObject, public bb::AbstractBpsEventHandler {
	Q_OBJECT

public:
	NfcId(QObject *parent = 0);

	virtual ~NfcId();

public slots:
	void startListening();
	void stopListening();

	signals:
	void touchedId(QString tagId);

private:
	static void checkReturnCode(int rc, int line, const char *file,
			const char *func);
	bool mFailedToInitialize;
	void initialize();
	void event(bps_event_t *event);
	void handleNfcEvent(bps_event_t *event);
	void terminate();
};

#endif /* NFCID_HPP_ */
