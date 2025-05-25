#pragma once
#include <TFT_eSPI.h>

class DisplayManager {
public:
    DisplayManager();
    void begin();
    void showTrack(const String &track);
    void showArtist(const String &artist);
    void showStatus(const String &status);

private:
    TFT_eSPI tft;
};
