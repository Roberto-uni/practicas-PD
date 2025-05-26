#pragma once
#include <AudioFileSourceICYStream.h>
#include <AudioGeneratorMP3.h>
#include <AudioOutputI2S.h>

class WebRadio {
public:
    WebRadio(const char* url);
    void begin(AudioOutputI2S* output);
    void loop();
    void setOutput(AudioOutputI2S* audioOut);

private:
    const char* streamURL;
    AudioFileSourceICYStream* file;
    AudioGeneratorMP3* mp3;
    AudioOutputI2S* out;
};
