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

    # Block util recv buffer = 1024 or recv EOF byte
    # conn.recv 最大區塊為 1024 bytes 超過部份會被切成兩次 recv 接收!
    data = conn.recv(1024)

    if not data:
        # client send data EOF, so break.
        print 'client data recv EOF'
        break
    else:
        print "-" * 20
        print data
        # 單獨一個 Datagram 恰好等於 = DONE 就會結束回圈
        print "DONE" == data
        if "DONE" == data:
            # Detect "DONE" Keywork for END Client
            break
print "-" * 20
print "Shutting down..."

server.close()
os.remove( sockfile )

print "Done"
