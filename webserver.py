
# Complete project details at https://RandomNerdTutorials.com
try:
  import usocket as socket
except:
  import socket

def web_page():
  text_file = open("html/index.html", "r")
  index_html = text_file.read()
  text_file.close()
  return index_html

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('', 80))
s.listen(5)

def handleWebRequest():
  conn, addr = s.accept()
  print('Got a connection from %s' % str(addr))
  request = conn.recv(1024)
  request = str(request)
  #Print full Request Header
  #print('Content = %s' % request)

  #get paramters from GET request
  beginGETParams = request.find('/?led=')+6
  lenghtGETParams = request.find(' ', beginGETParams)
  program = str(request[beginGETParams:lenghtGETParams])
  
  response = web_page()
  conn.send('HTTP/1.1 200 OK\n')
  conn.send('Content-Type: text/html\n')
  conn.send('Connection: close\n\n')
  conn.sendall(response)
  conn.close()
  return program

