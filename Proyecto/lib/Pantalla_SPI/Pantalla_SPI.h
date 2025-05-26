#pragma once
#include <TFT_eSPI.h>

class Pantalla_SPI {
public:
    Pantalla_SPI();
    void iniciar();
    void mostrarNombreEstacion(const String& nombre);
    void mostrarNombreCancion(const String& nombre);
    void mostrarTiempo(uint32_t actual, uint32_t total);
    void mostrarVolumen(float volumen);
private:
    TFT_eSPI tft;
    void mostrarTexto(const String& texto, int y);
};
