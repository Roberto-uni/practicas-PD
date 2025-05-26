#include "Lector_SD.h"


bool Lector_SD::iniciar() {
    //SPI.begin(PIN_SCLK, PIN_MISO, PIN_MOSI);
    if (!SD.begin(SD_CS)) {
        Serial.println("Error al inicializar la tarjeta SD");
        return false;
    }
    Serial.println("SD inicializada correctamente");
    return true;
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

