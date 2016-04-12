#include "historial.hpp"

Historial::Historial(){
	
		
		std::string ruta(std::getenv("HOME"));
		ruta += "/.talk";			//esto lo hacemos porque nos nos pilla ~
		std::string fichero(ruta); //inicializamos el fichero a la ruta indicada
		fichero += "/talk.log";

		//char RUTA_ACCESO[50];
		//ruta.copy(RUTA_ACCESO, sizeof(RUTA_ACCESO), 0);

		//char FICHERO[60];
		//fichero.copy(FICHERO, sizeof(FICHERO), 0);
		
		dir = opendir(ruta.c_str()); //utilizamos esta funcion para abrir y crearlo en caso de que no este nuestro directorio

		if(dir){	

			fd = open(fichero.c_str(), PERMISOS_FICHERO_CREADO, PERMISOS_DIRECTORIO);

				if(fd < 0) //se comprueba que open funcione
					throw std::system_error(errno, std::system_category(), "Fallo en open");

				if(ftruncate(fd, MAX_ITEM_IN_BUFFER) < 0) //ftruncate->cambia tamaño del archivo
					throw std::system_error(errno, std::system_category(), "Fallo en ftruncate");	

			pointer_mapeo = reinterpret_cast<char*>(mmap(NULL, MAX_ITEM_IN_BUFFER, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));			
			inicial_pos_mem = pointer_mapeo; 
			
				if(pointer_mapeo == MAP_FAILED)
					throw std::system_error(errno, std::system_category(), "Fallo en mmap");
			
			int i=0;

			while(inicial_pos_mem[i] != '~'){ 
				//std::cout << "CHIVATO" << std::endl;
				i++;
			}
			pointer_mapeo = pointer_mapeo + i;
			std::string ultima_linea ("");
			ultima_linea.copy(pointer_mapeo, ultima_linea.length(), 0);			 
			num_bytes = i; //inicializamos el numero de bytes usados a la pos en la que estamos
		
		}
		else if(ENOENT == errno){

			mkdir(ruta.c_str(), 0777);
			dir = opendir(ruta.c_str());
			fd = open(fichero.c_str(), PERMISOS_FICHERO, PERMISOS_DIRECTORIO);

				if(fd < 0) //se comprueba que open funcione
					throw std::system_error(errno, std::system_category(), "Fallo en open");

				if(ftruncate(fd, MAX_ITEM_IN_BUFFER) < 0) //ftruncate->cambia tamaño del archivo
					throw std::system_error(errno, std::system_category(), "Fallo en ftruncate");	

			pointer_mapeo = reinterpret_cast<char*>(mmap(NULL, MAX_ITEM_IN_BUFFER, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));			
			inicial_pos_mem = pointer_mapeo; 
			
				if(pointer_mapeo == MAP_FAILED)
					throw std::system_error(errno, std::system_category(), "Fallo en mmap");
			
		}
		else{

			throw std::system_error(errno, std::system_category(), "Fallo en opendir");
		}		

}

Historial::~Historial(){
	//antes de cerrar el programa escribimos un punto para saber en que pos nos quedamos
	std::string continuacion_line ("·");
	continuacion_line += '\n';	
	continuacion_line.copy(pointer_mapeo, continuacion_line.length(), 0);
	
	int desmapeo = munmap(inicial_pos_mem, MAX_ITEM_IN_BUFFER);
	closedir(dir);
	close(fd);
}

void Historial::insert_sms_historial(const Message& message){

	std::string line (message.usuario);
        line += " dijo: ";
	line += message.text;
	line += '\n';
	
	std::lock_guard<std::mutex> lock(p_mutex);

	{
		
		if(pointer_mapeo > inicial_pos_mem + MAX_ITEM_IN_BUFFER){
			pointer_mapeo = inicial_pos_mem;
			num_bytes = 0;
		}	
		
		num_bytes = line.copy(pointer_mapeo, line.length(), 0);
		pointer_mapeo += num_bytes; 
			
	}//el mutex es liberado automaticamente cuando salimos de este ambito

	 
}






















