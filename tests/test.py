#!/usr/bin/python
# -*- coding: utf-8 -*-

import socket
import time
import random
import os
import re

########################################

clientAddress = '127.0.0.1'
serverAddress = '127.0.0.1'
serverPort = 6969
name = 'Anonymous'
passwd = ''

client_home = "tests/client_files/"
server_home = "tests/server_files/"

size = 2 ** 11
socket.setdefaulttimeout(10)

########################################

def port(controlSocket):
	clientPort = random.randint(10000, 20000)

	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.bind( (clientAddress, clientPort))
	s.listen(1)

	command = "PORT " + clientAddress.replace('.',',') + ',' + str(clientPort/256) + ',' + str(clientPort%256)
	controlSocket.send(command + '\r\n')
	print (controlSocket.recv(size))
	return s


def pasv(controlSocket):
	controlSocket.send('PASV' + '\r\n')
	data = controlSocket.recv(size)
	print (data)
	pattern = '([0-9 ]+),([0-9 ]+),([0-9 ]+),([0-9 ]+),([0-9 ]+),([0-9 ]+)'
	match = re.findall(pattern, data)
	if match:
		match = match[0]
		ipString = match[0] + '.' + match[1] + '.' + match[2] + '.' + match[3]
		port = int(match[4]) * 256 + int(match[5])
		print ('remote:', ipString, port)
		s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		s.connect( (ipString, port))
		return s
	else:
		print ('PASV Fail!!')

def summary(title, flag):
	print ('%-25s %s' % (title, 'OK' if flag else 'Fail')	)


if __name__ == '__main__' :
	server_socket = {}

	print ('\033[92m\033[1m########### authentication test ###########\033[0m') # AUTH
	print ('name:', name, 'password:', passwd)

	try:
		server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		server_socket.connect( (serverAddress, serverPort) )
		print ('using socket', server_socket.getsockname())
	except:
		print ("can't connect to server, double check address and port")

	print ('------------------------------------')

	authenticationFlag = True
	server_socket.recv(size)
	server_socket.send('USER ' + name + '\r\n')
	server_socket.recv(size)
	server_socket.send('PASS ' + passwd + '\r\n')
	data = server_socket.recv(size)
	print (name, '[', data[0:-2], ']')
	
	if not data:
		data = ' '
	if data[0] != '2' and name != 'doesnotexist':
		authenticationFlag = False
	if data[0] == '2' and name == 'doesnotexist':
		authenticationFlag = False

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


	print ('\n\033[92m\033[1m########### active mode LIST ###########\033[0m') # ACTIVE LIST
	listFlag = True
	s = port(server_socket)
	time.sleep(1)	
	server_socket.send('LIST\r\n')
	try:
		connect, address = s.accept()
		time.sleep(1)
		data = connect.recv(size)
		print ('LIST format:')
		print ('------------------------------------')
		print (data)
		print ('------------------------------------')
		print (server_socket.recv(size))
		connect.close()
	except:
		print ('Fail!!')
		listFlag = False
	s.close()

	print ('\033[92m\033[1m########### active mode STOR ###########\033[0m') # ACTIVE UPLOAD
	print ('upload client_file.txt as from_client.txt')
	activeStoreFlag = True
	s = port(server_socket)
	time.sleep(1)
	server_socket.send('STOR from_client.txt' + '\r\n')
	try:
		connect, address = s.accept()
		testFile = file(client_home + '/client_file.txt')
		while True:
			data = testFile.read(size)
			if(data):
				connect.send(data)
			else:
				break
		print (server_socket.recv(size))
		testFile.close()
		connect.close()
		print (server_socket.recv(size))
	except:
		print ('Fail!!')
		activeStoreFlag = False
	s.close()
		

	print ('\n\033[92m\033[1m########### active mode RETR ###########\033[0m') # ACTIVE DOWNLOAD
	print ('download server_file.txt as from_server.txt')
	activeRetrieveFlag = True
	s = port(server_socket)
	time.sleep(1)
	server_socket.send('RETR server_file.txt' + '\r\n')
	try:
		connect, address = s.accept()
		testFile = open(client_home + '/from_server.txt', 'w')
		while True:
			data = connect.recv(size)
			if(data):
				testFile.write(data)
			else:
				break
		print (server_socket.recv(size))
		testFile.close()
		connect.close()
	except:
		print ('Fail!!')
		activeRetrieveFlag = False
	s.close()

	print ('\033[92m\033[1m########### passive mode STOR ###########\033[0m') # PASSIVE UPLOAD
	print ('upload client_file1.pdf as from_client1.pdf')
	passiveStoreFlag = True
	try:
		s = pasv(server_socket)
		time.sleep(1)
		server_socket.send('STOR from_client1.pdf' + '\r\n')
		testFile = file(client_home + 'client_file1.pdf')
		while True:
			data = testFile.read(size)
			if(data):
				s.send(data)
			else:
				break
		print (server_socket.recv(size))
		testFile.close()
		s.close()
		print (server_socket.recv(size)	  )
	except:
		print ('Fail!!')
		passiveStoreFlag = False


	print ('\033[92m\033[1m########### passive mode RETR ###########\033[0m') # PASSIVE DOWNLOAD
	print ('download server_file1.pdf as from_server1.pdf')
	passiveRetrieveFlag = True
	try:
		s = pasv(server_socket)
		time.sleep(1)
		server_socket.send('RETR server_file1.pdf' + '\r\n')
		testFile = open(client_home + 'from_server1.pdf', 'w')
		while True:
			data = s.recv(size)
			if(data):
				testFile.write(data)
			else:
				break
		print (server_socket.recv(size))
		testFile.close()
		s.close()
	except:
		print ('Fail!!')
		passiveRetrieveFlag = False

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
	
	print ('\033[92m\033[1m########### Buffer ###########\033[0m') # Buffer
	bufferFlag = True
	server_socket.send('P')
	server_socket.send('WD')
	server_socket.send('\r\n')
	print ('try: PWD')
	data = server_socket.recv(size)
	print (data[0:-2])
	if data[0] != '2':
		bufferFlag = False
		print ('Failed')
	else:
		print ('Buffer ok')

	print ('')
	print ('\033[92m\033[1m########### Summary ###########\033[0m') # SUMMARY

	summary('authentication', authenticationFlag)
	summary('LIST', listFlag)
	summary('active mode upload', activeStoreFlag)
	summary('active mode download', activeRetrieveFlag)
	summary('passive mode upload', passiveStoreFlag)
	summary('passive mode download', passiveRetrieveFlag)
	summary('file comapre', fileCompareFlag)
	summary('delete file', deleteFlag)
	summary('buffer', bufferFlag)
	time.sleep(1)
	server_socket.close() # Close connection