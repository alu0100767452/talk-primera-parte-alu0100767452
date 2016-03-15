#include "socketudp.hpp"





int main(int argc, char* argv[]){

    bool help_option = false;
    bool server_option = false;
    bool client_option = false;
    std::string port_option;
    std::string ip_option;

    std::cout << "argc: " << argc << std::endl;
    int op;


    while( (op = getopt(argc, argv, "hs:c:p:01")) != -1){
        switch (op){
            case '0':
            case '1': break;
            case 'h': help_option = true; break;
            case 's': server_option = true; break;
            case 'c': //std::printf("opción c con valor '%s'\n", optarg);
                      client_option = true;
                      ip_option = std::string(optarg); break;
            case 'p': //std::printf("opción p con valor '%s'\n", optarg);
                      port_option = std::string(optarg); break;
            case '?': break;
            default: std::fprintf(stderr, "?? getopt devolvió código de error 0%o ??\n", op);



        }
    }
    if(optind < argc){
        std::cout << "-- argumentos no opción --" << std::endl;
        for(; optind < argc; ++optind){
            std::cout << "argv[" << optind << "]: " << argv[optind] << std::endl;
        }
    }

    if(help_option){
        std::cout << "Ayuda: " << std::endl;
        std::cout << "Modo SERVIDOR:  ./talk -s -p <PUERTO>\n";
        std::cout << "Modo CLIENTE:  ./talk -c <IP_CLIENTE> -p <PUERTO>\n";
        return 0;
    }
    else if(client_option){
        
        Socket s;
        std::cout << "Iniciando chat..." << std::endl; 
        sockaddr_in ad = make_ip_address(ip_option.c_str(), atoi(port_option.c_str()));  
        sockaddr_in address = make_ip_address("127.0.0.3", 8002);
        sigset_t set;
        
        
        try{

            s = Socket(address, false);
            sigfillset(&set);
            std::thread enviar(&Socket::enviar_mensaje, &s, ad);
            std::thread recibir(&Socket::recibir_mensaje, &s, ad);

            recibir.detach(); //Hilo demonio
            enviar.join();  //Esperamos por el hilo

            request_cancellation(enviar);
            request_cancellation(recibir);

        }
        catch(std::system_error& e){
            std::cerr << program_invocation_name << ": " << e.what() << std::endl;
            return 2;
        }
        catch(abi::__forced_unwind&){
            std::cerr << "Error en la cancelación de los hilos\n";
            return 3;
        }

              
            std::cout << "Saliendo...\n";

        return 0;


    }
    else if(server_option){
        
        
        


    }

/*

    Socket s;
    std::cout << "Iniciando chat..." << std::endl; 
    sockaddr_in ad = make_ip_address("", 8889);  
    sockaddr_in address = make_ip_address("", 8888);
    sigset_t set;
    
    
try{

    s = Socket(address);
    sigfillset(&set);
    std::thread enviar(&Socket::enviar_mensaje, &s, ad);
    std::thread recibir(&Socket::recibir_mensaje, &s, ad);

    recibir.detach(); //Hilo demonio
    enviar.join();  //Esperamos por el hilo



    request_cancellation(enviar);
    request_cancellation(recibir);

}
catch(std::system_error& e){
    std::cerr << program_invocation_name << ": " << e.what() << std::endl;
    return 2;
}
catch(abi::__forced_unwind&){
    std::cerr << "Error en la cancelación de los hilos\n";
    return 3;
}

      
    std::cout << "Saliendo...\n";

    */
    return 0;
        


}
