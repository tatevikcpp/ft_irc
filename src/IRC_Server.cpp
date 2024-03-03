#include "IRC_Server.hpp"
#include "utils.hpp"

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
}

IRC_Server::~IRC_Server()
{

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
    int fdmax;        // maximum file descriptor number

    int listener;     // listening socket descriptor
    int newfd;        // newly accept()ed socket descriptor
    struct sockaddr remoteaddr; // client address
    socklen_t addrlen;

    char buf[256];    // buffer for client data
    int nbytes;

    // char remoteIP[INET6_ADDRSTRLEN];

    int yes = 1;        // for setsockopt() SO_REUSEADDR, below
    int i, j, rv;

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
        listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (listener < 0) 
        { 
            continue;
        }
        
        // lose the pesky "address already in use" error message
        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

        if (bind(listener, p->ai_addr, p->ai_addrlen) < 0) 
        {
            close(listener);
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
    if (listen(listener, 0) == -1)
    {
        perror("listen");
        exit(3);
    }

    // add the listener to the master set
    FD_SET(listener, &master);

    // keep track of the biggest file descriptor
    fdmax = listener; // so far, it's this one

    // main loop
    this->addChannel(new Channel("name"));
    for(;;) 
    {
        read_fds = master; // copy it
        if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) 
        {
            perror("select");
            exit(4);
        }

        // run through the existing connections looking for data to read
        for(i = 0; i <= fdmax; i++) 
        {
            if (FD_ISSET(i, &read_fds)) 
            { // we got one!!
                if (i == listener) 
                {
                    // TODO erb avelanum em nor clientner, miacnum enq serverin
                    // handle new connections

                    addrlen = sizeof remoteaddr;
                    newfd = accept(listener,
                        (struct sockaddr *)&remoteaddr,
                        &addrlen);

                    if (newfd == -1) 
                    {
                        perror("accept");
                    }
                    else 
                    {
                        FD_SET(newfd, &master); // add to master set
                        if (newfd > fdmax) {    // keep track of the max
                            fdmax = newfd;
                        }
                        Client* tmp = new Client(newfd, remoteaddr);
                        this->_clients[newfd] = tmp;
                        // this->addChannel()
                        this->addClientToChannel("name", tmp); // TODO porcnakan
                        std::cout << "new Client(newfd, remoteaddr); = " << newfd << std::endl;
                    }
                }
                else
                {
                    // handle data from a client
                    if ((nbytes = recv(i, buf, sizeof buf, 0)) <= 0)
                    {
                        // TODO heracnel clientin ir irer@ evs
                        // got error or connection closed by client
                        if (nbytes == 0)
                        {
                            // connection closed
                            printf("selectserver: socket %d hung up\n", i);
                        } 
                        else 
                        {
                            perror("recv");
                        }
                        close(i); // bye!
                        FD_CLR(i, &master); // remove from master set
                    } 
                    else 
                    {
                        // we got some data from a client
                        //TODO parsing anel clienti uxarkac@
                        for(j = 0; j <= fdmax; j++)
                        {
                            // if (ete inch vor Channei-i mej a)
                            // {
                                {
                                    // send to everyone!
                                    if (FD_ISSET(j, &master))
                                    {
                                        // auto it = this->_clients.find(j);
                                        // if (it != _clients.end())
                                        // {
                                        //     std::string channelName = "name"; 
                                        //     it->second
                                        // }
                                        // except the listener and ourselves
                                        if (j != listener && j != i)
                                        {
                                            if (send(j, buf, nbytes, 0) == -1) 
                                            {
                                                perror("send");
                                            }
                                        }
                                    }
                                } 
                            // }
                        }
                    }
                }
            }
        }
    }
    return 0;
}