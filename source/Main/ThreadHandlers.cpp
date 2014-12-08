/*
 * ThreadHandlers.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: Nick
 */

#include "..\..\source\Networking\sock.h"

void APPListenerThread()
{
	SocketItem sock;
	sock.port_rec = APPPORT;

	printf ("\nListerner : create socket");
	CreateSocket(&sock);

	do
	{
		memset(sock.buffer, 0, MAXMSG);
		GetMSG(&sock);

		printf("\nLOOP BITCH!");
		// Need to add Handler to send data to map
		// not exactly sure how this would be handled

	}while(true);

	CloseSockets(&sock);
}

void AppSenderThread()
{
	SocketItem sock;
	sock.port_trans = APPPORT;


	CreateSocket(&sock);

	// listens for first message then connects back.
	//GetMSGAndConnect(&sock);

	do
	{
		//AppSendMessages.push("Fuck off Tim.");
		// if a message needs to be sent to the app
		if( !AppSendMessages.empty() )
		{
			SendAppMSG(&sock);
		}

		// might need to fire off an app listener thread so that it will handle all the data in (item uses etc)
		// or get a non-blocking get message to recieve the data

	}while(true);

	CloseSockets(&sock);
}

void MapListenerThread()
{
	SocketItem sock;
	sock.port_rec = MAPPORT;

	printf ("\nListerner : create socket");
	CreateSocket(&sock);
	
	do
	{
		memset(sock.buffer, 0, MAXMSG);
		GetMSG(&sock);

		printf("\nLOOP BITCH!");
		// Need to add Handler to send data to map
		// not exactly sure how this would be handled

	}while(true);
	
	CloseSockets(&sock);
}

void MapSenderThread(const char *ServerName)
{
	SocketItem sock;
	sock.port_trans = MAPPORT;

	ConnectToSocket(&sock, ServerName);

	do
	{

		if( !MapSendMessages.empty() )
		{
			SendMapMSG(&sock);
		}

	}while(true);

	CloseSockets(&sock);
}

