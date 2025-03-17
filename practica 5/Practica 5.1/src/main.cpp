#include <Arduino.h>
#include <Wire.h>

#define SDA_PIN 8
#define SCL_PIN 9
void setup() {
    Wire.begin();               // Inicializa el bus I2CSDA_PIN,SCL_PIN
    Serial.begin(115200);       // Inicia la comunicación serie a 115200 baudios
    while (!Serial);            // Espera hasta que el puerto serie esté listo (solo necesario en algunas placas)
    Serial.println("\nI2C Scanner");
}

void loop() {
    byte error, address;
    int nDevices = 0;           // Contador de dispositivos I2C encontrados

    Serial.println("Scanning...");

    // Recorre todas las direcciones I2C posibles (de 1 a 127)
    for (address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();  // Comprueba si hay respuesta del dispositivo

        if (error == 0) {
            Serial.print("I2C device found at address 0x");
            if (address < 16) Serial.print("0"); // Formato correcto para valores menores a 0x10
            Serial.print(address, HEX);
            Serial.println(" !");
            nDevices++;
        }
        else if (error == 4) {
            Serial.print("Unknown error at address 0x");
            if (address < 16) Serial.print("0");
            Serial.println(address, HEX);
        }
    }

    // Mensaje si no se encontraron dispositivos
    if (nDevices == 0) {
        Serial.println("No I2C devices found\n");
    } else {
        Serial.println("Scanning complete\n");
    }

    delay(5000);  // Espera 5 segundos antes de realizar otro escaneo
}
