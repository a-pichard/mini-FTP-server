from transfer_modes import port, pasv
import time

def active_upload(server_socket, client_home, clientAddress, size):
    print ('\033[92m\033[1m########### active mode STOR ###########\033[0m') # ACTIVE UPLOAD
    activeStoreFlag = True

    print ('upload client_file.txt as from_client.txt')

    s = port(server_socket, clientAddress, size)
    time.sleep(1)

    cmd = 'STOR from_client.txt\r\n'
    server_socket.send(cmd.encode())
    resp = server_socket.recv(size).decode()
    print (resp)
    try:
        connect, _ = s.accept()
        testFile = open(client_home + '/client_file.txt')
        while True:
            data = testFile.read(size)
            if(data):
                connect.send(data.encode())
            else:
                break

        testFile.close()
        connect.close()

        resp = server_socket.recv(size).decode()
        print (resp)
    except:
        print ('Fail!!')
        activeStoreFlag = False
    s.close()

    return activeStoreFlag
		
def active_download(server_socket, client_home, clientAddress, size):
    print ('\n\033[92m\033[1m########### active mode RETR ###########\033[0m') # ACTIVE DOWNLOAD
    activeRetrieveFlag = True

    print ('download server_file.txt as from_server.txt')

    s = port(server_socket, clientAddress, size)
    time.sleep(1)

    cmd = 'RETR server_file.txt\r\n'
    server_socket.send(cmd.encode())
    resp = server_socket.recv(size).decode()
    print (resp)
    try:
        connect, _ = s.accept()
        testFile = open(client_home + '/from_server.txt', 'wb')
        while True:
            data = connect.recv(size)
            if(data):
                testFile.write(data)
            else:
                break
        
        resp = server_socket.recv(size).decode()
        print (resp)

        testFile.close()
        connect.close()
    except:
        print ('Fail!!')
        activeRetrieveFlag = False
    s.close()

    return activeRetrieveFlag

def passive_upload(server_socket, client_home, size):
    print ('\033[92m\033[1m########### passive mode STOR ###########\033[0m') # PASSIVE UPLOAD
    passiveStoreFlag = True

    print ('upload client_file1.pdf as from_client1.pdf')

    try:
        s = pasv(server_socket, size)
        time.sleep(1)
    
        cmd = 'STOR from_client1.pdf\r\n'
        server_socket.send(cmd.encode())

        resp = server_socket.recv(size).decode()
        print (resp)

        testFile = open(client_home + 'client_file1.pdf', 'rb')

        while True:
            data = testFile.read(size)
            if(data):
                s.send(data)
            else:
                break
        
        testFile.close()
        s.close()

        resp = server_socket.recv(size).decode()
        print (resp)
    except:
        print ('Fail!!')
        passiveStoreFlag = False

    return passiveStoreFlag

def passive_download(server_socket, client_home, size):
    print ('\033[92m\033[1m########### passive mode RETR ###########\033[0m') # PASSIVE DOWNLOAD
    passiveRetrieveFlag = True
    
    print ('download server_file1.pdf as from_server1.pdf')
    
    try:
        s = pasv(server_socket, size)
        time.sleep(1)

        cmd = 'RETR server_file1.pdf' + '\r\n'
        server_socket.send(cmd.encode())

        resp = server_socket.recv(size).decode()
        print (resp)

        testFile = open(client_home + 'from_server1.pdf', 'wb')

        while True:
            data = s.recv(size)
            if(data):
                testFile.write(data)
            else:
                break

        resp = server_socket.recv(size).decode()
        print (resp)

        testFile.close()
        s.close()
    except:
        print ('Fail!!')
        passiveRetrieveFlag = False

    return passiveRetrieveFlag