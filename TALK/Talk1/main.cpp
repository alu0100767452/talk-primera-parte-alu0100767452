#include "socketudp.hpp"


int main(){
    

    sockaddr_in address = make_ip_address("", 8888);

    Socket s(address);

    std::cout << "Iniciando chat..." << std::endl;

    std::string linea="";
    
    sockaddr_in ad = make_ip_address("", 8889);


   while(linea != ":q"){
    

        Message message;
        memset(message.text, 0, sizeof(message.text));

        std::getline(std::cin, linea);        
        linea.copy(message.text, sizeof(message.text)-1, 0);

        s.send_to(message, ad);
        s.receive_from(message, ad);


    }

    std::cout << "Saliendo...\n";

    return 0;
        


}
