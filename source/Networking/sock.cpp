#include "sock.h"

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
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(sockItem->port_rec);
	 
	status = bind(sockItem->ActiveSocketFD, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	if( status == -1 )
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
	msgSize = recv(sockItem->ActiveSocketFD,sockItem->buffer,MAXMSG,0);
	
	printf ("\nMessage size: %d", msgSize);
	printf ("\nMessage %s", sockItem->buffer);

	if (sockItem->port_rec == MAPPORT)
	{
		if(sockItem->buffer != NULL)
			MapRecvMessages.push(sockItem->buffer);
	}
	else
	{
		if(sockItem->buffer != NULL)
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

	msgSize = recvfrom(sockItem->ActiveSocketFD,sockItem->buffer,MAXMSG,0,(struct sockaddr *) &remaddr, &addrlen);
	
	if (sockItem->port_rec == MAPPORT)
	{
		if(sockItem->buffer != NULL)
			MapRecvMessages.push(sockItem->buffer);
	}
	else
	{
		if(sockItem->buffer != NULL)
			AppRecvMessages.push(sockItem->buffer);
	}


	status = connect(sockItem->ActiveSocketFD,(struct sockaddr *) &remaddr,addrlen);
	if(status == -1)
	{
		perror("connect()");
		exit(1);
	}
	
	return msgSize;
}

int SendAppMSG(SocketItem* sockItem)
{
	int status = 0;

	//Yes, I used a const-cast....shut up
	if(!AppSendMessages.empty())
	{
		//sleep(10);
		std::string message = AppSendMessages.top();
		char *msg = const_cast<char*>(message.c_str());
		int len = message.size();
		AppSendMessages.pop();

		struct hostent *hp;     /* host information */
		struct sockaddr_in servaddr;    /* server address */

		printf ( msg );

		/* fill in the server's address and data */
		memset((char*)&servaddr, 0, sizeof(servaddr));
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(sockItem->port_trans);

		/* look up the address of the server given its name */
		hp = gethostbyname("192.168.2.55"); // Aaron's
		//hp = gethostbyname("192.168.2.106"); // Kevin's

		/* put the host's address into the server address structure */
		memcpy((void *)&servaddr.sin_addr, hp->h_addr_list[0], hp->h_length);

		status = sendto(sockItem->ActiveSocketFD, msg, len, 0, (struct sockaddr *)&servaddr, sizeof(servaddr) );

		//status=send(sockItem->ActiveSocketFD,msg,len,0);

	}
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

