def delete_file(server_socket, size):
    print ('\033[92m\033[1m########### delete files ###########\033[0m') # DELETE FILE
    delete_flag = True

    cmd = 'DELE to_rm\r\n'
    print ('try: \"DELE to_rm\"')
    server_socket.send(cmd.encode())
    data = server_socket.recv(size).decode()
    print (data[0:-2])
    if data[0] != '2':
        delete_flag = False
        print ('Failed')
    else:
        print ('Delete Success')
    
    cmd = 'DELE idontexist\r\n'
    print ('try: \"DELE idontexist\"')
    server_socket.send(cmd.encode())
    data = server_socket.recv(size).decode()
    print (data[0:-2])
    if data[0] == '2':
        delete_flag = False
        print ('Succes (unexpected)')
    else:
        print ('Failed (expected)')

    cmd = 'DELE /tests/server_files/to_rm2\r\n'
    print ('try: \"DELE /tests/server_files/to_rm2\"')
    server_socket.send(cmd.encode())
    data = server_socket.recv(size).decode()
    print (data[0:-2])
    if data[0] != '2':
        delete_flag = False
        print ('Failed')
    else:
        print ('Delete Success')

    return delete_flag