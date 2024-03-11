#pragma once
#include "Client.hpp"
#include "IRC_Server.hpp"
#include <vector>

class Command;
typedef void (Command::*FUNC)(Client* client);

class Command
{
    public:
        Command();
        ~Command();


        void commandHandler(Client* client);
        
        void commandNICK(Client* client);    // 0
        void commandPASS(Client* client);    // 1
        void commandUSER(Client *client);    // 2
        // void CommandPING(Client *client);    // 3
        // void CommandPONG(Client *client);    // 4
        // void CommandCAP(Client *client);     // 5
        void CommandJOIN(Client *client);    // 6
        void commandPRIVMSG(Client *client); // 7
        void commandKICK(Client *client);    // 8
        void commandINVITE(Client *client);  // 9
        void commandMODE(Client *client);    // 10
        // void commandWHO(Client *client);     // 11
        void commandQUIT(Client *client);    // 12
        // void commandTOPIC(Client *client);   // 13
        // void commandPART(Client *client);    // 14

    private:
        std::map<std::string, FUNC> _commands;
        IRC_Server *_server;
        std::vector<std::string> _args;
};