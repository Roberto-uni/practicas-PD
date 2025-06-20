#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
  Serial.begin(9600);
  Serial.print("Iniciando SD...");

  // Inicializar la tarjeta SD en el pin 4
  if (!SD.begin(4)) {
    Serial.println(" No se pudo inicializar la tarjeta SD.");
    return;
  }

  Serial.println(" Inicialización exitosa.");

  // Intentar abrir el archivo en modo lectura
  myFile = SD.open("archivo.txt");
  if (myFile) {
    Serial.println("Contenido de archivo.txt:");

    // Leer y mostrar el contenido del archivo
    while (myFile.available()) {
      Serial.write(myFile.read());
    }

    // Cerrar el archivo
    myFile.close();
  } else {
    Serial.println("Error al abrir el archivo.");
  }
}

void loop() {
  // Nada que hacer aquí
}
