InvokedByNFC
============

It's easy to get invoked by NFC if there's some data on the Tag.
Then you can use the InvokationFramework as usual

One of my customers doesn't want to rely on Text written on a Tag,
because Tags will be placed at public places and so it would be easy
to overwrite them from any NFC-enabled smartphone.

Every NFC Tag has an own ID (ISO 14443)
So using this ID would be safe. The needed data comes from a server where the mapping was done between ID and data objects.

I tried to find an easy way to get the ID.
NFC Tool is able to read this kind of information from a Tag and I tried to scan the code,
but was lost in complexity.

Thanks to John Murray who helped me much pointing to the right places in src from NFCTool
and also NfcRaceTimeWay. Without his recipes it would have taken much longer to find a way to get the ID from the Tags.

ATTENTION !!!!  App is work-in-progress ... not ready-to-go yet ... stay tuned
