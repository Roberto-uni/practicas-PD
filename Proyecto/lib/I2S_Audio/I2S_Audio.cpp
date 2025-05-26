#include "I2S_Audio.h"

I2S_Audio::I2S_Audio(int bclk, int lrc, int dout, float gain) {
    out = new AudioOutputI2S();
    out->SetPinout(bclk, lrc, dout);
    out->SetGain(gain);
}

AudioOutputI2S* I2S_Audio::get() {
    return out;
}

void I2S_Audio::subirVolumen() {
    gain += 0.1f;
    if (gain > 1.0f) gain = 1.0f;
    out->SetGain(gain);
    Serial.println(String("subiendo volumen: ") + gain);
}

void I2S_Audio::bajarVolumen() {
    
    gain -= 0.1f;
    if (gain < 0.0f) gain = 0.0f;
    out->SetGain(gain);
    Serial.println(String("Bajando volumen: ") + gain);
;
}

