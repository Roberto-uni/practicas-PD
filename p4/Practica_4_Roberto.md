# Practica 4 Roberto

## INFORME PRÁCTICA 4: Sistemas operativos en tiempo real  
**Autor:** Roberto Dos Ramos  
[Repositorio GitHub](https://github.com/Roberto-uni/practicas-PD)

---

### Ejercicio 1

Consiste en la implementación de dos tareas diferentes:

1. La primera es un bucle infinito que se encarga de encender y apagar un LED.  
2. La segunda es una tarea puntual que se ejecuta únicamente una vez y adicionalmente muestra en qué núcleo del procesador se está ejecutando.

Para utilizar tareas, primero tenemos que programar una función que describa el comportamiento de esta, y luego definir la tarea en `void setup()`. Si queremos especificar el núcleo que queremos que utilice la tarea, tendremos que usar el comando `xTaskCreatePinnedToCore()`.

---

### Ejercicio 2

Para el ejercicio 2, la implementación de las tareas es similar a la del apartado anterior, solo que ahora utilizamos un **semáforo binario** para determinar cuándo una tarea se puede ejecutar.

Para esto:

- La tarea tiene que comprobar que tiene el semáforo mediante un `if`.
- Al finalizar, debe dar ese semáforo para que se ejecute la siguiente tarea.

> **Nota:** Para que se pueda ejecutar la siguiente tarea, después de dar el semáforo tenemos que usar `vTaskDelay()` para indicarle al programador que en ese periodo de tiempo no ejecute esta tarea y así pase a la siguiente. De lo contrario, seguiría repitiendo la misma tarea de forma indefinida.

[Repositorio GitHub](https://github.com/Roberto-uni/practicas-PD)
