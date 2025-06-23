#pragma once
#include <SD.h>
#include <FS.h>
#include <SPI.h>
#include <vector>

// Pines para SPI3 (HSPI)
#define PIN_SPI_MISO 36
#define PIN_SPI_MOSI 35
#define PIN_SPI_SCK  37
#define PIN_SPI_CS   38

// Declaración de SPI_SD
extern SPIClass SPI_SD;

class Lector_SD {
public:
    bool iniciar();
    std::vector<String> obtenerListaCanciones();
private:
    std::vector<String> canciones;
};
