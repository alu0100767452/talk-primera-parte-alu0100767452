#include "socketudp.hpp"


int main(){
    
    Socket s;

    std::cout << "Iniciando chat..." << std::endl;

    std::string linea="";
    
    sockaddr_in ad = make_ip_address("", 8889);


   while(1){
    

        Message message;
        memset(message.text, 0, sizeof(message.text));

        std::cin >> linea;
        if(linea == ":q")
        {
            std::cout << "Saliendo...\n";
            break;
        }
        
        linea.copy(message.text, sizeof(message.text)-1, 0);
        s.send_to(message, ad);

        s.receive_from(message, ad);

    }

    return 0;
        


}
