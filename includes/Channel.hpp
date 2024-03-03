#pragma once
#include <iostream>
#include "Client.hpp"
#include <map>
#include <set>

class Client;
class Channel
{
    public:
        Channel(const std::string& name, const std::string& pass);
        ~Channel();

        void addClient(Client &client);
        void deleteClient(int client_fd);
        void joinClient(Client *client);
        bool isInChannel(Client* client);
        bool isOperator(Client* client);
        void sending(Client* C, const std::string& msg, const std::string& cmd);
        void addOperator(Client *clinet);
        bool channelIsFull(void);
        bool emptyChannel(void);
        

    private:
        std::map<int, Client *> _client;
        std::set<std::string> _admins;
        std::string _name;
        std::string _pass;
};