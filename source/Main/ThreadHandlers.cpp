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
	sock.port_rec = port;

	printf ("\nListerner : create socket");
	CreateSocket(&sock);
	printf ("\nListerner : get message and connect");
	GetMSGAndConnect(&sock);
	
	do
	{
		GetMSG(&sock);
	}while(true);
	
	CloseSockets(&sock);
}

void SenderThread(int RecPort, int TransPort, const char *ServerName)
{
	SocketItem sock;
	sock.port_rec = RecPort;
	sock.port_trans = TransPort;

	ConnectToSocket(&sock, ServerName);
	SendMSG(&sock);
	CloseSockets(&sock);
}

