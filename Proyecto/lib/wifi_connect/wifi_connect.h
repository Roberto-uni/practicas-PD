#pragma once
#include <WiFi.h>

class wifi_connect {
public:
    void conectar(const char* ssid, const char* password);
    bool estaConectado();
};
