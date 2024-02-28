#include "Client.hpp"
#include <netinet/in.h>

Client::Client(int fd, const struct sockaddr_in& addr/* , TypeClient */) :_fd(fd)
{
    this->_fd = fd;
    this->_clientAddr = addr;
}

Client::~Client()
{

}