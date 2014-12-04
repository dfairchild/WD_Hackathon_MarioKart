#include "sock.cpp"

SocketItem testsocket;

int main(void)
{
	printf ("\nTestsocket assign port");
	testsocket.port_trans=12346;
	testsocket.port_rec=12345;

	printf ("\nConnect to Socket");
	ConnectToSocket(&testsocket,"127.0.0.1");

	printf ("\nSending testing string");
	SendMSG(&testsocket, "testing", 7);

	printf ("\nGetting Message");
	GetMSG(&testsocket);

	printf ("\nMessage reads: %s", testsocket.buffer);

	CloseSockets(&testsocket);

	printf ("\n");
	
	return 0;
}
