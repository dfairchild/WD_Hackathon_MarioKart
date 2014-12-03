#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <stack>

#define MAXMSG 4096

struct SocketItem
{
	int port;
	char buffer[MAXMSG];
	int ListenSockFD;
	int ActiveSocketFD;
};

extern std::stack<std::string> SendMessages;
extern std::stack<std::string> RecvMessages;

void CreateSocket(SocketItem* sockItem);
void AcceptSocket(SocketItem* sockItem);
void ConnectToSocket(SocketItem* sockItem, const char *ServerName);
void CloseSockets(SocketItem* sockItem);
int GetMSG(SocketItem* sockItem);
int SendMSG(SocketItem* sockItem);

void ListenerThread(int port);
void SenderThread(int port, const char *ServerName);

