#include <iostream>
#include "Client.hpp"
#include "Channel.hpp"


// esim e

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <map>


#define PORT "9034"   // port we're listening on

// senc eli

class IRC_Server
{
    public:
        // IRC_Server(const std::string& v1, const std::string& v2);
        IRC_Server(const char *port, const char *password);
        ~IRC_Server();
        // void initStruct(void);

    private:
        unsigned short _port;
        std::string _password;
        struct sockaddr_in _s_addr;
        std::map<int, Channel *> _channels;
        std::map<int, Client *> _clients;

};