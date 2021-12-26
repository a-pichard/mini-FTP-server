#!/usr/bin/python
# -*- coding: utf-8 -*-

import socket
import time
import random
import os
import re

from auth import auth
from common_cmds import common_cmds
from listftp import listftp
from file_transfer import active_download, active_upload, passive_download, passive_upload
from file_comparator import file_comparator
from delete_file import delete_file
from buffer import buffer

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

def summary(title, flag):
	print ('%-25s %s' % (title, 'OK' if flag else 'Fail'))


if __name__ == '__main__' :
	server_socket = {}

	try:
		server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		server_socket.connect( (serverAddress, serverPort))
		print ('using socket', server_socket.getsockname())
	except:
		print ("can't connect to server, double check address and port")
	print ('------------------------------------')

	authentication_flag = auth(server_socket, name, passwd, size)
	common_cmds(server_socket, size)
	list_flag = listftp(server_socket, clientAddress, size)
	activeStore_flag = active_upload(server_socket, client_home, clientAddress, size)
	activeRetrieve_flag = active_download(server_socket, client_home, clientAddress, size)
	passiveStore_flag = passive_upload(server_socket, client_home, size)
	passiveRetrieve_flag = passive_download(server_socket, client_home, size)
	fileCompare_flag = file_comparator(client_home, server_home)
	delete_flag = delete_file(server_socket, size)
	buffer_flag = buffer(server_socket, size)

	print ('\n\033[92m\033[1m########### Summary ###########\033[0m') # SUMMARY
	summary('authentication', authentication_flag)
	summary('LIST', list_flag)
	summary('active mode upload', activeStore_flag)
	summary('active mode download', activeRetrieve_flag)
	summary('passive mode upload', passiveStore_flag)
	summary('passive mode download', passiveRetrieve_flag)
	summary('file compare', fileCompare_flag)
	summary('delete file', delete_flag)
	summary('buffer', buffer_flag)
	time.sleep(1)
	server_socket.close() # Close connection

	exit_flag = 0
	if not (authentication_flag and list_flag and activeStore_flag and activeRetrieve_flag and passiveStore_flag and passiveRetrieve_flag and fileCompare_flag and delete_flag and buffer_flag):
		exit_flag = 1
	exit(exit_flag)