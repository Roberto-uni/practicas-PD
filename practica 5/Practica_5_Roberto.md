
# INFORME PRÁCTICA 5: Buses de comunicación I2C  
**Autor:** Roberto Dos Ramos  


---

## Ejercicio 1  
Este primer ejercicio consiste en conectar un bus I2C a la placa y, mediante el código proporcionado, ver qué dirección se le asignó al bus utilizado.  
Para el montaje tenemos que conectar los pines de **SDA** y **SCK** a los pines **8 y 9** respectivamente (por defecto suelen ser los pines 21 y 22, pero en la ESP32-S3 no hay pin 22).

---

## Ejercicio 2  
Para este ejercicio tenemos que implementar el código para hacer uso de un bus I2C.  
En este caso se utilizará el **display**, para ello se han de pasar los parámetros de la información a mostrar como el texto, el color, la ubicación y el tamaño de la letra.

```cpp
#include <Wire.h> 
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h> 

#define SCREEN_WIDTH 128  // Ancho de la pantalla en píxeles 
#define SCREEN_HEIGHT 64  // Alto de la pantalla en píxeles

#define SDA_PIN 8          // Pin SDA en ESP32-S3 
#define SCL_PIN 9          // Pin SCL en ESP32-S3 

#define OLED_RESET -1      // Reset (-1 si no se usa un pin de reset) 
#define SCREEN_ADDRESS 0x3C  // Dirección I2C del OLED (0x3C para la mayoría de pantallas SSD1306) 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); 

void setup() { 
  Serial.begin(115200); 
  Wire.begin(SDA_PIN, SCL_PIN);  // Inicializa I2C con los pines personalizados 

  // Inicializar la pantalla OLED 
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) { 
    Serial.println(F("Error al iniciar la pantalla SSD1306")); 
    while (true);  // Detener ejecución si falla la inicialización 
  } 

  display.clearDisplay();         // Limpia la pantalla 
  display.setTextSize(2);         // Tamaño del texto (1 = pequeño, 2 = mediano, etc.) 
  display.setTextColor(SSD1306_WHITE);  // Color del texto (blanco) 
  display.setCursor(20, 20);      // Posición inicial del texto (x, y) 
  display.println("Hola");        // Texto que se mostrará 
  display.display();              // Actualiza la pantalla con el texto 
} 

void loop() { 
  // No es necesario repetir el texto, ya que el setup() lo muestra y se mantiene en la pantalla 
}
```

---
