def common_cmds(server_socket, size):
    print ('\n\033[92m\033[1m########### pwd, cwd, cdup ###########\033[0m') # COMMON COMMANDS

    server_socket.send('PWD' + '\r\n')
    print ('try: pwd')
    print (server_socket.recv(size)[0:-2])

    server_socket.send('CWD ' + 'tests/server_files' + '\r\n')
    print ('try: cd ', 'tests/server_files')
    print (server_socket.recv(size)[0:-2])

    server_socket.send('CDUP' + '\r\n')
    print ('try: cdup')
    print (server_socket.recv(size)[0:-2])

    server_socket.send('CWD ' + 'server_files' + '\r\n')
    print ('try: cd ', 'server_files')
    print (server_socket.recv(size)[0:-2])

    server_socket.send('PWD' + '\r\n')
    print ('try: pwd')
    print (server_socket.recv(size)[0:-2])