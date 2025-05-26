#include "wifi_connect.h"

void wifi_connect::conectar(const char* ssid, const char* password) {
    WiFi.begin(ssid, password);
    Serial.print("Conectando a WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConectado: " + WiFi.localIP().toString());
}

bool wifi_connect::estaConectado() {
    return WiFi.status() == WL_CONNECTED;
}
