#include <iostream>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <cerrno>
#include <exception>
#include <system_error>
#include <thread>
#include <pthread.h>
#include <atomic>
#include <cxxabi.h>
#include <csignal>
#include <signal.h>
#include <vector>
#include <sys/mman.h>
#include <fcntl.h>
#include <dirent.h>
#include <mutex>
#include <sys/stat.h>


#define MAX_ITEM_IN_BUFFER (1000000) 
#define PERMISOS_FICHERO O_RDWR | O_CREAT | O_SYNC | O_APPEND
#define PERMISOS_FICHERO_CREADO O_RDWR | O_SYNC | O_APPEND 
#define PERMISOS_DIRECTORIO  S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH

struct Message{
    char text[1024];
    sockaddr_in dir_origen;
    char usuario[30];
};

class Historial{

	private:
		int fd;
		int num_bytes;
		char* pointer;
		DIR* dir;
		char* pointer_mapeo;
		char* inicial_pos_mem; 
		std::mutex p_mutex;
	public:
		Historial();
		~Historial();
		void insert_sms_historial(const Message& message);
};
