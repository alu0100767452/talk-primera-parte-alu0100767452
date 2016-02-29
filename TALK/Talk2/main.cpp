#include "socketudp.hpp"

int main(){
    

try{    

    sockaddr_in address = make_ip_address("", 8889);
    Socket s(address);
    std::cout << "Iniciando chat..." << std::endl;
    std::string linea="";
    sockaddr_in ad = make_ip_address("", 8888);




    std::thread enviar(&Socket::enviar_mensaje, &s, ad);
    std::thread recibir(&Socket::recibir_mensaje, &s, ad);
    
    


    

    recibir.join();
    enviar.join();
    request_cancellation(enviar);
    request_cancellation(recibir);
    
    std::cout << "Saliendo...\n";
}
catch(std::system_error& e){
    std::cerr << program_invocation_name << ": " << e.what() << std::endl;
    return 2;
}

    return 0;
        


}
