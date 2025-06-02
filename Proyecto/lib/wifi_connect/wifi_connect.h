#pragma once
#include <WiFi.h>
#include "Pantalla_SPI.h"

// Declaración anticipada para evitar incluir Pantalla_SPI.h aquí
class Pantalla_SPI;

class wifi_connect {
public:
    void conectar(const char* ssid, const char* password, Pantalla_SPI& tft);
    bool estaConectado();
};
