def auth(server_socket, name, passwd, size):
    print ('\033[92m\033[1m########### authentication test ###########\033[0m') # AUTH
    print ('name:', name, 'password:', passwd)

    server_socket.recv(size)
    cmd = 'USER ' + name + '\r\n'
    server_socket.send(cmd.encode())

    server_socket.recv(size)
    cmd = 'PASS ' + passwd + '\r\n'
    server_socket.send(cmd.encode())

    resp = server_socket.recv(size).decode()
    print (name, '[', resp[0:-2], ']')
    if not resp:
        resp = ' '

    return resp[0] == '2'