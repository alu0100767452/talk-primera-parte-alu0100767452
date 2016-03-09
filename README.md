Talk Primera-Parte
===================


Talk es un programa de mensajería instantánea en modo texto que fue introducido en los sistemas UNIX en 1983. Básicamente permitía que diferentes usuarios en diferentes máquinas pudieran conversar. Este sistema con el tiempo fue sustituido por el IRC —apareció en 1988— y este a su vez dio paso a la multitud de sistemas de mensajería instantánea que existen actualmente.

----------


Compilación
-------------

Para llevar a cabo la compilación de los programas es necesario utilizar la siguiente linea de comandos:

 - **g++ -g -std=c++11 main.cpp socketudp.cpp -o talk -pthread**

O bien ejecutando el comando:

 - **make**

Con ello se genera un ejecutable [***talk***] que corresponderá con una copia del programa.

Ejecución y Uso
-------------

Para la ejecución y uso deberemos:

 - Ejecutamos en nuestra terminal: **./talk**.
 - Una vez hayamos lanzado cada uno de los programas en nuestras terminales, SÓLO deberemos escribir puesto que el programa se encargará de conectarse mediante los puertos 8888 y 8889 ambas terminales.
 - El uso es similar al de un Walkie Talkie primero se escribe y se van recibiendo los mensajes de la otra terminal según vayamos mandando los mensajes.
 - En la última revisión del programa, se ha implementado el modelo multihilo permitiendo un uso más dinámico de la herramienta.
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
