# Practica 1 Roberto

## INFORME PRÁCTICA 1: BLINK  
**Autor:** Roberto Dos Ramos  

---

### Primera parte

La primera parte de la práctica consiste en hacer parpadear el LED de la placa utilizando el código aportado. Pero dado que estábamos utilizando un modelo de placa diferente, el código se tuvo que cambiar, ya que la nueva placa solo disponía de un RGB que requiere algo más que solo asignar una salida de voltaje alta a un pin.

Para poder utilizar el RGB, se instaló la librería `adafruit neopixel`. Una vez instalada, se creó un objeto para controlar el LED RGB y se le asignaron los parámetros necesarios. Luego, para hacer que se encienda, le dimos valores de color, en este caso rojo `(255, 0, 0)`, y para que se apague simplemente se estableció que “no hay color” `(0, 0, 0)`. Adicionalmente, se agregaron líneas de código para inicializar el puerto serie y para que se envíe por este un mensaje cuando se enciende y se apaga el LED.

---

### Segunda parte

En la segunda parte de la práctica, se le asignó a un pin de la placa (pin 2 en este caso) una salida de voltaje alta siempre que el LED esté encendido, y baja cuando no. Después se conectó a un osciloscopio, donde se puede observar el cambio de voltaje una vez pasa el `delay` indicado en el código.


---

### Medición de frecuencia máxima

Por último, se midió la máxima frecuencia que permite el microcontrolador. Para ello se eliminó el `delay` que había entre el encendido y apagado del LED, y se obtuvo una frecuencia de **1.078 kHz**.
