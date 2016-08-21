#ifndef _MY_SOCKET_H_
#define _MY_SOCKET_H_

#include "Noncopyable.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


namespace st
{
class InetAddress;

class Socket : Noncopyable
{
public:
	Socket();
	Socket(int);
	void ready(InetAddress & addr);
	int accept();
	int fd();

	void shutdownWrite();

	static InetAddress getLocalAddr(int fd);
	static InetAddress getPeerAddr(int fd);
private:
	void setReuseAddr(bool flag);
	void setReusePort(bool flag);
	void bind(InetAddress & addr);
	void listen();
private:
	int _fd;
};

}

#endif
