#include "Socket.h"
#include "InetAddress.h"
#include "TcpConnection.h"
#include "EpollPoller.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <iostream>

using std::cout;
using std::endl;

void onConnection(st::TcpConnectionPtr conn)
{
	cout << conn->toString() << "has connected!" << endl;
	conn->send("welcome to server.");
}

void onMessage(st::TcpConnectionPtr conn)
{
	std::string msg = conn->receive();
	cout << msg << endl;
	conn->send(msg);
}

void onClose(st::TcpConnectionPtr conn)
{
	cout << conn->toString() << " hase close." << endl;
}

int main(void)
{
	st::Socket sock;
	st::InetAddress addr(8888);
	sock.ready(addr);

	st::EpollPoller epollPoller(sock.fd());
	epollPoller.setConnectionCallback(onConnection);
	epollPoller.setMessageCallback(onMessage);
	epollPoller.setCloseCallback(onClose);

	epollPoller.loop();

#if 0
	int peerfd = sock.accept();
	st::TcpConnection conn(peerfd);
	std::cout << conn.toString() << std::endl;
	conn.send("welcome to server");
	while(true)
	{
		std::string s1 = conn.receive();
		conn.send(s1);
	}
#endif
	return 0;
}
