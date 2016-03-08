#include "socketudp.hpp"

#define PORT 8888
#define PORT_REMOTO 8889



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

void request_cancellation(std::thread& thread){
        pthread_cancel(thread.native_handle());
}


Socket::Socket(const sockaddr_in& address){

        quit = false;
  
        fd = socket(AF_INET, SOCK_DGRAM, 0);
        if( fd < 0)
            throw std::system_error(errno, std::system_category(), "Fallo al crear el socket");

    
        sockaddr_in server = address;

        if( bind(fd, reinterpret_cast<const sockaddr*>(&server), sizeof(server)) < 0 )
            throw std::system_error(errno, std::system_category(), "Fallo en bind");
   
}

Socket::~Socket(){
    close(fd);
}


Socket& Socket::operator=(Socket&& s){
    fd = s.fd;
    quit = s.quit;
    s.fd = -1;
    return *this;
}

void Socket::send_to(const Message &message, const sockaddr_in& address){

    sockaddr_in server = address;

    int result;

    if( result = sendto(fd, &message, sizeof(message), 0, reinterpret_cast<sockaddr*>(&server), sizeof(server)) < 0 )
        throw std::system_error(errno, std::system_category(), "Fallo al enviar");


}


Message Socket::receive_from(const sockaddr_in& address){

        Message message;
        socklen_t slen;

        sockaddr_in server = address;
        slen = sizeof(server);

        if( (recvfrom(fd, &message, sizeof(message), 0, reinterpret_cast<sockaddr*>(&server), &slen)) < 0 )
           throw std::system_error(errno, std::system_category(), "Fallo al recibir");


        return message;
}


void Socket::mostrar(const Message& message, const sockaddr_in& address){

    char* remote_ip = inet_ntoa(address.sin_addr);
    int remote_port = ntohs(address.sin_port);

    std::cout << remote_ip << ":" << remote_port << " > " << message.text << std::endl;

}

void Socket::enviar_mensaje(const sockaddr_in& address){
  
    try{
        std::string linea="";
        while(!quit){
            
            Message message;
            memset(message.text, 0, sizeof(message.text));

            std::getline(std::cin, linea);
            if(linea == ":q")
            {
                quit = true;
                break;
                
            } 
            linea.copy(message.text, sizeof(message.text)-1, 0);
            
            send_to(message, address);
        }
    }  
    catch(std::system_error& e){
       std::cerr << "Error en el hilo" << std::endl;
       quit = true;
    }

}

void Socket::recibir_mensaje(const sockaddr_in& address){

    try{
        while(!quit){
            usleep(25000);
            mostrar(receive_from(address),address);
        }
    }
    catch(std::system_error& e)
    {
        std::cerr << "Error en el hilo" << std::endl;
        quit = true;
    }  
      
}






