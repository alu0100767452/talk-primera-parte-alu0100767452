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
#include <csignal>
#include <signal.h>
#include <vector>



typedef void (*sighandler_t) (int);



struct Message{
    char text[1024];
    sockaddr_in dir_origen;
    char usuario[30];
};

struct ADDRESS{
    std::string sin_addr;
    int port;
};

struct Message_AD{
    Message m;
    sockaddr_in address;
};

class Socket{

    private:
        int fd;
         
        bool ini = false;
        sockaddr_in d_origen; 
        std::string username; 
        std::vector<sockaddr_in> clientes;
        bool servidor = false; //False = Cliente, True = Servidor

    public:
bool quit;
        Socket(): fd(-1){};
        Socket(const sockaddr_in& address, bool server_client, std::string user);
        ~Socket();


        Socket& operator=(Socket&& s);
        void send_to(const Message& message, const sockaddr_in& address);
        Message receive_from(const sockaddr_in& address);
        void mostrar(const Message& message, const sockaddr_in& address);
        void enviar_mensaje(const sockaddr_in& address);
        void recibir_mensaje(const sockaddr_in& address);
         
        void setQuit(bool set){ quit = set;};
       
        

};


sockaddr_in make_ip_address( std::string ip_address, int port );
void request_cancellation(std::thread& thread);
sighandler_t signal(int signum, sighandler_t handler);
void signal_handler(int signum);
