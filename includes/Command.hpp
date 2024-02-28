#pragma once
#include "Client.hpp"
#include "IRC_Server.hpp"


class Command
{
    public:
        Command();
        ~Command();


        void commandHandler(Client* C);
        
        void commandNICK(Client* C);    // 0
        void commandPASS(Client* C);    // 1
        void commandUSER(Client *C);    // 2
        // void CommandPING(Client *C);    // 3
        // void CommandPONG(Client *C);    // 4
        // void CommandCAP(Client *C);     // 5
        void CommandJOIN(Client *C);    // 6
        void commandPRIVMSG(Client *C); // 7
        void commandKICK(Client *C);    // 8
        void commandINVITE(Client *C);  // 9
        void commandMODE(Client *C);    // 10
        // void commandWHO(Client *C);     // 11
        void commandQUIT(Client *C);    // 12
        // void commandTOPIC(Client *C);   // 13
        // void commandPART(Client *C);    // 14

    private:
        std::map<std::string, func> _commands;
        // IRC_Server *_server;
};