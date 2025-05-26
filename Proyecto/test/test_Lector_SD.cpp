#include <Arduino.h>
#include <unity.h>
#include "Lector_SD.h"

Lector_SD lector;
// SD_CS = 7
void test_sd_iniciar() {
    bool iniciado = lector.iniciar();
    TEST_ASSERT_TRUE_MESSAGE(iniciado, "No se pudo iniciar la tarjeta SD");
}

void test_sd_obtener_cancion() {
    File archivo = lector.obtenerCancion("bensound-happyrock.wav");  // Asegúrate de que este archivo exista en tu SD
    TEST_ASSERT_TRUE_MESSAGE(archivo, "Archivo no encontrado o no se pudo abrir");
    archivo.close();
}

void test_sd_listar_canciones() {
    // Esta función imprime por Serial, así que verificamos que no falle
    lector.listarCanciones();
    TEST_PASS(); // No hay errores => test pasa
}

// Función que llama todos los tests
void test_lector_sd() {
    RUN_TEST(test_sd_iniciar);
    RUN_TEST(test_sd_obtener_cancion);
    RUN_TEST(test_sd_listar_canciones);
}
