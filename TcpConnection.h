#ifndef _MY_TCPCONNECTION_H_
#define _MY_TCPCONNECTION_H_

#include "Noncopyable.h"
#include "Socket.h"
#include "SocketIO.h"
#include "InetAddress.h"
#include <string>
#include <memory>
#include <functional>

namespace st
{
class TcpConnection;
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

class TcpConnection 
: Noncopyable
, public std::enable_shared_from_this<TcpConnection>
{
public:
	typedef std::function<void(TcpConnectionPtr)> TcpConnectionCallback;
	TcpConnection(int fd);
	~TcpConnection();

	std::string receive();
	void send(const std::string & msg);
	void shutdown();

	std::string toString() const;

	void handleConnectionCallback();
	void handleMessageCallback();
	void handleCloseCallback();

	void setConnectionCallback(TcpConnectionCallback cb);
	void setMessageCallback(TcpConnectionCallback cb);
	void setCloseCallback(TcpConnectionCallback cb);

private:
	Socket _sock;
	SocketIO _sockIO;
	const InetAddress _localAddr;
	const InetAddress _peerAddr;
	bool _isShutdownWrite;

	TcpConnectionCallback _onConnectionCb;
	TcpConnectionCallback _onMessageCb;
	TcpConnectionCallback _onCloseCb;
};

}
#endif
