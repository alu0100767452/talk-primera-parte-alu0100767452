#include "socketudp.hpp"


int main(){

    Socket s;
    std::cout << "Iniciando chat..." << std::endl; 
    sockaddr_in ad = make_ip_address("", 8889);  
    sockaddr_in address = make_ip_address("", 8888);
    
try{

    std::thread enviar(&Socket::enviar_mensaje, &s, ad);
    std::thread recibir(&Socket::recibir_mensaje, &s, ad);
    s = Socket(address);

    recibir.join();
    enviar.join();

    request_cancellation(enviar);
    request_cancellation(recibir);

}
catch(std::system_error& e){
    std::cerr << program_invocation_name << ": " << e.what() << std::endl;
    return 2;
}

     

      
    std::cout << "Saliendo...\n";

    
    return 0;
        


}
