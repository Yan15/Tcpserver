#ifndef __MY_TCPSERVER_H_
#define __MY_TCPSERVER_H_

#include "Noncopyable.h"
#include "Socket.h"
#include "EpollPoller.h"

namespace st
{

class TcpServer : Noncopyable
{
public:
	typedef EpollPoller::EpollPollerCallback TcpServerCallback;
	TcpServer(unsigned short port);
	TcpServer(const char * ip, unsigned short port);

	void start();
	void stop();

	void setConnectionCallback(TcpServerCallback cb);
	void setMessageCallback(TcpServerCallback cb);
	void setCloseCallback(TcpServerCallback cb);

private:
	Socket _sock;
	EpollPoller _epoll;

	TcpServerCallback _onConnection;
	TcpServerCallback _onMessage;
	TcpServerCallback _onClose;
};

}

#endif
