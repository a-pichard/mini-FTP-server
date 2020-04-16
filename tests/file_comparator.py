def file_comparator(client_home, server_home):
	print ('\033[92m\033[1m########### files compare ###########\033[0m') # CHECK FILES
	fileCompareFlag = True
	try:
		client_file = file(client_home + 'client_file.txt').readlines()
		client_file1 = file(client_home + 'client_file1.pdf').readlines()
		server_file = file(server_home + 'server_file.txt').readlines()
		server_file1 = file(server_home + 'server_file1.pdf').readlines()
		res_client_file = file(server_home + 'from_client.txt').readlines()
		res_client_file1 = file(server_home + 'from_client1.pdf').readlines()
		res_server_file = file(client_home + 'from_server.txt').readlines()
		res_server_file1 = file(client_home + 'from_server1.pdf').readlines()
		if (client_file == res_client_file):
			print ('client_file.txt transfer success')
		else:
			print ('client_file.txt transfer failed')
			fileCompareFlag = False

		if (client_file1 == res_client_file1):
			print ('client_file1.pdf transfer success')
		else:
			print ('client_file1.pdf transfer failed')
			fileCompareFlag = False

		if (server_file == res_server_file):
			print ('server_file.txt transfer success')
		else:
			print ('server_file.txt transfer failed')
			fileCompareFlag = False

		if (server_file1 == res_server_file1):
			print ('server_file1.pdf transfer success')
		else:
			print ('server_file1.pdf transfer failed')
			fileCompareFlag = False
	except:
		print ('A file cant be opened.')
		fileCompareFlag = False
	return fileCompareFlag