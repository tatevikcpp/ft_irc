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
        void joinClient(Client *client);
        bool isInChannel(Client* client);
        bool isOperator(Client* client);
        void sending(Client* C, const std::string& msg, const std::string& cmd);
        void addOperator(Clinet *clinet);
        bool channelIsFull(void);
        bool emptyChannel(void);
        

    private:
        std::map<int, Client *> _client;
        std::string _name;
};