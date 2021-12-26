def file_comparator(client_home, server_home):
	print ('\033[92m\033[1m########### files compare ###########\033[0m') # CHECK FILES
	fileCompare_flag = True

	try:
		client = get_file_content(client_home + 'client_file.txt')
		client1 = get_file_content(client_home + 'client_file1.pdf')
		server = get_file_content(server_home + 'server_file.txt')
		server1 = get_file_content(server_home + 'server_file1.pdf')
		res_client = get_file_content(server_home + 'from_client.txt')
		res_client1 = get_file_content(server_home + 'from_client1.pdf')
		res_server = get_file_content(client_home + 'from_server.txt')
		res_server1 = get_file_content(client_home + 'from_server1.pdf')

		if (client == res_client):
			print ('client_file.txt transfer success')
		else:
			print ('client_file.txt transfer failed')
			fileCompare_flag = False

		if (client1 == res_client1):
			print ('client_file1.pdf transfer success')
		else:
			print ('client_file1.pdf transfer failed')
			fileCompare_flag = False

		if (server == res_server):
			print ('server_file.txt transfer success')
		else:
			print ('server_file.txt transfer failed')
			fileCompare_flag = False

		if (server1 == res_server1):
			print ('server_file1.pdf transfer success')
		else:
			print ('server_file1.pdf transfer failed')
			fileCompare_flag = False

	except:
		print ('A file cant be opened.')
		fileCompare_flag = False

	return fileCompare_flag

def get_file_content(filepath):
	file = open(filepath, 'rb')
	content = file.read()
	file.close()

	return content