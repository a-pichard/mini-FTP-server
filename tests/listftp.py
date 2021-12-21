from transfer_modes import pasv, port
import time

def listftp(server_socket, clientAddress, size):
	print ('\n\033[92m\033[1m########### active mode LIST ###########\033[0m') # ACTIVE LIST
	listFlag = True

	s = port(server_socket, clientAddress, size)
	time.sleep(1)

	cmd = 'LIST\r\n'
	server_socket.send(cmd.encode())
	try:
		connect, _ = s.accept()

		time.sleep(1)
		resp = connect.recv(size).decode()

		print ('LIST format:')
		print ('------------------------------------')
		print (resp)
		print ('------------------------------------')

		resp = connect.recv(size).decode()
		print (resp)

		connect.close()
	except:
		print ('Fail!!')
		listFlag = False
	s.close()

	return listFlag