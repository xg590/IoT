import network, socket, ussl  

ip, port = 'abc.xyz', 12345   
ssid     = 'xxx'
passwd   = 'xxx'  
key      = '''-----BEGIN PRIVATE KEY-----
MIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQCume13Aoi0OUy8
oH4QfaT6EVFmIgNB/p2NIBin
-----END PRIVATE KEY-----'''
cert     = '''-----BEGIN CERTIFICATE-----
MIIDAzCCAeugAwIBAgIUJIlBvZtHZCk5VyO5S1UIGHtCk68wDQYJKoZIhvcNAQEL
5SxpsCsenQ==
-----END CERTIFICATE-----''' 

sta_if = network.WLAN(network.STA_IF) 
sta_if.active(True) 
sta_if.connect(ssid, passwd)
while not sta_if.isconnected():
    pass 

s = socket.socket()
s.connect((ip, port))  
ss = ussl.wrap_socket(s, server_side=False, server_hostname=ip, key=key.encode(), cert=cert.encode()) 
ss.write(b'1')   
