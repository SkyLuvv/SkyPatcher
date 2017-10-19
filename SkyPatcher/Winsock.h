#pragma once
#include <string>
#include "WindowsIncludes.h"

class Client
{

public:
	Client() = default;
	Client(const std::string IP_ADDRESS, uint32_t PortNum);
	~Client();
	bool Connect();
	void SendAMessage(const std::string & Message);
private:
	//IP address the client is going to connect to (our server)
	std::string IP_ADDRESS;
	//port number it's going to connect to
	uint32_t PortNum;
	SOCKADDR_IN addr;
	SOCKET Connection;

};