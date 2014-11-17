#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXMSG 4096

int ListenSockFD, ActiveSocketFD;
char buffer[MAXMSG];
struct sockaddr_in serv_addr, cli_addr, sender_addr;

void CreateSocket(int port)
{
	int status;
	int val;

	ListenSockFD=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if(ListenSockFD==-1)
	{
		perror("socket()");
		exit(1);
	}

	val = 1;
	setsockopt(ListenSockFD, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
	
	serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(port);
	 
	status=bind(ListenSockFD, (struct sockaddr *) &serv_addr, sizeof(serv_addr))
	if(status==-1)
	{
		perror("bind()");
		exit(1);
	}
}

void AcceptSocket(void)
{
	listen(ListenSockFD,5);
	ActiveSocketFD = accept(ListenSockFD,(struct sockaddr *)&cli_addr,sizeof(cli_addr));
}

void ConnectToSocket(char *ServerName, int port)
{
	struct hostent *hostptr;
	int status;
	
	ActiveSocketFD=socket(PF_INET,SOCK_DGRAM,IPPROTO_UDP);
	
	hostptr=gethostbyname(ServerName);
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
   serv_addr.sin_port = htons(port);
   status=connect(ActiveSocketFD,(struct sockaddr *) &serv_addr,sizeof(serv_addr))
	
	if(status==-1)
	{
		perror("connect()");
		exit(1);
	}
	
}

void CloseSockets(void)
{
	close(ListenSockFD);
	close(ActiveSocketFD);
}

int GetMSG(void)
{
	int msgSize;
	
	bzero(buffer,MAXMSG);
	size=recv(ActiveSocketFD,buffer,MAXMSG,0);
	
	return size;
}

void SendMSG(unsigned char *msg,int len)
{
	int status;

	status=send(ActiveSocketFD,msg,len,0);
	return status;
}
	
	
