# Practica 6 Roberto

## INFORME PRACTICA 6: Buses de comunicación II (SPI)  
**Roberto Dos Ramos**

El ejercicio práctico 1 consiste en la lectura de un archivo de texto almacenado en una tarjeta SD utilizando una placa ESP32-S3 y un módulo lector conectado mediante el bus SPI. Para ello, se emplea el código proporcionado, el cual se encarga de inicializar la tarjeta SD y abrir el archivo deseado mediante la función `SD.open()`, a la que se le pasa como argumento el nombre del archivo.

Una vez abierto correctamente, el contenido del archivo se muestra por el monitor serial, carácter por carácter. Finalmente, tras completar la lectura, el archivo se cierra utilizando la función `close()`.
