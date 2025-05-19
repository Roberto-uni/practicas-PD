#include "DisplayManager.h"

DisplayManager::DisplayManager() {}

void DisplayManager::begin() {
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);
}

void DisplayManager::showTrack(const String &track) {
    tft.fillRect(0, 0, 240, 30, TFT_BLACK);
    tft.setCursor(0, 0);
    tft.print("Track: " + track);
}

void DisplayManager::showArtist(const String &artist) {
    tft.fillRect(0, 40, 240, 30, TFT_BLACK);
    tft.setCursor(0, 40);
    tft.print("Artist: " + artist);
}

void DisplayManager::showStatus(const String &status) {
    tft.fillRect(0, 80, 240, 30, TFT_BLACK);
    tft.setCursor(0, 80);
    tft.print("Time: " + status);
}
