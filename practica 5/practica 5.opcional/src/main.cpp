#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_AHTX0.h>

#define SCREEN_WIDTH 128  // Ancho del OLED en píxeles
#define SCREEN_HEIGHT 64  // Alto del OLED en píxeles

#define SDA_PIN 8   // Pin SDA en ESP32-S3
#define SCL_PIN 9   // Pin SCL en ESP32-S3

#define OLED_RESET    -1  // Reset (-1 si no se usa un pin de reset)
#define SCREEN_ADDRESS 0x3C  // Dirección I2C del OLED (0x3C para la mayoría de pantallas SSD1306)

// Inicializar pantalla OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Inicializar sensor AHT10
Adafruit_AHTX0 aht10;

void setup() {
    Serial.begin(115200);
    Wire.begin(SDA_PIN, SCL_PIN);  // Inicializa I2C con los pines definidos

    // Inicializar la pantalla OLED
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("Error al iniciar la pantalla SSD1306"));
        while (true);  // Detener ejecución si falla la inicialización
    }

    // Inicializar el sensor AHT10 con la librería Adafruit
    if (!aht10.begin()) {
        Serial.println("Error: No se detectó el sensor AHT10.");
        while (true);  // Detener si no encuentra el sensor
    }

    Serial.println("Sistema iniciado correctamente.");
}

void loop() {
    // Leer temperatura y humedad
    sensors_event_t humidity, temp;
    aht10.getEvent(&humidity, &temp);  // Obtener valores

    // Mostrar temperatura en el monitor serie
    Serial.print("Temperatura: ");
    Serial.print(temp.temperature);
    Serial.println(" °C");

    // Limpiar pantalla OLED
    display.clearDisplay();

    // Configurar texto en pantalla
    display.setTextSize(2);  // Tamaño del texto
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 20);
    
    // Mostrar temperatura en el OLED
    display.print("Temp: ");
    display.print(temp.temperature);
    display.print(" C");

    display.display();  // Actualizar pantalla

    delay(2000);  // Esperar 2 segundos antes de actualizar
}
