#pragma once
#include <Arduino.h>

class SDManager {
public:
    SDManager(int csPin);
    bool begin();
    bool fileExists(const char *filename);

private:
    int cs;
};
