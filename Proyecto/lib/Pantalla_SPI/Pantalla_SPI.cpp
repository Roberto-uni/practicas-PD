#include "TFT_eSPI.h"
#include "Pantalla_SPI.h"

Pantalla_SPI ::Pantalla_SPI() : tft() {}

void Pantalla_SPI::iniciar() {
    
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(1);
    
}
void Pantalla_SPI::limpiar(){
    tft.fillScreen(TFT_BLACK);
}

void Pantalla_SPI::mostrarTexto(const String& texto, int y) {

    tft.fillRect(0, y, 320, 20, TFT_BLACK);
    tft.setCursor(10, y);
    tft.print(texto);

}

void Pantalla_SPI::mostrarNombreEstacion(const String& nombre) {

    tft.setTextSize(2);
    mostrarTexto( nombre, 20);

}

void Pantalla_SPI::mostrarNombreCancion(const String& nombre) {
    tft.setTextSize(1);
    if (nombre.length() > 0) {
        mostrarTexto("Cancion: " + nombre, 50);
    } else {
        mostrarTexto("Cancion: nombre no disponible", 50);
    }

}

void Pantalla_SPI::mostrarTiempo(uint32_t actual) {
    tft.fillRect(0, 110, 320, 20, TFT_BLACK);  // borrar solo línea de tiempo
    tft.setTextSize(2);
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "------%02d:%02d------",
             actual / 60, actual % 60 );
    mostrarTexto(buffer, 110);
}


void Pantalla_SPI::mostrarEstadoReproduccion(bool pausado) {
    // Borra el área donde se mostrará el estado (ajusta tamaño y posición si es necesario)
    tft.fillRect(0, 85, 160, 20, TFT_BLACK); // Área limpia
    tft.setTextSize(1);
    if (pausado) {
        // Dibuja dos barras verticales (símbolo de pausa)
        tft.fillRect(10, 85, 4, 10, TFT_WHITE);
        tft.fillRect(18, 85, 4, 10, TFT_WHITE);

        // Muestra texto "Pausado"
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setCursor(30, 90);
        tft.setTextSize(1);
        tft.print("Pausado");
    } else {
        // Dibuja triángulo (símbolo de reproducción)
        tft.fillTriangle(10, 85, 10, 95, 20, 90, TFT_WHITE);

        // Muestra texto "Reproduciendo"
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setCursor(30, 90);
        tft.setTextSize(1);
        tft.print("Reproduciendo");
    }
}



//#include <algorithm> // si estás en un entorno que lo soporta

void Pantalla_SPI::mostrarVolumen(float volumen) {
    // Asegurar que el volumen está entre 0.0 y 3.0
    if (volumen < 0.0) volumen = 0.0;
    if (volumen > 3.0) volumen = 3.0;

    const float paso = 0.3;
    const int max_cuadros = 10;  // 3.0 / 0.3 = 10 cuadros
    int cuadros_activos = (int)(volumen / paso + 0.001); // evitar error de redondeo flotante
    if (cuadros_activos > max_cuadros) cuadros_activos = max_cuadros;

    // Tamaño y posición de los cuadros
    const int cuadro_ancho = 12;
    const int cuadro_alto = 10;
    const int espacio = 4;

    int x_inicio = (tft.width() - (max_cuadros * cuadro_ancho + (max_cuadros - 1) * espacio)) / 2;
    int y_inicio = tft.height() - cuadro_alto - 40; // 10 px de margen inferior

    // Colores
    uint16_t color_activo = TFT_GREEN;
    uint16_t color_inactivo = TFT_DARKGREY;

    // Dibujar cuadros
    for (int i = 0; i < max_cuadros; i++) {
        int x = x_inicio + i * (cuadro_ancho + espacio);
        uint16_t color = (i < cuadros_activos) ? color_activo : color_inactivo;
        tft.fillRect(x, y_inicio, cuadro_ancho, cuadro_alto, color);
        tft.drawRect(x, y_inicio, cuadro_ancho, cuadro_alto, TFT_WHITE); // borde opcional
    }
}



