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

    
        fd = socket(AF_INET, SOCK_DGRAM, 0);
        if( fd < 0)
            throw std::system_error(errno, std::system_category(), "Fallo al crear el socket");
        else
            std::cout << "Socket creado\n";
    
  

        sockaddr_in server = address;

        if( bind(fd, reinterpret_cast<const sockaddr*>(&server), sizeof(server)) < 0 )
            throw std::system_error(errno, std::system_category(), "Fallo en bind");
        else
            std::cout << "Bind establecido\n";
  



}

Socket::~Socket(){
    close(fd);
}



void Socket::send_to(const Message& message, const sockaddr_in& address){

    sockaddr_in server = address;

    int result;
    if( result = sendto(fd, &message, sizeof(message), 0, reinterpret_cast<sockaddr*>(&server), sizeof(server)) < 0 )
        std::cerr << "Fallo al enviar: " << std::strerror(errno) << std::endl;


}


Message Socket::receive_from(const sockaddr_in& address){

    Message message;
    socklen_t slen;

    sockaddr_in server = address;

    slen = sizeof(server);

    if( (recvfrom(fd, &message, sizeof(message), 0, reinterpret_cast<sockaddr*>(&server), &slen)) < 0 )
        std::cerr << "Fallo al recibir" << std::strerror(errno) << std::endl;

    return message;
}

void Socket::mostrar(const Message& message, const sockaddr_in& address){

    char* remote_ip = inet_ntoa(address.sin_addr);
    int remote_port = ntohs(address.sin_port);

    std::cout << remote_ip << ":" << remote_port << " > " << message.text << std::endl;
}










