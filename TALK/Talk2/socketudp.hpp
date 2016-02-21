#include <iostream>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <cerrno>


struct Message{
    char text[1024];
};

class Socket{

    private:
        int fd;

    public:
        Socket();
        ~Socket();
        void send_to(Message& message, const sockaddr_in& address);
        void receive_from(Message& message_, const sockaddr_in& address);


};

sockaddr_in make_ip_address( std::string ip_address, int port );
