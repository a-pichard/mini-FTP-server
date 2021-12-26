def buffer(server_socket, size):
    print ('\033[92m\033[1m########### Buffer ###########\033[0m') # Buffer
    buffer_flag = True

    server_socket.send(('P').encode())
    server_socket.send(('WD').encode())
    server_socket.send(('\r\n').encode())
    print ('try: PWD')

    data = server_socket.recv(size).decode()

    print (data[0:-2])
    if data[0] != '2':
        buffer_flag = False
        print ('Failed')
    else:
        print ('Buffer ok')

    return buffer_flag