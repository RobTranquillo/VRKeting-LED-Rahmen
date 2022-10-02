try:
  import usocket as socket
except:
  import socket

import network, time

ssid = "22"
password = "frankreich"
dhcp_hostname = "leuchte"

print("...") ##force newline after binary output

station = network.WLAN(network.STA_IF)
station.config(dhcp_hostname=dhcp_hostname)

station.active(True)
station.connect(ssid, password)

while station.isconnected() == False:
    print("Wifi connection: False (check credentials)")
    time.sleep(2)
    pass

print('Connection successful')
print(station.ifconfig())
