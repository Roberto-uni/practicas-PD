
# Informe Práctica 2: Interrupciones  
**Autor:** Roberto Dos Ramos  

---

## Práctica A: Interrupción por GPIO  

Esta primera parte consiste en comprobar el funcionamiento de una interrupción generada por el hardware en el ESP32 al presionar un botón físico usando el código aportado por el documento de la práctica. 

Cada vez que se presiona el botón (lo que genera un flanco descendente), se activa la ISR (la rutina de interrupción asociada a la funcion IRAM_ATTR isr() ) y se registra esa pulsación. El programa continúa ejecutando su bucle principal y muestra en el monitor serie cuántas veces se ha pulsado el botón. Después de un minuto, la interrupción se desactiva y ya no se registran más pulsaciones, aunque el programa siga funcionando.

Después de cargar el programa en la placa, al presionar el botón en el monitor serial se observa el mensaje

Button 1 has been pressed 1;
Button 1 has been pressed 2;
Button 1 has been pressed 3;
….

Después de que haya transcurrido un minuto lo que se observa en el monitor serial es el mensaje “interrupt detached”


### Salida esperada en el monitor serial:
```
Button 1 has been pressed 1
Button 1 has been pressed 2
Button 1 has been pressed 3
...
Interrupt Detached!
```


