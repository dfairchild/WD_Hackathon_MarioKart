/*
 * ThreadHandlers.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: Nick
 */

#include "..\..\source\Networking\sock.h"
#define LISTEN_PORT 	5000
#define SENDER_PORT 	5001

void ListenerThread()
{
	SocketItem sock;
	sock.port = LISTEN_PORT;

	CreateSocket(&sock);
	AcceptSocket(&sock);
	GetMSG(&sock);
	CloseSockets(&sock);
}

void SenderThread()
{
	SocketItem sock;
	sock.port = SENDER_PORT;

	ConnectToSocket(&sock, "192.168.1.6");
	SendMSG(&sock, "Test", sizeof("Test"));
	CloseSockets(&sock);
}

