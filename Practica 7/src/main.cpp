#include <Arduino.h>
#include <driver/i2s.h>
#include <math.h>

#define I2S_NUM         I2S_NUM_0
#define SAMPLE_RATE     44100
#define TONE_FREQ       440
#define I2S_BCLK        41
#define I2S_LRCLK       42
#define I2S_DOUT        40

#define PI              3.14159265
#define VOLUME          0.3  // 0.0 a 1.0

void setupI2S() {
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags = 0,
    .dma_buf_count = 8,
    .dma_buf_len = 64,
    .use_apll = false,
    .tx_desc_auto_clear = true,
    .fixed_mclk = 0
  };

  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_BCLK,
    .ws_io_num = I2S_LRCLK,
    .data_out_num = I2S_DOUT,
    .data_in_num = I2S_PIN_NO_CHANGE
  };

  i2s_driver_install(I2S_NUM, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM, &pin_config);
  i2s_zero_dma_buffer(I2S_NUM);
}

void generateTone() {
  const int samples = SAMPLE_RATE / TONE_FREQ;
  int16_t buffer[samples];

  for (int i = 0; i < samples; i++) {
    float sample = sinf(2 * PI * i / samples);
    buffer[i] = (int16_t)(sample * 32767 * VOLUME);  // 16-bit PCM
  }

  while (true) {
    size_t bytes_written;
    i2s_write(I2S_NUM, buffer, sizeof(buffer), &bytes_written, portMAX_DELAY);
  }
}

void setup() {
  Serial.begin(115200);
  setupI2S();
  delay(500);
  generateTone();
}

void loop() {
  // Nada aquí, el tono se genera en bucle
}


