#include <Arduino.h>

// Definimos el pin del LED
const int ledPin = 2;  // Asegúrate de que el LED esté conectado a este pin

// Declaramos un semáforo binario
SemaphoreHandle_t semaforo;

void encenderLED(void * parameter) {
  for (;;) {
    // Espera a que el semáforo esté disponible
    if (xSemaphoreTake(semaforo, portMAX_DELAY) == pdTRUE) {
      // Encender el LED
      digitalWrite(ledPin, HIGH);  // Encender el LED
      Serial.println("LED Encendido");
      // Pausar la tarea por 500ms
      vTaskDelay(500 / portTICK_PERIOD_MS);
      // Liberar el semáforo para que la otra tarea pueda apagar el LED
      
      xSemaphoreGive(semaforo);
      vTaskDelay(10 / portTICK_PERIOD_MS);
    }
  }
}

void apagarLED(void * parameter) {
  for (;;) {
    // Espera a que el semáforo esté disponible
    if (xSemaphoreTake(semaforo, portMAX_DELAY) == pdTRUE) {
      // Apagar el LED
      digitalWrite(ledPin, LOW);  // Apagar el LED
      Serial.println("LED Apagado");
      // Pausar la tarea por 500ms
      vTaskDelay(500 / portTICK_PERIOD_MS);
      // Liberar el semáforo para que la otra tarea pueda encender el LED
      xSemaphoreGive(semaforo);
      vTaskDelay(10 / portTICK_PERIOD_MS);
    }
  }
}

void setup() {
  // Iniciar comunicación serial
  Serial.begin(115200);

  // Configurar el pin del LED como salida
  pinMode(ledPin, OUTPUT);

  // Crear el semáforo binario. Inicialmente está disponible (1)
  semaforo = xSemaphoreCreateBinary();
  xSemaphoreGive(semaforo);  // Inicialmente lo damos para que la tarea de encendido pueda comenzar

  // Crear las tareas
  xTaskCreate(encenderLED, "Encender LED", 1000, NULL, 1, NULL);
  xTaskCreate(apagarLED, "Apagar LED", 1000, NULL, 1, NULL);
}

void loop() {}
