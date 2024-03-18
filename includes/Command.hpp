#pragma once

#include "Client.hpp"
#include "IRC_Server.hpp"
#include <vector>
#include <map>

class Client;
class Command;
class IRC_Server;

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
        void CommandPING(Client *client);    // 3
        void CommandPONG(Client *client);    // 4
        void CommandCAP(Client *client);     // 5
        void CommandJOIN(Client *client);    // 6
        void commandPRIVMSG(Client *client); // 7
        void commandKICK(Client *client);    // 8
        void commandINVITE(Client *client);  // 9
        void commandMODE(Client *client);    // 10
        // void commandWHO(Client *client);     // 11
        void commandQUIT(Client *client);    // 12
        // void commandTOPIC(Client *client);   // 13
        // void commandPART(Client *client);    // 14


        void print_vector(std::vector<std::string> _vec);

    private:
        std::map<std::string, FUNC> _commands;
        IRC_Server *_server;
        std::vector<std::string> _args;
};


// void Command::CommandJOIN(Client *C)
// {
//     if (!C->isRegistered())
//     {
//         C->reply(ERR_NOTREGISTERED(C->getNICK()));
//         DEBUGGER();
//         return ;
//     }

//     if (_arg.empty())
//     {
//         C->reply(ERR_NEEDMOREPARAMS(C->getNICK(), "JOIN"));
//         DEBUGGER();
//         return ;
//     }

//     if (_arg[0] == "0")
//     {
//         C->leavingForChannels(NULL, "");
//         _server->checkForCloseCannel();
//         DEBUGGER();
//         return ;
//     }

//     DEBUGGER();
//     std::string channelName = _arg[0];
//     std::string pass = _arg.size() > 1 ? _arg[1] : "";

//     std::map<std::string, std::string> ch = stringToMap(channelName, pass);
//     for (std::map<std::string, std::string>::iterator it = ch.begin(); it != ch.end(); ++it)
//     {
//         channelName = it->first;
//         DEBUGGER();
//         pass = it->second;
//         if (channelName[0] != '#' && channelName[0] != '&')
//         {
//             C->reply(ERR_BADCHANMASK(C->getNICK(), channelName + static_cast<char>(1)));
//             DEBUGGER();
//             return ;
//         }
//         Channel* channel = _server->getChannel(channelName);
//         if (!channel)
//         {
//             channel = _server->createChannel(channelName, pass);
//             DEBUGGER();
//         }

//         if (channel->isInChannel(C))
//         {
//             C->reply(ERR_USERONCHANNEL(C->getNICK(), C->getNICK(), channelName + static_cast<char>(1)));
//             DEBUGGER();
//             return ;
//         }

//         if (channel->isInviteOnly())
//         {
//             C->reply(ERR_INVITEONLYCHAN(C->getNICK(), channelName + static_cast<char>(1)));
//             DEBUGGER();
//             return ;
//         }

//         if (channel->channelIsFull())
//         {
//             C->reply(ERR_CHANNELISFULL(C->getNICK(), channelName + static_cast<char>(1)));
//             DEBUGGER();
//             return ;
//         }

//         if (channel->getKey() != pass)
//         {
//             C->reply(ERR_BADCHANNELKEY(C->getNICK(), channelName, "Cannot join channel (+k)"));
//             DEBUGGER();
//             return ;
//         }
//         C->joinToChannel(channel);

        
//         DEBUGGER();
//     }
// }