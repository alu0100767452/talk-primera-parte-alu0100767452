#include "socketudp.hpp"

int main(){
    
    Socket s;
    std::cout << "Iniciando chat..." << std::endl;
    sockaddr_in ad = make_ip_address("", 8888);
    sockaddr_in address = make_ip_address("", 8889);

try{    


    s = Socket(address);
   
    std::thread enviar(&Socket::enviar_mensaje, &s, ad);
    std::thread recibir(&Socket::recibir_mensaje, &s, ad);


    recibir.detach(); //Hilo demonio
    enviar.join(); //Esperamos por el hilo



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
