#include <iostream>
#include <vector>
#include <list>
#include "IRC_Server.hpp"

class IRC_Server;

class Client
{
    public:
        Client(int fd, const struct sockaddr_in& addr , TypeClient = 1);
        ~Client();

        enum TypeClient
        {
            Operator,
            Primary
        };

        const int _fd
        void joinToChannel(Channel *channel);
        void leavingChannels(Channel *channel /*,  lalala */);
        void sending(const std::string& message);
        void reply(const std::string& message);
        void bufferToList(void);
        
    private:

        std::string _port;
        struct sockaddr_in _clientAddr;
        Channel* _channels;

        std::string _pass;
        std::string _nick;
        std::string _username;
        std::string _hostname;
        std::string _realname;
        std::string _buffer;
        // TypeClient _clientType;

        std::vector<std::string> _arguments;
        std::List<std::string> _bufferlist;
};