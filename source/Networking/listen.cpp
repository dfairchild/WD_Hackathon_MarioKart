#include "sock.cpp"
#include <cerrno>

SocketItem testsocket;

int main(void)
{
	printf ("\nTestsocket assign port");
	//testsocket.port_trans=12345;
	testsocket.port_rec=12346;

	printf ("\nCreating Socket");
	CreateSocket(&testsocket);

	printf ("\nRecieve and connect");
	GetMSGAndConnect(&testsocket);

	printf ("\nMessage reads: %s", testsocket.buffer);

	printf ("\nSending testing string");
	SendMSG(&testsocket, "testing", 7);

	CloseSockets(&testsocket);

	printf ("\n");

	return 0;
	
}
