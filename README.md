Talk
===================


Talk es un programa de mensajería instantánea en modo texto que fue introducido en los sistemas UNIX en 1983. Básicamente permitía que diferentes usuarios en diferentes máquinas pudieran conversar. Este sistema con el tiempo fue sustituido por el IRC —apareció en 1988— y este a su vez dio paso a la multitud de sistemas de mensajería instantánea que existen actualmente.

----------


Compilación
-------------

Para llevar a cabo la compilación de los programas es necesario utilizar la siguiente linea de comandos:

 - **g++ -g -std=c++11 main.cpp socketudp.cpp historial.cpp -o talk -pthread**

O bien ejecutando el comando:

 - **make**

Con ello se genera un ejecutable [***talk***] que corresponderá con una copia del programa.

Ejecución y Uso
-------------

Para la ejecución del programa deberemos tener en cuenta el modo en cómo queremos ejecutar nuestro programa diferenciando entre:

 - **Modo Servidor**
	 - ./talk -s -p < NúmeroPuerto > [-u < Usuario >]
 - **Modo Cliente**
	 - ./talk -c < dirServidor > -p < NúmeroPuerto > [-u < Usuario >]
	 - 
 - En la última revisión del programa, se ha implementado el modelo multihilo permitiendo un uso más dinámico de la herramienta y permitiendo el uso del chat de forma multiusuario, donde una copia del programa actúa de servidor al que se conectaran los usuarios enviando los mensajes que se reenviaran al resto de ellos.
 - Para terminar de hablar bastará con escribir **:q** o con **Ctrl+C**.

Características
-------------
Principales características del proyecto

 - Utilización de los sockets ( llamadas a función **socket()** ).
 - Envío de mensajes mediante **sendto()**.
 - Recibo de mensajes mediante **recvfrom()**.
 - Manejo de errores y excepciones, utilizando principalmente la librería *system_error*.
 - Creación de estructuras **Message** y función **make_ip_address**.
 - Modelo multihilo que permite tanto enviar como recibir mensajes de manera simultánea gracias al uso de **thread**.
 - Cancelación de hilos. Función **request_cancellation** y manejo de errores.
 - Utilización de metodos **join** y **detach** para la espera en los hilos.
 - Permite chat multiusuario mediante el uso de clientes/servidor, para su funcionamiento, el usuario envía un mensaje al servidor y este lo redistribuye a todos los clientes conocidos excepto al que envió el mensaje almacenados en un vector de clientes.
 - Permite argumentos pasados por la línea de comandos:
	 - Modo Servidor:  **-s**
	 - Modo Cliente:  **-c "dirServidor"**
		 - Ejemplo:   -c 127.0.0.1
	 - Puerto:  **-p "númeroPuerto"**
		 - Ejemplo:   -p 8000
	 - Usuario:  **-u "nombreUsuario"**
		 - Ejemplo:  -u Alejandro
	 - Ayuda:  **-h**
 - Uso de **historial de mensajes** los mensajes tanto recibidos como enviados por el usuario se almacenarán en la siguiente ruta: **"./talk/talk.log"**
 - Implementado el front-end gráfico en Qt para la aplicación gráfica.

