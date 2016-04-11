#include "socketudp.hpp"

#define PORT 8888
#define PORT_REMOTO 8889

std::atomic<bool> q(false);
sigset_t set;

std::vector<sockaddr_in> eliminar_repetidos(std::vector<sockaddr_in> vector){

    sockaddr_in ele;
    std::vector<sockaddr_in> v_aux;
    std::vector<sockaddr_in> v_final;
    int cont,i,k, j=0, z=0;
    int n = vector.size();

        
            for (i=0;i<vector.size();i++) {
                    cont=0;
                    ele=vector[i];
                    v_aux.push_back(ele);
                    for (k=0;k<vector.size();k++)
                            if ( v_aux[k].sin_addr.s_addr == ele.sin_addr.s_addr )
                                    cont++;

                    if ( cont == 1 ) {
                            v_final.push_back(ele);
                    }
            }

        return v_final;
}


void  signal_handler(int signum){
    switch(signum){
        case SIGINT:
            std::cout << "Desconectando..." << std::endl;
            q = true;
            break;
        case SIGTERM:
            std::cout << "Desconectando..." << std::endl;
            q = true;
            break;
        case SIGHUP:
            std::cout << "Desconectando..." << std::endl;
            q = true;
            break;
        default: break;
    }
}


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


Socket::Socket(const sockaddr_in& address, bool server_client, std::string user){

        quit = false;
        servidor = server_client;
        d_origen = address;
        username = user;

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
    servidor = s.servidor;
    username = s.username;
    d_origen = s.d_origen;
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


        if(servidor){

            clientes.push_back(message.dir_origen);
            clientes = eliminar_repetidos(clientes);

           //ENVIO DEL MENSAJE A TODOS LOS CLIENTES
           for(int i=0; i<clientes.size(); i++){
                if(clientes[i].sin_addr.s_addr != message.dir_origen.sin_addr.s_addr)
                    send_to(message, clientes[i]);
           }
        }


        return message;
}


void Socket::mostrar(const Message& message, const sockaddr_in& address){

    //char* remote_ip = inet_ntoa(message.dir_origen.sin_addr);
    //int remote_port = ntohs(message.dir_origen.sin_port);

    //std::cout << remote_ip << ":" << remote_port << " > " << message.text << std::endl;
    std::cout << message.usuario << ": " << message.text << std::endl; 

}

void Socket::enviar_mensaje(const sockaddr_in& address){

    signal(SIGINT, &signal_handler);
    signal(SIGTERM, &signal_handler);
    signal(SIGHUP, &signal_handler);  
    

    try{
        std::string linea;
        
        
        while(!quit){
            
            Message message;
            memset(message.text, 0, sizeof(message.text));
            memset(message.usuario, 0, sizeof(message.usuario));

            
            std::getline(std::cin, linea);
            setQuit(q);
            
            if(quit){
                break;    
            }
   
            if(linea == ":q")
            {
                quit = true;
                break;
                
            } 
            else if(linea != ""){

                
                linea.copy(message.text, sizeof(message.text)-1, 0);
                username.copy(message.usuario, sizeof(message.usuario)-1, 0);                
                message.dir_origen = d_origen;
                if(!servidor)
                    send_to(message, address);
                else{
                    for(int i=0; i<clientes.size(); i++){
                        if(clientes[i].sin_addr.s_addr != message.dir_origen.sin_addr.s_addr)
                            send_to(message, clientes[i]);
                    }
                }
            }         

        }
    }  
    catch(std::system_error& e){
       std::cerr << "Error en el hilo" << std::endl;
       quit = true;
    }

}

void Socket::recibir_mensaje(const sockaddr_in& address){

    sigfillset(&set);
    pthread_sigmask(SIG_BLOCK, &set, nullptr);
    
    try{
        while(!quit){
            mostrar(receive_from(address),address);
        }
    }
    catch(std::system_error& e)
    {
        std::cerr << "Error en el hilo" << std::endl;
        quit = true;
    }  
      
}






