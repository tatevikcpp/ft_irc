#include "Channel.hpp"

Channel::Channel(const std::string& name)
{
    this->_name = name;
}

~Channel()
{

}

void Channel::addClient(Client &client)
{
    this->_client[client._fd] = &client;
}

void Channel::deleteClient(int client_fd)
{
    this->_client.erase(client_fd);
}