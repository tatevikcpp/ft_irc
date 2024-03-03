#include "Client.hpp"
#include <netinet/in.h>

Client::Client(int fd, const struct sockaddr& addr) : _fd(fd)
{
    this->_clientAddr = addr;
}

Client::~Client()
{

}

void Client::bufferToList(void)
{
    std::string str = this->_buffer;
    std::string del = "\r\n";
    size_t start = 0;

    // _bufferlist.clear();
    // if (str.find(del) == std::string::npos)
    // {
    //     del = '\n';
    // }
    
    size_t end = str.find(del);

    while (end != std::string::npos)
    {
        _bufferlist.push_back(str.substr(start, end - start));
        start = end + del.length();
        end = str.find(del, start);
    }
}