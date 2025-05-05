#include <Arduino.h>
void setup() {
  Serial.begin(115200); // UART0 (PC)
  Serial2.begin(115200, SERIAL_8N1, 16, 17); // UART2

  Serial.println("ESP32 UART bridge iniciado");
}

void loop() {
  // Reenvía datos desde Serial (UART0) a UART2
  if (Serial.available()) {
    char c = Serial.read();
    Serial.print("[UART0->2]: ");
    Serial.println(c);        // Mostrar lo que se reenvía
    Serial2.write(c);
  }

  // Reenvía datos desde UART2 a UART0
  if (Serial2.available()) {
    char c = Serial2.read();
    Serial.print("[UART2->0]: ");
    Serial.println(c);        // Mostrar lo que regresa
    Serial.write(c);          // Eco en consola
  }
}


