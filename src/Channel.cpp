#include "Channel.hpp"

Channel::Channel(const std::string& name, Client *client, const std::string& pass) : _name(name), _pass(pass)
{
    if (client)
        this->joinClient(client);
//     this->_name = name;
//     this->_pass = pass;
}

Channel::~Channel()
{

}

void Channel::joinClient(Client *client)
{
    this->_client[client->_fd] = client;
}

void Channel::deleteClient(Client &client)
{
    this->_client.erase(client._fd);
}

void Channel::sending(Client* C, const std::string& msg/* , const std::string& cmd */)
{
    std::map<int, Client *>::const_iterator it = this->_client.cbegin(); // TODO nayel !!

    while (it != this->_client.cend())
    {
        if (C->_fd != it->first)
        {
            if (send(it->first, msg.c_str(), msg.size(), 0) == -1)
            {

            }
        }
        it++;
    }
}
