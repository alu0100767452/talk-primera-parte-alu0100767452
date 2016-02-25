#include "socketudp.hpp"

#define PORT 8889
#define PORT_REMOTO 8888



sockaddr_in make_ip_address( std::string ip_address, int port ){

    sockaddr_in server;
    server.sin_family = AF_INET;
    if( ip_address == "" )
        server.sin_addr.s_addr = INADDR_ANY;
    else
        server.sin_addr.s_addr = inet_addr( ip_address.c_str() );
    server.sin_port = htons( port );

    return server;

}

Socket::Socket(const sockaddr_in& address){

    try{
        fd = socket(AF_INET, SOCK_DGRAM, 0);
        if( fd < 0)
            throw 1;
        else
            std::cout << "Socket creado\n";
    }
    catch(int error){
        std::system_error(errno, std::system_category(), "Fallo al crear el socket");
    }

    try{
        sockaddr_in server = address;

        if( bind(fd, reinterpret_cast<const sockaddr*>(&server), sizeof(server)) < 0 )
            throw 1;
        else
            puts("Bind establecido\n");
    }
    catch(int e){
        std::system_error(errno, std::system_category(), "Fallo en bind");
    }    




}

Socket::~Socket(){
    close(fd);
}



void Socket::send_to(Message& message, const sockaddr_in& address){

    sockaddr_in server = address;

    int result;
    if( result = sendto(fd, &message, sizeof(message), 0, reinterpret_cast<sockaddr*>(&server), sizeof(server)) < 0 )
        std::cerr << "Fallo al enviar: " << std::strerror(errno) << std::endl;

    memset(message.text, 0, sizeof(message.text));

}


void Socket::receive_from(Message& message_, const sockaddr_in& address){

    Message message;
    socklen_t slen;

    sockaddr_in server = address;

    slen = sizeof(server);

    if( (recvfrom(fd, &message, sizeof(message), 0, reinterpret_cast<sockaddr*>(&server), &slen)) < 0 )
        std::cerr << "Fallo al recibir" << std::strerror(errno) << std::endl;


    char* remote_ip = inet_ntoa(server.sin_addr);
    int remote_port = ntohs(server.sin_port);

    message.text[1023] = '\0';
    std::cout << remote_ip << ":" << remote_port << " > " << message.text << std::endl;


}











