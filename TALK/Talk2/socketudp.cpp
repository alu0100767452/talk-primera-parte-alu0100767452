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

Socket::Socket(){

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if( fd < 0)
        puts("Fallo al crear el socket");
    else
        std::cout << "Socket creado";

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY; //inet_addr("172.0.0.2");
    server.sin_port = htons( PORT );

    if( bind(fd, (struct sockaddr *)&server, sizeof(server)) < 0 )
        puts("Error en bind");
    else
        puts("Bind establecido");



}

Socket::~Socket(){
    close(fd);
}



void Socket::send_to(const Message& message, const sockaddr_in& address){



    sockaddr_in server = address;
    socklen_t alen = sizeof(server);

    
    int result;
    if( result = sendto(fd, &message, sizeof(message), 0, (struct sockaddr *)&server, sizeof(server)) < 0 )
        puts("Fallo al enviar.");

}


void Socket::receive_from(Message& message_, const sockaddr_in& address){

    Message message;
    socklen_t slen;

    sockaddr_in server = address;


    slen = sizeof(server);

    if( (recvfrom(fd, &message, sizeof(message), 0, (struct sockaddr *) &server, &slen)) < 0 )
        puts("Fallo al recibir");



    char* remote_ip = inet_ntoa(server.sin_addr);
    int remote_port = ntohs(server.sin_port);

    message.text[1023] = '\0';
    std::cout << remote_ip << ":" << remote_port << " > " << message.text << std::endl;

}











