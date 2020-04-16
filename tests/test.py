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

	authenticationFlag = auth(server_socket, name, passwd, size)
	common_cmds(server_socket, size)
	listFlag = listftp(server_socket, clientAddress, size)
	activeStoreFlag = active_upload(server_socket, client_home, clientAddress, size)
	activeRetrieveFlag = active_download(server_socket, client_home, clientAddress, size)
	passiveStoreFlag = passive_upload(server_socket, client_home, size)
	passiveRetrieveFlag = passive_download(server_socket, client_home, size)
	fileCompareFlag = file_comparator(client_home, server_home)
	deleteFlag = delete_file(server_socket, size)
	bufferFlag = buffer(server_socket, size)

	print ('\n\033[92m\033[1m########### Summary ###########\033[0m') # SUMMARY
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