#ifndef _MY_INETADDRESS_H_
#define _MY_INETADDRESS_H_

#include <netinet/in.h>
#include <string>

namespace st
{
class InetAddress
{
public:
	InetAddress(unsigned short port);
	InetAddress(const char * ip, unsigned short port);
	InetAddress(const struct sockaddr_in & addr);

	struct sockaddr_in *getInetAddressPtr();

	std::string ip() const;
	unsigned short port() const;

private:
	struct sockaddr_in _addr;
};

}
#endif
