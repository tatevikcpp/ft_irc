#include "Command.hpp"

Command::Command(/* Server *server */) /* : _server(server) */
{
    // FUNC f[] = {&Command::commandPASS, &Command::commandNICK,       // 0, 1
    //              &Command::commandUSER, &Command::CommandPING,      // 2, 3
    //              &Command::CommandPONG, &Command::CommandCAP,       // 4, 5
    //              &Command::CommandJOIN, &Command::commandPRIVMSG,   // 6, 7
    //              &Command::commandKICK, &Command::commandINVITE,    // 8, 9
    //              &Command::commandMODE, &Command::commandWHO,       // 10, 11
    //              &Command::commandQUIT, &Command::commandTOPIC,     // 12, 13
    //              &Command::commandPART};                             // 14

    // _commands.insert(std::make_pair("", f[]));
    // _commands["PASS"] = f[0];
    // _commands.insert(std::make_pair("PASS", f[0]));
    // _commands.insert(std::make_pair("NICK", f[1]));
    // _commands.insert(std::make_pair("USER", f[2]));
    // _commands.insert(std::make_pair("PING", f[3]));
    // _commands.insert(std::make_pair("PONG", f[4]));
    // _commands.insert(std::make_pair("CAP",  f[5]));
    // _commands.insert(std::make_pair("JOIN",  f[6]));
    // _commands.insert(std::make_pair("PRIVMSG", f[7]));
    // _commands.insert(std::make_pair("KICK", f[8]));
    // _commands.insert(std::make_pair("INVITE", f[9]));
    // _commands.insert(std::make_pair("MODE", f[10]));
    // _commands.insert(std::make_pair("WHO", f[11]));
    // _commands.insert(std::make_pair("QUIT", f[12]));
    // _commands.insert(std::make_pair("TOPIC", f[13]));
    // _commands.insert(std::make_pair("PART", f[14]));
}


Command::~Command()
{

}

void Command::commandPASS(Client* client)
{
    if (_args.empty())
    {
        // ERR_NEEDMOREPARAMS(C->getNICK(), "PASS");
        return ;
    }

    std::string password = _arg[0];

    if (password != _server->getPASS())
    {
        // ERR_PASSWDMISMATCH (C->getNICK());
        return ;
    }
    client->setPASS(password);
}

void Command::commandNICK(Client* client)
{
    if (_arg.empty())
    {
        // ERR_NONICKNAMEGIVEN(C->getNICK());
        return ;
    }
    std::string nick = _arg[0];

    Client* client = _server->getClient(nick);
    if (client == NULL)
    {
        // ERR_NICKNAMEINUSE(C->getNICK(), nick);
        return ;
    }
    client->setNICK(nick);
}


void Command::commandUSER(Client *client)
{
    if (client->isRegistered())
    {
        // ERR_ALREADYREGISTERED(C->getNICK());
        return ;
    }
    if (_arg.size() < 4)
    {
        // ERR_NEEDMOREPARAMS(C->getNICK(), "USER");
        return ;
    }
    client->setUSER(_args[0], _args[3]);
}

void Command::CommandJOIN(Client *client)
{
    
}