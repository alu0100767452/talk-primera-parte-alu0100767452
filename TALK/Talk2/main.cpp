#include "socketudp.hpp"


int main(){
    

try{    

    sockaddr_in address = make_ip_address("", 8889);

    Socket s(address);

    std::cout << "Iniciando chat..." << std::endl;

    std::string linea="";
    
    sockaddr_in ad = make_ip_address("", 8888);


   while(linea != ":q"){
        
        Message message;
        memset(message.text, 0, sizeof(message.text));
        std::getline(std::cin, linea);
        
        linea.copy(message.text, sizeof(message.text)-1, 0);
        
         s.send_to(message, ad);
         s.mostrar(s.receive_from(ad),ad);


    }


    std::cout << "Saliendo...\n";
}
catch(std::system_error& e){
    std::cerr << program_invocation_name << ": " << e.what() << std::endl;
    return 2;
}

    return 0;
        


}
