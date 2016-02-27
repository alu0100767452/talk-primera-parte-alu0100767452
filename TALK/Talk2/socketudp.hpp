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
#include <exception>
#include <system_error>
#include <thread>


struct Message{
    char text[1024];
};

class Socket{

    private:
        int fd;

    public:
        Socket(const sockaddr_in& address);
        ~Socket();
        void send_to(const Message& message, const sockaddr_in& address);
        Message receive_from(const sockaddr_in& address);
        void mostrar(const Message& message, const sockaddr_in& address);

};

sockaddr_in make_ip_address( std::string ip_address, int port );
