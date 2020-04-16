def delete_file(server_socket, size):
    print ('\033[92m\033[1m########### delete files ###########\033[0m') # DELETE FILE
    deleteFlag = True
    server_socket.send('DELE to_rm\r\n')
    print ('try: delete \'to_rm\'')
    data = server_socket.recv(size)
    print (data[0:-2])
    if data[0] != '2':
    	deleteFlag = False
    	print ('Failed')
    else:
    	print ('Delete Success')
    server_socket.send('DELE idontexist\r\n')
    print ('try: delete idontexist')
    data = server_socket.recv(size)
    print (data[0:-2])
    if data[0] == '2':
    	deleteFlag = False
    	print ('Succes (unexpected)')
    else:
    	print ('Failed (expected)')
    server_socket.send('DELE /tests/server_files/to_rm2\r\n')
    print ('try: delete /tests/server_files/to_rm2')
    data = server_socket.recv(size)
    print (data[0:-2])
    if data[0] != '2':
    	deleteFlag = False
    	print ('Failed')
    else:
    	print ('Delete Success')
    return deleteFlag