#include "IRC_Server.hpp"
#include "utils.hpp"
#include <fcntl.h>

// #include <netinet/in.h>
// struct in_addr
// {
//     unsigned long s_addr;  // load with inet_aton()
// };

// struct sockaddr_in
// {
//     short            sin_family;   // e.g. AF_INET
//     unsigned short   sin_port;     // e.g. htons(3490)
//     struct in_addr   sin_addr;     // see struct in_addr, below
//     char             sin_zero[8];  // zero this if you want to
// };


IRC_Server::IRC_Server(const char *port, const char *password)
{
    this->_port = std::atoi(port);
    this->_password = password;
    _s_addr.sin_family = AF_INET;
    _s_addr.sin_port = htons(_port);
    _s_addr.sin_addr.s_addr = INADDR_ANY;

    this->_command = new Command(this);
}

IRC_Server::~IRC_Server(/* *this */)
{

}

std::string IRC_Server::getPASS(void)
{
    return (this->_password);
}

Client * IRC_Server::getClient(const std::string& nick) // TODO esim
{
    std::map<std::string, Channel*>::iterator it = this->_channels.find(nick);
    if (it != this->_channels.end())
    {
        std::cout << "lala" << std::endl;
        // return (it->second);  // TODO
    }
    return NULL;
}


void IRC_Server::addChannel(Channel *channel)
{

    if (this->_channels.insert(std::make_pair(channel->_name, channel)).second == false)
    {
        std::cout << "alredy exist\n";
    }
}

void IRC_Server::addClientToChannel(const std::string& name, Client *client)
{
    std::map<std::string, Channel *>::iterator  it = this->_channels.find(name);
    if (it != this->_channels.end())
    {
        it->second->joinClient(client);
    }
}


// Channel* Server::createChannel(const std::string& name, const std::string& pass)
// {
//     Channel *new_channel = new Channel(name, pass);
//     this->_channels.insert(new_channel);
//     return (new_channel);
// }

