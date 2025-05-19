#pragma once
#include <Arduino.h>

class AudioPlayer {
public:
    AudioPlayer(int bclkPin, int lrclkPin, int doutPin);
    void begin();
    void playWAV(const char *filename);  // From SD

private:
    int bclk, lrclk, dout;
};
