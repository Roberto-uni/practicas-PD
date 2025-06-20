
# INFORME PRÁCTICA 7: Buses de comunicación III (I2S)  
**Roberto Dos Ramos**

---

## Ejercicio Práctico 1

En este primer ejercicio utilizaremos la librería **ESP8266 de Earle F. Philhower** para reproducir un archivo de audio (o en su defecto un arreglo de bytes que corresponde al audio) con nuestra placa **ESP32-S3** y el módulo **I2S MAX98357A**. Para esto usaremos el código de ejemplo incluido con la librería.

El código genera un objeto de entrada donde carga la cabecera `sampleaac.h`, luego genera unos objetos `aac` y `out` que corresponden a los datos de audio a reproducir y a la salida de audio que recibirá el I2S. Finalmente, se inicializa el objeto `aac` tomando como argumentos en su función `begin()` a los objetos de entrada y salida `in` y `out`.

---

## Ejercicio Práctico 2

Para este ejercicio tenemos que reproducir audio de una SD a través del módulo I2S. Para esto usaremos las clases:

- `AudioGeneratorMP3`
- `AudioFileSourceSD`
- `AudioOutputI2S`

Estas clases ya incluyen los constructores necesarios para generar un objeto con el archivo SD que deseamos reproducir, un objeto que gestiona los datos que saldrán por el I2S, y un objeto que, usando los dos objetos previos, reproduce el archivo `.mp3`.

En el código primero inicializamos los pines del lector SD, después creamos el objeto de salida I2S (`out`) e inicializamos el módulo con los pines establecidos. Finalmente se inicializa el objeto con el archivo SD y reproducimos el audio con el objeto `mp3`.
