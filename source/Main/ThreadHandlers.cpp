/*
 * ThreadHandlers.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: Nick
 */

#include "..\..\source\Networking\sock.h"

void MapListenerThread()
{
	SocketItem sock;
	sock.port_rec = MAPRECVPORT;

	printf ("\nListerner : create socket");
	CreateSocket(&sock);
	
	do
	{
		GetMSG(&sock);

		// Need to add Handler to send data to map
		// not exactly sure how this would be handled

	}while(true);
	
	CloseSockets(&sock);
}

void AppSenderThread()
{
	SocketItem sock;
	sock.port_rec = APPRECVPORT;


	CreateSocket(&sock);

	// listens for first message then connects back.
	GetMSGAndConnect(&sock);

	do
	{
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

void MapSenderThread(const char *ServerName)
{
	SocketItem sock;
	sock.port_trans = MAPRECVPORT;

	ConnectToSocket(&sock, ServerName);

	do
	{
		if( !AppSendMessages.empty() )
		{
			SendMapMSG(&sock);
		}

	}while(true);

	CloseSockets(&sock);
}

