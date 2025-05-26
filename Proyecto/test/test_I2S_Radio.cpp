#include <Arduino.h>
#include <unity.h>
#include "WebRadio.h"
#include "I2S_Audio.h"

// Pines I2S simulados (no se inicializarán hardware real en test)
#define I2S_DOUT 21
#define I2S_BCLK 20
#define I2S_LRC  19

// URL de stream para test
const char* testStreamURL = "http://media-ice.musicradio.com/ClassicFMMP3";

I2S_Audio* i2sAudio;
WebRadio* webRadio;

void test_i2s_initial_gain() {
    i2sAudio = new I2S_Audio(I2S_BCLK, I2S_LRC, I2S_DOUT, 0.5);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.5, i2sAudio->getGain());
    delete i2sAudio;
}

void test_i2s_volume_up_down() {
    i2sAudio = new I2S_Audio(I2S_BCLK, I2S_LRC, I2S_DOUT, 0.5);
    i2sAudio->subirVolumen();
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.6, i2sAudio->getGain());
    i2sAudio->bajarVolumen();
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.5, i2sAudio->getGain());
    delete i2sAudio;
}

void test_webradio_set_output() {
    webRadio = new WebRadio(testStreamURL);
    i2sAudio = new I2S_Audio(I2S_BCLK, I2S_LRC, I2S_DOUT, 0.5);

    webRadio->setOutput(i2sAudio->get());
    TEST_ASSERT_NOT_NULL(i2sAudio->get());


    delete webRadio;
    delete i2sAudio;
}

void test_webradio_begin_loop() {
    webRadio = new WebRadio(testStreamURL);
    i2sAudio = new I2S_Audio(I2S_BCLK, I2S_LRC, I2S_DOUT, 0.5);

    webRadio->setOutput(i2sAudio->get());

    // No esperamos que falle en begin
    bool started = webRadio->begin(i2sAudio->get());
    TEST_ASSERT_TRUE(started);

    // Llamar loop no debe fallar
    webRadio->loop();

    delete webRadio;
    delete i2sAudio;
}

void test_I2S_Radio() {
    RUN_TEST(test_i2s_initial_gain);
    RUN_TEST(test_i2s_volume_up_down);
    RUN_TEST(test_webradio_set_output);
    RUN_TEST(test_webradio_begin_loop);
}

