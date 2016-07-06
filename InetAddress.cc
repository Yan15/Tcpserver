#include "InetAddress.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

namespace st
{
InetAddress::InetAddress(unsigned short port)
{
	memset(&_addr,0,sizeof(struct sockaddr_in));
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
	_addr.sin_addr.s_addr = INADDR_ANY;
}

InetAddress::InetAddress(const char *ip,unsigned short port)
{
	memset(&_addr,0,sizeof(struct sockaddr_in));
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
	_addr.addr_in.s_addr = inet_addr(ip);
}

InetAddress::InetAddress(struct sockaddr_in &_addr)
:_addr(addr)
{}

string InetAddress::ip()const
{
	return string(inet_ntoa(_addr.sin_addr));
}

unsigned short InetAddress::port()const
{
	return ntohs(_addr.sin_port);
}

struct sockaddr_in *InetAddress::getInetAddressPtr()
{
	return &_addr;
}
}
