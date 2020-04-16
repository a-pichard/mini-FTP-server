def auth(server_socket, name, passwd, size):
    print ('\033[92m\033[1m########### authentication test ###########\033[0m') # AUTH
    print ('name:', name, 'password:', passwd)

    server_socket.recv(size)
    server_socket.send('USER ' + name + '\r\n')
    server_socket.recv(size)
    server_socket.send('PASS ' + passwd + '\r\n')
    data = server_socket.recv(size)
    print (name, '[', data[0:-2], ']')
    if not data:
    	data = ' '
    return data[0] == '2'