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
    enum TypeClient
    {
        Owner,
        Operator,
        Primary
    };
    public:

        Client(int fd, const struct sockaddr& addr);
        ~Client();


        const int _fd;
        void leaveChannel(const std::string& name);
        Channel* createChannel(const std::string& name, const std::string& pass = "");
        // void sending(const std::string& message);
        // void reply(const std::string& message);
        bool isRegistered(void);
        std::string getNick(void);
        void setNick(const std::string& nick);
        void setPASS(const std::string& pass);
        void setUSER(const std::string& username, const std::string& realname);
        void checkForRegistered(void);
        void splitbuffer(void);

        void setArguments(void);
        
        std::string _buffer;

    private:

        // std::string _port;
        struct sockaddr _clientAddr;
        // std::map<std::string, Channel*> _channels;
        std::map<std::string, std::pair<Channel*, TypeClient> > _channels;


        std::string _pass;
        std::string _nick;
        std::string _username;
        std::string _hostname;
        std::string _realname;

        std::vector<std::string> _arguments;
        std::list<std::string> _bufferlist; // or std::vector<std::string> _buffervec

        bool _registered;
};