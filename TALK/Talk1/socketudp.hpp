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
#include <pthread.h>
#include <atomic>
#include <cxxabi.h>

struct Message{
    char text[1024];
};

class Socket{

    private:
        int fd;
        bool quit;     

    public:

        Socket(): fd(-1){};
        Socket(const sockaddr_in& address);
        ~Socket();
        Socket& operator=(Socket&& s);
        void send_to(const Message& message, const sockaddr_in& address);
        Message receive_from(const sockaddr_in& address);
        void mostrar(const Message& message, const sockaddr_in& address);
        void enviar_mensaje(const sockaddr_in& address);
        void recibir_mensaje(const sockaddr_in& address);
         


};

sockaddr_in make_ip_address( std::string ip_address, int port );
void request_cancellation(std::thread& thread);
