#include "SDManager.h"
#include <SD.h>
#include <SPI.h>

SDManager::SDManager(int csPin) : cs(csPin) {}

bool SDManager::begin() {
    return SD.begin(cs);
}

bool SDManager::fileExists(const char *filename) {
    return SD.exists(filename);
}
