#include "SocketIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>



namespace st
{

SocketIO::SocketIO(int fd)
: _fd(fd)
{}

ssize_t SocketIO::readn(char * buff, size_t count)
{
	size_t nleft = count;
	char * pbuf = buff;
	ssize_t ret = 0;
	while(nleft > 0)
	{
		ret = read(_fd, pbuf, nleft);
		if(-1 == ret)
		{
			if(errno == EINTR)
			{	continue;	}
			perror("read");
			exit(EXIT_FAILURE);
			
		}
		else if(0 == ret)//读到文件末尾
		{
			break;
		}
		pbuf += ret;
		nleft -= ret;
	}
	return (count - nleft);
}

ssize_t SocketIO::writen(const char * buff, size_t count)
{
	size_t nleft = count;
	const char * pbuf = buff;
	ssize_t ret = 0;
	while(nleft > 0)
	{
		ret = write(_fd, pbuf, nleft);
		if(-1 == ret)
		{
			if(errno == EINTR)
				continue;
			perror("write");
			exit(EXIT_FAILURE);
		}	
		pbuf += ret;
		nleft -= ret;
	}
	return (count - nleft);
}

ssize_t SocketIO::readPeek(char * buff, size_t count)
{
	ssize_t nread;
	do
	{
		nread = ::recv(_fd, buff, count, MSG_PEEK);
	}while(nread == -1 && errno == EINTR);
	return nread;
}


ssize_t SocketIO::readline(char * buff, size_t max)
{
	size_t nleft = max - 1;
	char * pbuf = buff;
	size_t total = 0;
	while(nleft > 0)
	{
		ssize_t  nread = readPeek(pbuf, nleft); 
		if(nread <= 0)
			return nread;
		for(int idx = 0; idx != nread; ++idx)
		{
			if(pbuf[idx] == '\n')
			{
				int nsize = idx + 1;
				if(readn(pbuf, nsize) != nsize)
					return EXIT_FAILURE;
				nleft -= nsize;
				total += nsize;
				pbuf += nsize;
				*pbuf = '\0';
				return total;
			}
		}
		if(readn(pbuf, nread) != nread)
			return EXIT_FAILURE;

		nleft -= nread;
		pbuf += nread;
		total += nread;
	}
	*pbuf = '\0';
	return max - 1;
}

}
