import RFM69

FREQUENCY = 43  # 433MHz
NODEID = 1
NETWORKID = 100
TXPOWER = 31  # Max Power
CRYPTPASS = "0123456789012345"

RFM69.initialize(FREQUENCY, NODEID, NETWORKID)
RFM69.encrypt(CRYPTPASS)
RFM69.setPowerLevel(TXPOWER) 

while True:
    RFM69.receive()
    datalen = RFM69.getDataLen()

    if datalen:
        senderId = RFM69.getSenderId()
        rssi = RFM69.getRssi()
        data = RFM69.getData()
        print "DATA RECEIVED\n- RSSI: %s\nSender: %s\nData: '%s'\n\n\n" % (rssi, senderId, data)
