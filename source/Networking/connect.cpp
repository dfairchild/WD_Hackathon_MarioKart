#include "sock.cpp"

SocketItem testsocket;

int main(void)
{
	printf ("\nTestsocket assign port");
	testsocket.port_trans = 6000;
	testsocket.port_rec = 0;

	printf ("\nCreate Socket");
	//ConnectToSocket(&testsocket,"192.168.2.100");
	CreateSocket(&testsocket);

	printf ("\nSending testing string");
	SendMessages.push("Test Message");
	SendMSG(&testsocket);

	//printf ("\nGetting Message");
	//GetMSG(&testsocket);

	//printf ("\nMessage reads: %s", testsocket.buffer);

	while(true)
	{
		SendMessages.push("spam");
		SendMSG(&testsocket);
		sleep(5);
	}

	CloseSockets(&testsocket);

	printf ("\n");
	
	return 0;
}