// server mekic aveli clientneri hamar

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int IRC_Server::start(void)
{
    fd_set master;    // master file descriptor list
    fd_set read_fds;  // temp file descriptor list for select()
    // int _fdmax;        // maximum file descriptor number

    // int listener;     // listening socket descriptor
    // int _newfd;        // newly accept()ed socket descriptor
    struct sockaddr remoteaddr; // client address
    socklen_t addrlen;

    char buf[256];    // buffer for client data
    int nbytes;

    // char remoteIP[INET6_ADDRSTRLEN];

    int yes = 1;        // for setsockopt() SO_REUSEADDR, below
    // int i, j, rv;
     // reference Client(Server) ++this->_clients
    int rv;

    struct addrinfo hints, *ai, *p;

    FD_ZERO(&master);    // clear the master and temp sets
    FD_ZERO(&read_fds);

    // get us a socket and bind it
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    if ((rv = getaddrinfo(NULL, my_to_string(this->_port).c_str(), &hints, &ai)) != 0)
    {
        fprintf(stderr, "selectserver: %s\n", gai_strerror(rv));
        exit(1);
    }
    
    for(p = ai; p != NULL; p = p->ai_next) 
    {
        this->_listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (this->_listener < 0) 
        {
            continue;
        }
        
        // lose the pesky "address already in use" error message
        setsockopt(this->_listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

        if (bind(this->_listener, p->ai_addr, p->ai_addrlen) < 0) 
        {
            perror("bind: ");
            close(this->_listener);
            continue;
        }

        break;
    }

    // if we got here, it means we didn't get bound
    if (p == NULL) 
    {
        fprintf(stderr, "selectserver: failed to bind\n");
        exit(2);
    }

    freeaddrinfo(ai); // all done with this

    // listen
    if (listen(this->_listener, 0) == -1)
    {
        perror("listen");
        exit(3);
    }

    // add the listener to the master set
    FD_SET(this->_listener, &master);

    // keep track of the biggest file descriptor
    this->_fdmax = this->_listener + 1; // so far, it's this one

    // main loop
    this->addChannel(new Channel("name"));
    for(;;) 
    {
        read_fds = master; // copy it
        // _max_fd = _clients.rbegin()->first + 1;
        _select_fd = select(_fdmax, &read_fds, NULL, NULL, NULL);
        if (_select_fd == -1)
        {
            std::cout << "stex select" << std::endl;
            perror("select");
            exit(4);
        }
        else if (_select_fd)
        {
            // run through the existing connections looking for data to read
            if (FD_ISSET(this->_listener, &read_fds)) 
            { 
                // we got one!!
                    // TODO erb avelanum em nor clientner, miacnum enq serverin
                    // handle new connections

                addrlen = sizeof remoteaddr;
                _newfd = accept(this->_listener,
                    (struct sockaddr *)&remoteaddr,
                    &addrlen);

                if (_newfd == -1)
                {
                    perror("accept");
                }
                else if (_newfd)
                {
                    std::cout << "client connect" << std::endl;
                    if (fcntl(this->_listener, F_SETFL, O_NONBLOCK) == -1)
                    {
                        close(this->_listener);
                        std::cout << "Error: setting client fd to non-blocking mode failed!" << std::endl;
                    }

                    FD_SET(_newfd, &master);
                        // add to master set
                    if (_newfd >= _fdmax) 
                    {    // keep track of the max
                        _fdmax = _newfd + 1;
                    }
                    Client* tmp = new Client(_newfd, remoteaddr);
                    this->_clients[_newfd] = tmp;  // adding client to server
                    // this->addChannel()
                    // this->addClientToChannel("name", tmp); // TODO porcnakan
                    std::cout << "new Client(_newfd, remoteaddr); = " << _newfd << std::endl;
                }
            }
            for(std::map<int, Client *>::iterator it = this->_clients.begin();
                   _select_fd != 0 && it != this->_clients.end() ; ++it)
            {
                // std::cout << "loop" << std::endl;
                if (FD_ISSET(it->first, &read_fds)) 
                {
                    _select_fd--;
                    // we got one!!
                    // handle data from a client
                    if ((nbytes = recv(it->first, buf, sizeof buf, 0)) <= 0)
                    {
                        // TODO heracnel clientin ir irer@ evs
                        // got error or connection closed by client
                        if (nbytes == 0)
                        {
                            // connection closed
                            printf("selectserver: socket %d hung up\n", it->first);
                        } 
                        else
                        {
                            perror("recv");
                        }

                        close(it->first); // bye!
                        FD_CLR(it->first, &master); // remove from master set
                    } 
                    else
                    {
                        std::cout << "sending message" << std::endl;
                        int i = 0;
                        while(buf[i])
                        {
                            it->second->_buffer += buf[i];
                            // std::cout << " it->second->_buffer "<< it->second->_buffer << std::endl;
                            i++; 
                        }

                        if (it->second->_buffer.find('\n') != std::string::npos)
                        {
                            // it->second->setInputBuffer(it->second->_buffer);//TODO kaskaceli => veranayel
                            it->second->splitbuffer();
                            it->second->setArguments();
                            while (!it->second->getArguments().empty() || !it->second->getCommand().empty())
                            {
                                // std::cout << "face :D" << std::endl;
                                this->_command->commandHandler(it->second);
                                it->second->setArguments();
                                // exit(1);
                                // std::cout << "return " << std::endl;
                            }

                        }



                // if (it->second->_tmpBuffer.find('\n') != std::string::npos)
                // {
                //     it->second->setInputBuffer(it->second->_tmpBuffer);
                //     it->second->splitBufferToList();
                //     it->second->setArguments();
                //     while (!it->second->getArguments().empty() || !it->second->getCommand().empty())
                //     {
                //         _command->commandHandler(it->second);
                //         it->second->setArguments();
                //     }
                //     it->second->_tmpBuffer = "";
                // }





                        // we got some data from a client
                        //TODO parsing anel clienti uxarkac@
                        // TODO 
                    //     for(j = 0; j <= _fdmax; j++)
                    //     {
                    //         // if (ete inch vor Channei-i mej a)
                    //         // {
                    //             {
                    //                 // send to everyone!
                    //                 if (FD_ISSET(j, &master))
                    //                 {
                    //                     // auto it = this->_clients.find(j);
                    //                     // if (it != _clients.end())
                    //                     // {
                    //                     //     std::string channelName = "name"; 
                    //                     //     it->second
                    //                     // }
                    //                     // except the listener and ourselves
                    //                     if (j != this->_listener && j != i)
                    //                     {
                    //                         if (send(j, buf, nbytes, 0) == -1) 
                    //                         {
                    //                             std::cout << "stex send" << std::endl;
                    //                             perror("send");
                    //                         }
                    //                         // std::cout<< "lalala\n";
                    //                     }
                    //                 }
                    //             } 
                    //         // }
                    }
                }
                    // _select_fd--;
                // TODO  if (FD_ISSET(it->first, &write_fds)) _select_fd--
            }
        }
    }
    return 0;
}