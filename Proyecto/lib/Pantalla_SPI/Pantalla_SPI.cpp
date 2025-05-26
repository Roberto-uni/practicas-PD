#include "TFT_eSPI.h"
#include "Pantalla_SPI.h"

Pantalla_SPI ::Pantalla_SPI() : tft() {}

void Pantalla_SPI::iniciar() {
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(1);
}

void Pantalla_SPI::mostrarTexto(const String& texto, int y) {
    tft.fillRect(0, y, 320, 20, TFT_BLACK);
    tft.setCursor(10, y);
    tft.print(texto);
}

void Pantalla_SPI::mostrarNombreEstacion(const String& nombre) {
    mostrarTexto("Estacion: " + nombre, 20);
}

void Pantalla_SPI::mostrarNombreCancion(const String& nombre) {
    if (nombre.length() > 0) {
        mostrarTexto("Cancion: " + nombre, 50);
    } else {
        mostrarTexto("Cancion: nombre no disponible", 50);
    }
}

void Pantalla_SPI::mostrarTiempo(uint32_t actual, uint32_t total) {
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%02d:%02d / %02d:%02d",
             actual / 60, actual % 60, total / 60, total % 60);
    mostrarTexto(buffer, 80);
}

void Pantalla_SPI::mostrarVolumen(float volumen) {
    // Asegurar que el volumen está entre 0 y 1
    if (volumen < 0.0) volumen = 0.0;
    if (volumen > 1.0) volumen = 1.0;

    const int max_cuadros = 10;  // 10 cuadros = volumen máximo 1.0
    int cuadros_activos = (int)(volumen * max_cuadros + 0.5); // redondear

    // Tamaño y posición de los cuadros
    const int cuadro_ancho = 12;
    const int cuadro_alto = 20;
    const int espacio = 4;

    int x_inicio = (tft.width() - (max_cuadros * cuadro_ancho + (max_cuadros - 1) * espacio)) / 2;
    int y_inicio = tft.height() - cuadro_alto - 10; // 10 px de margen inferior

    // Colores
    uint16_t color_activo = TFT_GREEN;
    uint16_t color_inactivo = TFT_DARKGREY;

    // Dibujar cuadros
    for (int i = 0; i < max_cuadros; i++) {
        int x = x_inicio + i * (cuadro_ancho + espacio);
        uint16_t color = (i < cuadros_activos) ? color_activo : color_inactivo;
        tft.fillRect(x, y_inicio, cuadro_ancho, cuadro_alto, color);
        // opcional: borde
        tft.drawRect(x, y_inicio, cuadro_ancho, cuadro_alto, TFT_WHITE);
    }
}
