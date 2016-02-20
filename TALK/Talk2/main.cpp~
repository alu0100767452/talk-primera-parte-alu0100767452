#include "socketudp.hpp"


int main(){
    
    Socket s;

    std::cout << "Iniciando chat..." << std::endl;

    std::string linea="";
    
    sockaddr_in ad = make_ip_address("", 8888);


   while(linea != "\q")
    {
        
        Message message;
        strcpy(message.text, ""); 
        std::cin >> linea;
        linea.copy(message.text, sizeof(message.text)-1, 0);
        s.send_to(message, ad);
        s.receive_from(message, ad);

    }

        


}
