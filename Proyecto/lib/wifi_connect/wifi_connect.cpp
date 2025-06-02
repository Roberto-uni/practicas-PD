#include "wifi_connect.h"
#include "Pantalla_SPI.h"


void wifi_connect::conectar(const char* ssid, const char* password, Pantalla_SPI& tft) {
    WiFi.begin(ssid, password);
    Serial.print("Conectando a WiFi");
    tft.mostrarTexto("Conectando a WiFi", 20);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConectado: " + WiFi.localIP().toString());
}

bool wifi_connect::estaConectado() {
    return WiFi.status() == WL_CONNECTED;
}
