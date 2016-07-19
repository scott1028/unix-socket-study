import socket
import sys

# Create a TCP/IP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the socket to the address given on the command line
server_address = ('0.0.0.0', 3333)
sock.bind(server_address)
sock.listen(0)
print >>sys.stderr, 'starting up on %s port %s' % sock.getsockname()

while True:
    print >>sys.stderr, 'waiting for a connection'
    connection, client_address = sock.accept()
    client_host, client_port = connection.getpeername()
    try:
        print >>sys.stderr, 'client connected:', client_address
        while True:
            data = connection.recv(16)
            data += "%s, %s\n" % (str(client_host), str(client_port))
            print >>sys.stderr, 'received "%s"' % data
            if data:
                connection.sendall(data)
            else:
                break
    finally:
        connection.close()
