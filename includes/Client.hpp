#pragma once

#include <iostream>
#include <vector>
#include <list>
#include "IRC_Server.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <map>
class IRC_Server;
class Channel;
class Client
{
    public:

        Client(int fd, const struct sockaddr& addr);
        ~Client();


        const int _fd;
        void joinToChannel(Channel *channel);
        void leavingChannels(Channel *channel);
        void sending(const std::string& message);
        void reply(const std::string& message);
        void bufferToList(void);
        
    private:

        // std::string _port;
        struct sockaddr _clientAddr;
        std::map<int, Channel*> _channels;


        std::string _pass;
        std::string _nick;
        std::string _username;
        std::string _hostname;
        std::string _realname;
        std::string _buffer;

        std::vector<std::string> _arguments;
        std::list<std::string> _bufferlist;
};