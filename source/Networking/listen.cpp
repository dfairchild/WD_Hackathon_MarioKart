#include "sock.cpp"
#include <cerrno>

SocketItem testsocket;

int main(void)
{
	printf ("\nTestsocket assign port");
	//testsocket.port_tran s= 0;
	testsocket.port_rec = 5000;

	printf ("\nCreating socket");
	CreateSocket(&testsocket);

	printf ("\nGet message");
	GetMSG(&testsocket);

	printf ("\nMessage reads: %s", testsocket.buffer);

	CloseSockets(&testsocket);

	printf ("\n");

	return 0;
	
}
