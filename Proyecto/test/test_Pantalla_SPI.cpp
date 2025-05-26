#include <Arduino.h>
#include <unity.h>
#include "Pantalla_SPI.h"

Pantalla_SPI pantalla;

void test_iniciar_pantalla() {
    pantalla.iniciar();
    TEST_PASS();
}

void test_mostrar_nombre_estacion() {
    pantalla.mostrarNombreEstacion("Radio Test");
    TEST_PASS();
}

void test_mostrar_nombre_cancion() {
    pantalla.mostrarNombreCancion("Cancion Test");
    pantalla.mostrarNombreCancion("");
    TEST_PASS();
}

void test_mostrar_tiempo() {
    pantalla.mostrarTiempo(65, 240); // 01:05 / 04:00
    TEST_PASS();
}

void test_Pantalla_SPI() {
    RUN_TEST(test_iniciar_pantalla);
    RUN_TEST(test_mostrar_nombre_estacion);
    RUN_TEST(test_mostrar_nombre_cancion);
    RUN_TEST(test_mostrar_tiempo);
}



