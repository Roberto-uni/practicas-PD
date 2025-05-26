#pragma once
#include <AudioOutputI2S.h>
#define I2S_DOUT 21  
#define I2S_BCLK 20
#define I2S_LRC  19


class I2S_Audio {
public:
    I2S_Audio(int bclk, int lrc, int dout, float gain );
    AudioOutputI2S* get();
    void subirVolumen();
    void bajarVolumen();
    float getGain() const { return gain; };
private:
    AudioOutputI2S* out;
    float gain ;
};
