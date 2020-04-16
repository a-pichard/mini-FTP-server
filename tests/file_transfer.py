from transfer_modes import port, pasv
import time

def active_upload(server_socket, client_home, clientAddress, size):
    print ('\033[92m\033[1m########### active mode STOR ###########\033[0m') # ACTIVE UPLOAD
    print ('upload client_file.txt as from_client.txt')
    activeStoreFlag = True
    s = port(server_socket, clientAddress, size)
    time.sleep(1)
    server_socket.send('STOR from_client.txt' + '\r\n')
    print (server_socket.recv(size))
    try:
    	connect, _ = s.accept()
    	testFile = file(client_home + '/client_file.txt')
    	while True:
    		data = testFile.read(size)
    		if(data):
    			connect.send(data)
    		else:
    			break
    	testFile.close()
    	connect.close()
    	print (server_socket.recv(size))
    except:
    	print ('Fail!!')
    	activeStoreFlag = False
    s.close()
    return activeStoreFlag
		
def active_download(server_socket, client_home, clientAddress, size):
    print ('\n\033[92m\033[1m########### active mode RETR ###########\033[0m') # ACTIVE DOWNLOAD
    print ('download server_file.txt as from_server.txt')
    activeRetrieveFlag = True
    s = port(server_socket, clientAddress, size)
    time.sleep(1)
    server_socket.send('RETR server_file.txt' + '\r\n')
    print (server_socket.recv(size))
    try:
        connect, _ = s.accept()
        testFile = open(client_home + '/from_server.txt', 'w')
        while True:
            data = connect.recv(size)
            if(data):
                testFile.write(data)
            else:
                break
        print (server_socket.recv(size))
        testFile.close()
        connect.close()
    except:
        print ('Fail!!')
        activeRetrieveFlag = False
    s.close()
    return activeRetrieveFlag

def passive_upload(server_socket, client_home, size):
    print ('\033[92m\033[1m########### passive mode STOR ###########\033[0m') # PASSIVE UPLOAD
    print ('upload client_file1.pdf as from_client1.pdf')
    passiveStoreFlag = True
    try:
    	s = pasv(server_socket, size)
    	time.sleep(1)
    	server_socket.send('STOR from_client1.pdf' + '\r\n')
    	print (server_socket.recv(size))
    	testFile = file(client_home + 'client_file1.pdf')
    	while True:
    		data = testFile.read(size)
    		if(data):
    			s.send(data)
    		else:
    			break
    	testFile.close()
    	s.close()
    	print (server_socket.recv(size))
    except:
    	print ('Fail!!')
    	passiveStoreFlag = False
    return passiveStoreFlag

def passive_download(server_socket, client_home, size):
    print ('\033[92m\033[1m########### passive mode RETR ###########\033[0m') # PASSIVE DOWNLOAD
    print ('download server_file1.pdf as from_server1.pdf')
    passiveRetrieveFlag = True
    try:
        s = pasv(server_socket, size)
        time.sleep(1)
        server_socket.send('RETR server_file1.pdf' + '\r\n')
        print (server_socket.recv(size))
        testFile = open(client_home + 'from_server1.pdf', 'w')
        while True:
            data = s.recv(size)
            if(data):
                testFile.write(data)
            else:
                break
        print (server_socket.recv(size))
        testFile.close()
        s.close()
    except:
    	print ('Fail!!')
    	passiveRetrieveFlag = False
    return passiveRetrieveFlag