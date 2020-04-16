import random
import re
import socket

def port(controlSocket, clientAddress, size):
	clientPort = random.randint(10000, 20000)

	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.bind( (clientAddress, clientPort))
	s.listen(1)

	command = "PORT " + clientAddress.replace('.',',') + ',' + str(clientPort/256) + ',' + str(clientPort%256)
	controlSocket.send(command + '\r\n')
	print (controlSocket.recv(size))
	return s


def pasv(controlSocket, size):
	controlSocket.send('PASV' + '\r\n')
	data = controlSocket.recv(size)
	print (data)
	pattern = '([0-9 ]+),([0-9 ]+),([0-9 ]+),([0-9 ]+),([0-9 ]+),([0-9 ]+)'
	match = re.findall(pattern, data)
	if match:
		match = match[0]
		ipString = match[0] + '.' + match[1] + '.' + match[2] + '.' + match[3]
		port = int(match[4]) * 256 + int(match[5])
		print ('remote:', ipString, port)
		s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		s.connect( (ipString, port))
		return s
	else:
		print ('PASV Fail!!')