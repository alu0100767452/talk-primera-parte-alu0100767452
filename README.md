Talk Primera-Parte
===================


Talk es un programa de mensajería instantánea en modo texto que fue introducido en los sistemas UNIX en 1983. Básicamente permitía que diferentes usuarios en diferentes máquinas pudieran conversar. Este sistema con el tiempo fue sustituido por el IRC —apareció en 1988— y este a su vez dio paso a la multitud de sistemas de mensajería instantánea que existen actualmente.

----------


Compilación
-------------

Para llevar a cabo la compilación de los programas es necesario utilizar la siguiente linea de comandos:
	**g++ -g -std=c++11 main.cpp socketudp.hpp -o talk**
Con ello se genera un ejecutable [*talk*] que corresponderá con una copia del programa

Ejecución y Uso
-------------

Para la ejecución y uso deberemos:

 - ./talk
 - Una vez hayamos lanzado cada uno de los programas en nuestras terminales, SÓLO deberemos escribir puesto que el programa se encargará de conectarse mediante los puertos 8888 y 8889 ambas terminales.
 - El uso es similar al de un Walkie Talkie primero se escribe y se van recibiendo los mensajes de la otra terminal según vayamos mandando los mensajes.
 - Para terminar de hablar bastará con escribir **\q** o con **Ctrl+C**.

Características
-------------
Principales características del proyecto

 - Utilización de los sockets ( llamadas a función **socket()** )
 - Envío de mensajes mediante **sendto()**
 - Recibo de mensajes mediante **recvfrom()**
 - Manejo de errores
 - Creación de estructuras **Message** y función **make_ip_address**
