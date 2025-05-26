#include <Arduino.h>
#include <unity.h>

extern void test_wifi_connect();
extern void test_Pantalla_SPI();
extern void test_lector_sd();
extern void test_I2S_Radio();

void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}


void setup() {
  Serial.begin(115200);
  delay(1000);

  UNITY_BEGIN();

  Serial.print("prueba sd");
  test_lector_sd();
  
  Serial.print("prueba pantalla");
  test_Pantalla_SPI();
  

   Serial.print("prueba wifi");
  test_wifi_connect();
  
  Serial.print("Prueba radio y audio");
  test_I2S_Radio();


  UNITY_END();
}

void loop() {
  // Nada
}
