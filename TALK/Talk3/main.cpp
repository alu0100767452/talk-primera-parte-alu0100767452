#include "socketudp.hpp"





int main(int argc, char* argv[]){

    bool help_option = false;
    bool server_option = false;
    bool client_option = false;
    std::string port_option;
    std::string ip_option;
    std::string username;

    std::cout << "argc: " << argc << std::endl;
    int op;


    while( (op = getopt(argc, argv, "hsc:u:p:01")) != -1){
        switch (op){
            case '0':
            case '1': break;
            case 'h': help_option = true; break;
            case 'u': username = std::string(optarg); break;
            case 's': std::cout << "MODO SERVIDOR" << std::endl;
                      server_option = true; break;
            case 'c': std::cout << "MODO CLIENTE" << std::endl;
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
        std::cout << "Modo SERVIDOR:  ./talk -s -p <PUERTO> [-u <USERNAME>]\n";
        std::cout << "Modo CLIENTE:  ./talk -c <IP_CLIENTE> -p <PUERTO> [-u <USERNAME>]\n";
        return 0;
    }
    else if(client_option){
        
        Socket s;
        std::cout << "Iniciando chat..." << std::endl; 
        sockaddr_in ad = make_ip_address(ip_option, atoi(port_option.c_str()));  
        sockaddr_in address = make_ip_address("127.0.0.3", 8002);
        sigset_t set;
        std::string name;
        
        
        try{

            if(username != "" )
                name = username;
            else
                name = std::getenv("USER");

            s = Socket(address, false, name);
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
        
        
        Socket s;
        std::cout << "Iniciando chat..." << std::endl; 
        sockaddr_in ad = make_ip_address("", atoi(port_option.c_str()));  
        sockaddr_in address = make_ip_address("127.0.0.3", atoi(port_option.c_str()));
        sigset_t set;
        std::string name;
        
        
        try{

            if(username != "" )
                name = username;
            else
                name = std::getenv("USER");


            s = Socket(address, true, name);
            sigfillset(&set);
            std::thread enviar(&Socket::enviar_mensaje, &s, ad);
            std::thread recibir(&Socket::recibir_mensaje, &s, address);

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


    return 0;
        


}
