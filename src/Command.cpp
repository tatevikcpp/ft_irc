#include "Command.hpp"
#include "Numeric_and_error_replies.hpp"

Command::Command(IRC_Server *server) : _server(server)
{
    FUNC f[] = {&Command::commandPASS, &Command::commandNICK,       // 0, 1
                 &Command::commandUSER, &Command::CommandPING,      // 2, 3
                 &Command::CommandPONG, &Command::CommandCAP /*,       // 4, 5
                 &Command::CommandJOIN, &Command::commandPRIVMSG,   // 6, 7
                 &Command::commandKICK, &Command::commandINVITE,    // 8, 9
                 &Command::commandMODE, &Command::commandWHO,       // 10, 11
                 &Command::commandQUIT, &Command::commandTOPIC,     // 12, 13
                 &Command::commandPART */};                             // 14

    // _commands.insert(std::make_pair("", f[]));
    _commands["PASS"] = f[0];
    _commands.insert(std::make_pair("PASS", f[0]));
    _commands.insert(std::make_pair("NICK", f[1]));
    _commands.insert(std::make_pair("USER", f[2]));
    _commands.insert(std::make_pair("PING", f[3]));
    _commands.insert(std::make_pair("PONG", f[4]));
    _commands.insert(std::make_pair("CAP",  f[5]));
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

//print vector

void Command::print_vector(std::vector<std::string> _vec)
{
    if (!_vec.empty())
    {
        std::vector<std::string>::iterator it = _vec.begin();
        for (; it != _vec.end(); ++it)
            std::cout << *it << " " << std::endl;
    }
    else
        std::cout << "vector is empty" << std::endl;
}

Command::~Command()
{

}

void Command::commandHandler(Client* client)
{
    // print_vector(client->getArguments());
    this->_args = client->getArguments();
    // std::cout << std::endl;
    std::string cmd = client->getCommand();
    std::map<std::string, FUNC>::iterator it = this->_commands.begin();
    for( ; it != this->_commands.end(); ++it)
    {
        if (it->first == cmd)
        {
            // std::cout << "cmd = " << cmd << std::endl;
            (this->*_commands[it->first])(client);
            return ;
        }
    }
    client->reply(ERR_UNKNOWNCOMMAND(client->getNICK(), client->getCommand()));
}

void Command::CommandCAP(Client *client)
{
    (void)*client;
}

void Command::CommandPING(Client *client) // TODO
{
    if (_args.empty())
    {
        (void)*client;
        client->reply(ERR_NEEDMOREPARAMS(client->getNICK(), "PING"));
        // DEBUGGER();
        return ;
    }
    // client->sending(RPL_PING(C->getPrefix(), _arg[0]));
}


void Command::CommandPONG(Client *client) //TODO
{
    if (_args.empty())
    {
        (void)*client;
        client->reply(ERR_NEEDMOREPARAMS(client->getNICK(), "PONG"));
        // DEBUGGER();
        return ;
    }
    // client->sending(RPL_PING(client->getPrefix(), _arg[0]));
}

void Command::commandPASS(Client* client) //TODO kisat
{
    this->_args = client->getArguments();
    if (_args.empty())
    {
        client->reply(ERR_NEEDMOREPARAMS(client->getNICK(), "PASS"));
        return ;
    }

    std::string password = this->_args[0];
    if (password != _server->getPASS())
    {
        // std::cout << "NOT correct password" << std::endl;
        // exit(1);
        client->reply(ERR_PASSWDMISMATCH (client->getNICK()));
        return ;
    }
    // std::cout << "correct password" << std::endl;
    client->setPASS(password); //TODO indz petq a ardyoq ?
}

void Command::commandNICK(Client* client)
{
    this->_args = client->getArguments();
    if (_args.empty())
    {
        client->reply(ERR_NONICKNAMEGIVEN(client->getNICK()));
        return ;
    }
    std::string nick = _args[0];
    // std::cout << "nik: " << nick << std::endl;

    Client* Client = _server->getClient(nick);
    if (Client == NULL)
    {
        client->reply(ERR_NICKNAMEINUSE(client->getNICK(), nick));
        return ;
    }
    (void)*client;
    // client->setNICK(nick);
}


void Command::commandUSER(Client *client)
{
    if (client->isRegistered())
    {
        // client->reply(ERR_ALREADYREGISTERED(client->getNICK()));
        return ;
    }
    if (_args.size() < 4)
    {
        // client->reply(ERR_NEEDMOREPARAMS(client->getNICK(), "USER"));
        return ;
    }
    client->setUSER(_args[0], _args[3]);
}

// void Command::CommandJOIN(Client *client)
// {
//     if (!client->isRegistered())
//     {
//         // client->reply(ERR_NOTREGISTERED(client->getNICK()));
//         return ;
//     }

//     if (_args.empty())
//     {
//         // client->reply(ERR_NEEDMOREPARAMS(client->getNICK(), "JOIN"));
//         return ;
//     }

//     //eli inch vor baner :D
    
// }