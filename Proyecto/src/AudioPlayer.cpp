#include "AudioPlayer.h"
#include <driver/i2s.h>
#include <SD.h>

AudioPlayer::AudioPlayer(int bclkPin, int lrclkPin, int doutPin)
    : bclk(bclkPin), lrclk(lrclkPin), dout(doutPin) {}

void AudioPlayer::begin() {
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate = 44100,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = I2S_COMM_FORMAT_I2S_MSB,
        .intr_alloc_flags = 0,
        .dma_buf_count = 8,
        .dma_buf_len = 64,
        .use_apll = false,
        .tx_desc_auto_clear = true
    };

    i2s_pin_config_t pin_config = {
        .bck_io_num = bclk,
        .ws_io_num = lrclk,
        .data_out_num = dout,
        .data_in_num = I2S_PIN_NO_CHANGE
    };

    i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_NUM_0, &pin_config);
}

void AudioPlayer::playWAV(const char *filename) {
    File file = SD.open(filename);
    if (!file) return;

    uint8_t buffer[1024];
    while (file.available()) {
        int bytesRead = file.read(buffer, sizeof(buffer));
        size_t bytesWritten;
        i2s_write(I2S_NUM_0, buffer, bytesRead, &bytesWritten, portMAX_DELAY);
    }
    file.close();
}
