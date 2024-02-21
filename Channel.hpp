#include <iostream>
#include "Client.hpp"
#include <map>

class Channel
{
    public:
        Channel(const std::string& name);
        ~Channel();

        void addClient(Client &client);
        void deleteClient(int client_fd);
        

    private:
        std::map<int, Client *> _client;
        std::string _name;
};