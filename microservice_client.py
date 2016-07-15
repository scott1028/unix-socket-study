import socket
import sys

# Create a UDS socket
sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)

# Connect the socket to the port where the server is listening
server_address = './communicate.sock'
print >>sys.stderr, 'connecting to %s' % server_address
try:
    sock.connect(server_address)
    sock.send('1' * 1025)
    # import pdb; pdb.set_trace()
    sock.send('DONE')  # for server detect

    # This will not work, you can not use sock.send(''), you should use sock.close() to send empty data.
    # sock.send('')    
    # import pdb; pdb.set_trace()

    # This will send a '' length = 0 data to server
    sock.close()
except socket.error, msg:
    print >>sys.stderr, msg
    sys.exit(1)

