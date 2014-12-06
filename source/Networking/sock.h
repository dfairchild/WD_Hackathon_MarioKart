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

#define MAPRECVPORT 5000
#define MAPSENDPORT 5001
#define APPRECVPORT 6000
#define APPSENDPORT 6001


struct SocketItem
{
	int port_trans;
	int port_rec;
	char buffer[MAXMSG];
	int ActiveSocketFD;
};

extern std::stack<std::string> AppSendMessages;
extern std::stack<std::string> AppRecvMessages;

extern std::stack<std::string> MapSendMessages;
extern std::stack<std::string> MapRecvMessages;

void BindSocket(SocketItem* sockItem);
void CreateSocket(SocketItem* sockItem);
void ConnectToSocket(SocketItem* sockItem, const char *ServerName);
void CloseSockets(SocketItem* sockItem);
int GetMSG(SocketItem* sockItem);
int GetMSGAndConnect(SocketItem* sockItem);
int SendAppMSG(SocketItem* sockItem);
int SendMapMSG(SocketItem* sockItem);

void MapListenerThread();
void AppSenderThread();
void MapSenderThread(const char *ServerName);

