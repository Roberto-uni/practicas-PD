#include "Lector_SD.h"

SPIClass SPI_SD(FSPI);  // FSPI equivale a SPI3 en ESP32-S3

bool Lector_SD::iniciar() {
    Serial.println("Inicializando SPI3 y SD...");

    SPI_SD.begin(PIN_SPI_SCK, PIN_SPI_MISO, PIN_SPI_MOSI, PIN_SPI_CS);
    if (!SD.begin(PIN_SPI_CS, SPI_SD)) {
        Serial.println("¡Fallo al montar la tarjeta SD!");
        return false;
    }

    Serial.println("Tarjeta SD montada.");
    return true;
}

std::vector<String> Lector_SD::obtenerListaCanciones() {
    canciones.clear();
    File root = SD.open("/");
    while (File file = root.openNextFile()) {
        String nombre = file.name();
        if (nombre.endsWith(".mp3")) {
            canciones.push_back(nombre);
        }
        file.close();
    }
    return canciones;
}



File Lector_SD::obtenerCancion(const String& nombreArchivo) {
    return SD.open("/" + nombreArchivo);
}



void Lector_SD::listarCanciones() {
    File root = SD.open("/");
    while (File file = root.openNextFile()) {
        Serial.println(file.name());
        file.close();
    }
}


