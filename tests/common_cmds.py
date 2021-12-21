def common_cmds(server_socket, size):
    print ('\n\033[92m\033[1m########### pwd, cwd, cdup ###########\033[0m') # COMMON COMMANDS

    print (f'try: \"PWD\"')
    cmd = 'PWD' + '\r\n'
    server_socket.send(cmd.encode())
    resp = server_socket.recv(size).decode()
    print (resp[0:-2])

    print (f'try: \"CWD\"')
    cmd = 'CWD ' + 'tests/server_files' + '\r\n'
    server_socket.send(cmd.encode())
    resp = server_socket.recv(size).decode()
    print (resp[0:-2])

    cmd = 'CDUP' + '\r\n'
    print (f'try: \"CDUP\"')
    server_socket.send(cmd.encode())
    resp = server_socket.recv(size).decode()
    print (resp[0:-2])

    cmd = 'CWD ' + 'server_files' + '\r\n'
    print (f'try: \"CWD\"')
    server_socket.send(cmd.encode())
    resp = server_socket.recv(size).decode()
    print (resp[0:-2])

    print (f'try: \"PWD\"')
    cmd = 'PWD' + '\r\n'
    server_socket.send(cmd.encode())
    resp = server_socket.recv(size).decode()
    print (resp[0:-2])