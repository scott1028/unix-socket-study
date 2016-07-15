# coding: utf-8

import socket
import os, os.path
import time

sockfile = "./communicate.sock"

if os.path.exists( sockfile ):
  os.remove( sockfile )

print "Opening socket..."

server = socket.socket( socket.AF_UNIX, socket.SOCK_STREAM )
server.bind(sockfile)
server.listen(5)

print "Listening..."
while True:
  conn, addr = server.accept()

  print 'accepted connection'

  while True: 

    data = conn.recv(1024)

    if not data:
        # client send data EOF, so break.
        break
    else:
        print "-" * 20
        print data
        print "DONE" == data
        if "DONE" == data:
            break
print "-" * 20
print "Shutting down..."

server.close()
os.remove( sockfile )

print "Done"
