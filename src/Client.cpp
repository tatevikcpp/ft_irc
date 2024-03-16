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

void Client::checkForRegistered(void)
{
    if (!_pass.empty() && !_username.empty() && !_nick.empty() && !_registered)
    {
        this->_registered = true;
        //  reply(RPL_WELCOME(_nick));
    }
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

// void Client::joinToChannel(Client *client)
// {
//     channel->joinClient()
// }



void Client::setArguments(void)
{
    std::string str(_vecBuffer.front());
    std::string delimiter = " ";
    std::size_t end = 0;
    std::size_t i = 0;

    i = str.find(delimiter);
    if (i != std::string::npos)
    {
        this->_command = str.substr(0, i);
        str = str.substr(i);
    }

    i = 0;
    if (!str.empty())
    {
        while (str[i] && str[i] == ' ')
            i++;

        end = str.find(delimiter, i);

        while (end != std::string::npos)
        {
            if (str[i] && str[i] == ':')
            {
                this->_arguments.push_back(str.substr(i, end - i));
            }
        }
    }

}

void Client::splitbuffer(void)
{
    std::string str = this->_buffer;
    std::string del = "\r\n";
    size_t start = 0;

    // _vecBuffer.clear();
    // if (str.find(del) == std::string::npos)
    // {
    //     del = '\n';
    // }
    
    size_t end = str.find(del);

    while (end != std::string::npos)
    {
        _vecBuffer.push_back(str.substr(start, end - start));
        start = end + del.length();
        end = str.find(del, start);
    }
}
