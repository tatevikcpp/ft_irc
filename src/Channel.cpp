#include "Channel.hpp"

Channel::Channel(const std::string& name, const std::string& pass) : _name(name), _pass(pass)
{
//     this->_name = name;
//     this->_pass = pass;
}

Channel::~Channel()
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