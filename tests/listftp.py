from transfer_modes import pasv, port
import time

def listftp(server_socket, clientAddress, size):
    print ('\n\033[92m\033[1m########### active mode LIST ###########\033[0m') # ACTIVE LIST
    listFlag = True
    s = port(server_socket, clientAddress, size)
    time.sleep(1)	
    server_socket.send('LIST\r\n')
    try:
    	connect, _ = s.accept()
    	time.sleep(1)
    	data = connect.recv(size)
    	print ('LIST format:')
    	print ('------------------------------------')
    	print (data)
    	print ('------------------------------------')
    	print (server_socket.recv(size))
    	connect.close()
    except:
    	print ('Fail!!')
    	listFlag = False
    s.close()
    return listFlag