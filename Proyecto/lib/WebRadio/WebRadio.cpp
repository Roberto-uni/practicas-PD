#include "WebRadio.h"

WebRadio::WebRadio(const char* url)
    : streamURL(url), file(nullptr), mp3(nullptr), out(nullptr) {}

void WebRadio::begin(AudioOutputI2S* output) {
    file = new AudioFileSourceICYStream(streamURL);
    file->SetReconnect(5, 1000);
    out = output;
    mp3 = new AudioGeneratorMP3();
    mp3->begin(file, out);
}

void WebRadio::loop() {
    if (mp3 && !mp3->loop()) {
        Serial.println("Stream terminado o error. Reiniciando...");
        mp3->stop();
        delete mp3;

        file->close();
        delete file;

        file = new AudioFileSourceICYStream(streamURL);
        file->SetReconnect(5, 1000);

        mp3 = new AudioGeneratorMP3();
        mp3->begin(file, out);
    }
}

void WebRadio::setOutput(AudioOutputI2S* audioOut) {
    out = audioOut;
}
