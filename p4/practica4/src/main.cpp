#include <Arduino.h>

const int led1 = 2; // pin del LED

void toggleLED(void * parameter) {
Serial.print("Task toggleLED is running on: ");
Serial.println(xPortGetCoreID());
  for (;;) {
    // Encender el LED
    digitalWrite(led1, HIGH);
    Serial.println("on");
    // Pausar la tarea por 500 ms
    vTaskDelay(500 / portTICK_PERIOD_MS);

    // Apagar el LED
    digitalWrite(led1, LOW);
    Serial.println("off");
    // Pausar la tarea por otros 500 ms
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void uploadToAWS(void * parameter) {
  // Implementa tu lógica personalizada para la tarea aquí
  Serial.print("Task uploadToAWS is running on: ");
  Serial.println(xPortGetCoreID());
  Serial.println("Subiendo datos a AWS...");
  
  // Simula trabajo o realiza la lógica de la tarea
  delay(2000);  // Solo como ejemplo

  // Cuando hayas terminado, elimina la tarea si ya no es necesaria
  vTaskDelete(NULL);
}

void setup() {
  Serial.begin(115200);
  pinMode(led1, OUTPUT);

  // Crear tarea para alternar el LED
  xTaskCreate(
    toggleLED,         // Función de la tarea
    "Toggle LED",      // Nombre de la tarea
    1000,              // Tamaño del stack (en palabras)
    NULL,              // Parámetro de la tarea
    1,                 // Prioridad de la tarea
    NULL               // Manejador de la tarea (no se necesita aquí)
  );

  // Crear tarea para subir a AWS, asignada al núcleo 0
  xTaskCreatePinnedToCore(
    uploadToAWS,       // Función de la tarea
    "Upload to AWS",   // Nombre de la tarea
    1000,              // Tamaño del stack (en palabras)
    NULL,              // Parámetro de la tarea
    1,                 // Prioridad de la tarea
    NULL,              // Manejador de la tarea (no se necesita aquí)
    0                  // Asignar a CPU0
  );
}

void loop() {
  
  delay(1000); // Puedes dejar esto o eliminarlo, no afecta a las tareas de FreeRTOS
}


