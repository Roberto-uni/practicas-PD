#include <Arduino.h>
#include <unity.h>
#include "wifi_connect.h"

// Cambia por tus credenciales de red reales para pruebas
const char* ssid = "RedmiNote7";
const char* password = "estacosa";

wifi_connect wifi;


void test_wifi_conectar() {
    wifi.conectar(ssid, password);
    TEST_ASSERT_TRUE(wifi.estaConectado());
}

void test_wifi_estado() {
    TEST_ASSERT_EQUAL(WL_CONNECTED, WiFi.status());
}

void test_wifi_connect() {
    RUN_TEST(test_wifi_conectar);
    RUN_TEST(test_wifi_estado);
}
