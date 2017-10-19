
#include "Winsock.h"
#include <thread>
#include <chrono>


using namespace std::this_thread;
using namespace std::chrono;

Client::Client(const std::string IP_ADDRESS, uint32_t PortNum)
	:
	IP_ADDRESS(IP_ADDRESS),
	PortNum(PortNum)
{
	//Need sizeofaddr for the connect function
	//we'll define the address using the inetpton function and store that in our buffer (addr.sin_addr...)

	InetPton(AF_INET, this->IP_ADDRESS.c_str(), &addr.sin_addr.s_addr);
	addr.sin_port = htons(this->PortNum); //Port = 1111
	addr.sin_family = AF_INET; //IPv4 Socket

							   //we return the result of the socket to our connect socket
							   //this is creating a socket so that we can connect to our server
	Connection = socket(AF_INET, SOCK_STREAM, NULL);

	//Winsock Startup
	//first what is happening here is that we are starting up (initialising the winsock dll) where the version is defined through the passed paramaters in MAKEWORD
	WORD DllVersion = MAKEWORD(2, 1);

	WSAData wsaData;
	//If WSAStartup returns anything other than 0, then that means an error has occured in the WinSock Startup.
	if (WSAStartup(DllVersion, &wsaData) != 0)
	{
		MessageBox(0, "Winsock Failed To Initialize.", "Winsock", MB_ICONERROR);
	}
}

Client::~Client()
{
	closesocket(Connection);
	WSACleanup();
}

bool Client::Connect()
{
	return connect(Connection, (SOCKADDR*)&addr, sizeof(addr));
}

void Client::SendAMessage(const std::string & Message)
{

	size_t totalbytesent = 0;
	size_t bytesleft = Message.length();
	//the bytes sent from our function
	size_t n; 

    //while the total bytes sent is less than the bytes we are trying to send, continue this loop
	while (totalbytesent < Message.length())
	{
		//send our buffer, if it didnt send all the information, send the whole buffer again
		n = send(Connection, Message.c_str(), bytesleft, 0);

		if (n == SOCKET_ERROR)
			break;
		//store the totalbytes sent in our variable to keep track
		totalbytesent = n;

	}
	
}
