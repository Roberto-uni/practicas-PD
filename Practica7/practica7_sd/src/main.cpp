#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <AudioFileSourceSD.h>
#include <AudioGeneratorMP3.h>
#include <AudioOutputI2S.h>

// Pines del lector SD
#define SD_MISO 36
#define SD_MOSI 35
#define SD_SCK  37
#define SD_CS   38

// Pines I2S para MAX98357A
#define I2S_BCLK 41
#define I2S_LRCK 42
#define I2S_DOUT 40

// Objetos de audio
AudioGeneratorMP3 *mp3;
AudioFileSourceSD *file;
AudioOutputI2S *out;

SPIClass spiSD(FSPI);  // Utiliza FSPI en ESP32-S3

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Inicializando...");

  // Inicializa el bus SPI con pines personalizados
  spiSD.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);

  // Inicializa la tarjeta SD
  if (!SD.begin(SD_CS, spiSD)) {
    Serial.println("❌ Error al inicializar la tarjeta SD.");
    while (true);
  }
  Serial.println("✅ Tarjeta SD inicializada.");

  // Inicializa salida de audio I2S
  out = new AudioOutputI2S();
  out->SetPinout(I2S_BCLK, I2S_LRCK, I2S_DOUT);
  out->SetGain(0.8);  // Volumen

  // Cargar archivo MP3
  file = new AudioFileSourceSD("/Korn_Blind.mp3");
  mp3 = new AudioGeneratorMP3();
  mp3->begin(file, out);

  Serial.println("🎵 Reproduciendo audio...");
}

void loop() {
  if (mp3->isRunning()) {
    mp3->loop();
  } else {
    Serial.println("✅ Reproducción finalizada.");
    delay(2000);
  }
}
