#include "WebRadio.h"
#include "I2S_Audio.h"
#include "wifi_connect.h"
#include "Pantalla_SPI.h"


// Pines I2S para ESP32-S3
#define I2S_DOUT 21
#define I2S_BCLK 20
#define I2S_LRC  19

// Pines botones
#define BOTON_SUBIR 4
#define BOTON_BAJAR 5

// WiFi
wifi_connect* red;
const char* ssid = "RedmiNote7";
const char* password = "estacosa";


// Stream
const char* streamURL = "http://media-ice.musicradio.com/ClassicFMMP3";

// Objetos
I2S_Audio* i2s;
WebRadio* radio;
Pantalla_SPI pan;

void setup() {
  Serial.begin(115200);
  pan.iniciar();
  delay(500);
  red->conectar(ssid,password);

  pinMode(BOTON_SUBIR, INPUT_PULLUP);
  pinMode(BOTON_BAJAR, INPUT_PULLUP);

  i2s = new I2S_Audio(I2S_BCLK, I2S_LRC, I2S_DOUT, 0.8);
  radio = new WebRadio(streamURL);

  pan.mostrarNombreEstacion("ClassicFMMP3");
  pan.mostrarVolumen(i2s->getGain());

  radio->setOutput(i2s->get());
  radio->begin(i2s->get());
}

void loop() {
  radio->loop();
    // Leer botones (activo bajo)
  if (digitalRead(BOTON_SUBIR) == LOW) {
    i2s->subirVolumen();
    pan.mostrarVolumen(i2s->getGain());
    delay(300); // debounce y evitar subidas muy rápidas
  }

  if (digitalRead(BOTON_BAJAR) == LOW) {
    i2s->bajarVolumen();
    pan.mostrarVolumen(i2s->getGain());
    delay(300); // debounce y evitar bajadas muy rápidas
  }
}
