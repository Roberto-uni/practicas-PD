#include "AudioGeneratorAAC.h"
#include "AudioOutputI2S.h"
#include "AudioFileSourcePROGMEM.h"
#include "sampleaac.h"  // Asegúrate de que este archivo exista y contenga el audio en formato AAC

AudioFileSourcePROGMEM *in;
AudioGeneratorAAC *aac;
AudioOutputI2S *out;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Inicializa fuente de audio desde memoria PROGMEM
  in = new AudioFileSourcePROGMEM(sampleaac, sizeof(sampleaac));

  // Inicializa salida I2S
  out = new AudioOutputI2S();
  out->SetGain(0.125);            // volumen (0.0 a 1.0)
  out->SetPinout(41, 42, 40);     // BCLK, LRCLK, DIN

  // Inicializa decodificador AAC
  aac = new AudioGeneratorAAC();
  aac->begin(in, out);
}

void loop() {
  if (aac->isRunning()) {
    aac->loop();
  } else {
    aac->stop();
    Serial.println("Reproducción terminada.");
    delay(1000);
  }
}
