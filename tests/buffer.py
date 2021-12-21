def buffer(server_socket, size):
    print ('\033[92m\033[1m########### Buffer ###########\033[0m') # Buffer
    bufferFlag = True

    server_socket.send(('P').encode())
    server_socket.send(('WD').encode())
    server_socket.send(('\r\n').encode())
    print ('try: PWD')

    data = server_socket.recv(size).decode()

    print (data[0:-2])
    if data[0] != '2':
        bufferFlag = False
        print ('Failed')
    else:
        print ('Buffer ok')

    return bufferFlag