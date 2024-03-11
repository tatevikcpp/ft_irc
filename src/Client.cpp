#include "Client.hpp"
#include <netinet/in.h>

Client::Client(int fd, const struct sockaddr& addr) : _fd(fd)
{
    this->_clientAddr = addr;
    this->_registered = false;
}

Client::~Client()
{

}

bool Client::isRegistered(void)
{
    return (this->_registered);
}

void Client::setPASS(const std::string& pass)
{
    this->_pass = pass;
}

void Client::setNick(const std::string& nick)
{
    this->_nick = nick;
}

void Client::setUSER(const std::string& username, const std::string& realname)
{
    this->_username = username;
    this->_realname = realname;
}

//   std::map<std::string, std::pair<Channel*, TypeClient>>
Channel* Client::createChannel(const std::string& name, const std::string& pass)
{
    // this->_channels.insert(name, std::pair<Channel*, TypeClient>(tmp, Owner));
    if (this->_channels.find(name) == this->_channels.end())
    {
        return (NULL);
    }
    Channel *tmp = new Channel(name, this, pass);
    this->_channels[name] = std::make_pair(tmp, Owner);
    return (tmp);
}

void Client::leaveChannel(const std::string& name)
{
    std::map<std::string, std::pair<Channel*, TypeClient> >::iterator it = this->_channels.find(name);
    if (it != this->_channels.end())
    {
        it->second.first->deleteClient(*this);
        this->_channels.erase(it);  //TODO - ha vor ?
    }
}


// void Client::bufferToList(void)
// {
//     std::string str = this->_buffer;
//     std::string del = "\r\n";
//     size_t start = 0;

//     // _bufferlist.clear();
//     // if (str.find(del) == std::string::npos)
//     // {
//     //     del = '\n';
//     // }
    
//     size_t end = str.find(del);

//     while (end != std::string::npos)
//     {
//         _bufferlist.push_back(str.substr(start, end - start));
//         start = end + del.length();
//         end = str.find(del, start);
//     }
// }

// void Client::joinToChannel(Client *client)
// {
//     channel->joinClient()
// }