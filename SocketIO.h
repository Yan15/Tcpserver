#ifndef __MY_SOCKETIO_H_
#define __MY_SOCKETIO_H_

#include "Noncopyable.h"
#include <unistd.h>

namespace st
{
class SocketIO : Noncopyable
{
public:
	SocketIO(int fd);

	ssize_t readn(char * buff, size_t count);
	ssize_t writen(const char * buff, size_t count);
	ssize_t readline(char * buff, size_t max);

private:
	ssize_t readPeek(char * buff, size_t count);

private:
	int _fd;
};

}

#endif
