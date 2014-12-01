#include "..\..\source\Networking\sock.h"

struct sockaddr_in serv_addr, cli_addr, sender_addr;

void CreateSocket(SocketItem* sockItem)
{
	int status;
	int val;

	sockItem->ListenSockFD=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if(sockItem->ListenSockFD==-1)
	{
		perror("socket()");
		exit(1);
	}

	val = 1;
	setsockopt(sockItem->ListenSockFD, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(sockItem->port);
	 
	status=bind(sockItem->ListenSockFD, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	if(status==-1)
	{
		perror("bind()");
		exit(1);
	}
}

void AcceptSocket(SocketItem* sockItem)
{
	listen(sockItem->ListenSockFD,5);
	sockItem->ActiveSocketFD = accept(sockItem->ListenSockFD,(struct sockaddr *)&cli_addr,(socklen_t*)(sizeof(cli_addr)));
}

void ConnectToSocket(SocketItem* sockItem, char *ServerName)
{
	struct hostent *server;
	int status;
	
	sockItem->ActiveSocketFD=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
	
	server=gethostbyname(ServerName);
	
	// Use ISO-standard memset instead of non-standard bzero
	std::memset((char *) &serv_addr, 0, sizeof(serv_addr));
	//bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;

	//Use ISO-standard memcpy instead of non-standard bcopy
	memcpy((char *)&serv_addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
	//bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
	serv_addr.sin_port = htons(sockItem->port);
	status=connect(sockItem->ActiveSocketFD,(struct sockaddr *) &serv_addr,sizeof(serv_addr));
	
	if(status==-1)
	{
		perror("connect()");
		exit(1);
	}
	
}

void CloseSockets(SocketItem* sockItem)
{
	close(sockItem->ListenSockFD);
	close(sockItem->ActiveSocketFD);
}

int GetMSG(SocketItem* sockItem)
{
	int msgSize;
	
	memset(sockItem->buffer, 0, MAXMSG);
	//bzero(sockItem->buffer,MAXMSG);
	msgSize=recv(sockItem->ActiveSocketFD,sockItem->buffer,MAXMSG,0);
	
	return msgSize;
}

int SendMSG(SocketItem* sockItem, char *msg,int len)
{
	int status;

	status=send(sockItem->ActiveSocketFD,msg,len,0);
	return status;
}
	
	
