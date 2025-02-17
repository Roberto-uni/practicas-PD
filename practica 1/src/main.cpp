#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#define LED_PIN     48      // Pin donde está conectado el LED
#define NUM_LEDS    1      // Número de LEDs en la tira (en este caso, 1 LED)
#define BRIGHTNESS  255    // Brillo máximo del LED (0 a 255)
#define LED_BUILTIN 2
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Inicializa el LED
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show();  // Asegura que el LED esté apagado al principio
}

void loop() {
  

  // Cambiar el color del LED a rojo
  Serial.println("ON");
  digitalWrite(LED_BUILTIN, HIGH);
  strip.setPixelColor(0, strip.Color(255, 0, 0)); // Rojo
  strip.show();
 delay(1000); // Esperar 1 segundo
  
  
  // apaga
  Serial.println("OFF");
  digitalWrite(LED_BUILTIN, LOW);
  strip.setPixelColor(0, strip.Color(0, 0, 0)); // Azul
  strip.show();
  delay(1000); // Esperar 1 segundo
  

}