#include "..\..\source\Networking\sock.h"

struct sockaddr_in serv_addr, cli_addr;

std::stack<std::string> AppSendMessages;
std::stack<std::string> AppRecvMessages;

std::stack<std::string> MapSendMessages;
std::stack<std::string> MapRecvMessages;

void BindSocket(SocketItem* sockItem)
{
	int status;
	int val;

	val = 1;
	setsockopt(sockItem->ActiveSocketFD, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(sockItem->port_rec);
	 
	status=bind(sockItem->ActiveSocketFD, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	if(status==-1)
	{
		perror("bind()");
		exit(1);
	}

}

void CreateSocket(SocketItem* sockItem)
{
	sockItem->ActiveSocketFD=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if(sockItem->ActiveSocketFD==-1)
	{
		perror("listen socket()");
		exit(1);
	}

	BindSocket(sockItem);
}

void ConnectToSocket(SocketItem* sockItem, const char *ServerName)
{
	struct hostent *server;
	int status;
	
	sockItem->ActiveSocketFD=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if(sockItem->ActiveSocketFD==-1)
	{
		perror("active socket()");
		exit(1);
	}
	
	server=gethostbyname(ServerName);
	
	std::memset((char *) &cli_addr, 0, sizeof(cli_addr));
	cli_addr.sin_family = AF_INET;

	memcpy((char *)&cli_addr.sin_addr.s_addr, (char *)server->h_addr, server->h_length);
	cli_addr.sin_port = htons(sockItem->port_trans);
	
	status=connect(sockItem->ActiveSocketFD,(struct sockaddr *) &serv_addr,sizeof(serv_addr));
	if(status==-1)
	{
		perror("connect()");
		exit(1);
	}
	
}

void CloseSockets(SocketItem* sockItem)
{
	close(sockItem->ActiveSocketFD);
}

int GetMSG(SocketItem* sockItem)
{
	int msgSize;
	
	memset(sockItem->buffer, 0, MAXMSG);
	msgSize=recv(sockItem->ActiveSocketFD,sockItem->buffer,MAXMSG,0);
	
	if (sockItem->port_rec == MAPRECVPORT)
	{
		MapRecvMessages.push(sockItem->buffer);
	}
	else
	{
		AppRecvMessages.push(sockItem->buffer);
	}
	return msgSize;
}

int GetMSGAndConnect(SocketItem* sockItem)
{
	int status;
	int msgSize;
	struct sockaddr_in remaddr; 
	socklen_t addrlen = sizeof(remaddr);

	msgSize=recvfrom(sockItem->ActiveSocketFD,sockItem->buffer,MAXMSG,0,(struct sockaddr *) &remaddr, &addrlen);
	
	if (sockItem->port_rec == MAPRECVPORT)
	{
		MapRecvMessages.push(sockItem->buffer);
	}
	else
	{
		AppRecvMessages.push(sockItem->buffer);
	}


	status=connect(sockItem->ActiveSocketFD,(struct sockaddr *) &remaddr,addrlen);
	if(status==-1)
	{
		perror("connect()");
		exit(1);
	}
	
	return msgSize;
}

int SendAppMSG(SocketItem* sockItem)
{
	int status;

	//Yes, I used a const-cast....shut up
	char *msg = const_cast<char*>(AppSendMessages.top().c_str());
	int len = AppSendMessages.top().size();
	AppSendMessages.pop();
	status=send(sockItem->ActiveSocketFD,msg,len,0);
	return status;
}
	
int SendMapMSG(SocketItem* sockItem)
{
	int status;

	//Yes, I used a const-cast....shut up
	char *msg = const_cast<char*>(MapSendMessages.top().c_str());
	int len = MapSendMessages.top().size();
	MapSendMessages.pop();
	status=send(sockItem->ActiveSocketFD,msg,len,0);
	return status;
}

