/*
 * ThreadHandlers.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: Nick
 */

#include "..\..\source\Networking\sock.h"
#define LISTEN_PORT 	5000
#define SENDER_PORT 	5001

void ListenerThread(int port)
{
	SocketItem sock;
	sock.port = port;

	CreateSocket(&sock);
	AcceptSocket(&sock);
	GetMSG(&sock);
	CloseSockets(&sock);
}

void SenderThread(int port, const char *ServerName)
{
	SocketItem sock;
	sock.port = port;

	ConnectToSocket(&sock, ServerName);
	SendMSG(&sock);
	CloseSockets(&sock);
}

