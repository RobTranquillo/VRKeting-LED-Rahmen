
# Complete project details at https://RandomNerdTutorials.com
try:
  import usocket as socket
except:
  import socket
  
from machine import Pin
led = Pin(2, Pin.OUT)

def web_page():
  text_file = open("html/index.html", "r")
  index_html = text_file.read()
  text_file.close()
  return index_html

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('', 80))
s.listen(5)

while True:
  conn, addr = s.accept()
  print('Got a connection from %s' % str(addr))
  request = conn.recv(1024)
  request = str(request)
  #Print full Request Header
  #print('Content = %s' % request)

  #get Paramters from GET request
  #led_on = request.find('/?led=on')
  #über GET die Routen bauen
  
  response = web_page()
  conn.send('HTTP/1.1 200 OK\n')
  conn.send('Content-Type: text/html\n')
  conn.send('Connection: close\n\n')
  conn.sendall(response)
  conn.close()

