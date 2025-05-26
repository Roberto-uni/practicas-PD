#pragma once
#include <SD.h>
#include <FS.h>
#include <SPI.h>
#include <TFT_eSPI.h>
// Pines
/*#define PIN_MOSI   11
#define PIN_MISO   13
#define PIN_SCLK   12
#define TFT_CS     10
#define TFT_DC     8
#define TFT_RST    9*/



const int SD_CS = 14;  // Cambia este valor al pin CS correcto para tu hardware



class Lector_SD {
public:
    bool iniciar();
    File obtenerCancion(const String& nombreArchivo);
    void listarCanciones();
    
};
