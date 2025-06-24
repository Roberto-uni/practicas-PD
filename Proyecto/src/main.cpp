#include "WebRadio.h"
#include "I2S_Audio.h"
#include "wifi_connect.h"
#include "Pantalla_SPI.h"
#include "Lector_SD.h"

// Pines botones
#define BOTON_NEXT    15
#define BOTON_SUBIR   7
#define BOTON_PAUSA   6
#define BOTON_BAJAR   5
#define BOTON_PREV    4
#define BOTON_WEBoSD  19

// WiFi
wifi_connect* red;
const char* ssid = "DIGIFIBRA-EH74";
const char* password = "FCPTEX5t35";
uint16_t puerto = 80;

// Objetos compartidos
I2S_Audio* i2s;
WebRadio* radio;
Pantalla_SPI pan;
Lector_SD sd;

std::vector<String> listaCanciones;

// Estado compartido
bool webosd = false;                  // false = SD, true = web
volatile bool cambiarModo = false;
volatile int accionBoton = 0;         // 1=subirVol, 2=bajarVol, 3=pausa, 4=siguiente, 5=anterior


// ======== TAREAS RTOS ==========

void tareaBotones(void* pvParameters) {
  for (;;) {
    if (digitalRead(BOTON_WEBoSD) == LOW) {
      if(webosd){
        pan.limpiar();
        pan.mostrarNombreEstacion("Pasando a Local");
        pan.mostrarNombreCancion("reiniciando sistema");
        delay(2500);
        ESP.restart();}
      webosd = !webosd;
      cambiarModo = true;
      vTaskDelay(300 / portTICK_PERIOD_MS);
    }

    if (digitalRead(BOTON_SUBIR) == LOW)  accionBoton = 1;
    if (digitalRead(BOTON_BAJAR) == LOW)  accionBoton = 2;
    if (!webosd && digitalRead(BOTON_PAUSA) == LOW) accionBoton = 3;
    if (digitalRead(BOTON_NEXT) == LOW)   accionBoton = 4;
    if (!webosd && digitalRead(BOTON_PREV) == LOW)   accionBoton = 5;

    vTaskDelay(300 / portTICK_PERIOD_MS); // Anti-rebote
  }
}

void tareaAudio(void* pvParameters) {
  for (;;) {
    if (cambiarModo) {
      cambiarModo = false;

      Serial.println("🔄 Cambiar modo");

      if (i2s && i2s->isPlaying()) Serial.println("deteniendo rep local");i2s->stop();
      
      if (webosd) {
        pan.limpiar();
        pan.mostrarNombreEstacion("Reproduciendo Web");
        pan.mostrarNombreCancion(WiFi.localIP().toString());
      } 
      /*else {
        temp = 0;
        pan.limpiar();
        if (radio) {
          radio->detener();
          pan.mostrarNombreEstacion("terminando transmision web");
          
          vTaskDelay(100 / portTICK_PERIOD_MS);
        }
        if (i2s) {
          i2s->begin_SD(listaCanciones, 0);
          pan.limpiar();
          pan.mostrarNombreEstacion("Reproduciendo SD");
          pan.mostrarNombreCancion(i2s->getNombreCancionActual());
          pan.mostrarEstadoReproduccion(i2s->isPaused());
        } else {
          Serial.println("⚠️ i2s es NULL, no se puede iniciar reproducción SD");
        }
        }*/
    }

    // Acciones de botones
    switch (accionBoton) {
      case 1:
        if (i2s) {
          i2s->subirVolumen();
          pan.mostrarVolumen(i2s->getGain());
        }
        break;
      case 2:
        if (i2s) {
          i2s->bajarVolumen();
          pan.mostrarVolumen(i2s->getGain());
        }
        break;
      case 3:
        if (i2s) {
          i2s->Pausa();
          pan.mostrarEstadoReproduccion(i2s->isPaused());
        }
        break;
      case 4:
        if (i2s) {
          i2s->siguienteCancion();
          pan.mostrarNombreCancion(i2s->getNombreCancionActual());
          pan.mostrarEstadoReproduccion(i2s->isPaused());
        }
        break;
      case 5:
        if (i2s) {
          i2s->AnteriorCancion();
          pan.mostrarNombreCancion(i2s->getNombreCancionActual());
          pan.mostrarEstadoReproduccion(i2s->isPaused());
        }
        break;
    }
    accionBoton = 0;

    // Loop de reproducción
    if (webosd) {
      if (radio) {
        radio->manejarClientes();
      } else {
        Serial.println("⚠️ radio es NULL, no se puede manejar clientes web");
      }
    } else {
      if (i2s) {
        i2s->loop_SD();
      } else {
        Serial.println("⚠️ i2s es NULL, no se puede reproducir SD");
      }
    }

    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}


void tareaPantalla(void* pvParameters) {
  for (;;) {
    if (!webosd && i2s->isPlaying() && !i2s->isPaused()) {
      uint32_t actual = i2s->getTiempoActual();
      pan.mostrarTiempo(actual);
    }

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

// ========= SETUP Y LOOP PRINCIPALES ============

void setup() {
  Serial.begin(115200);

  // Inicializaciones
  red = new wifi_connect();
  i2s = new I2S_Audio(I2S_BCLK, I2S_LRC, I2S_DOUT);

  pan.iniciar();
  sd.iniciar();
  pan.mostrarTexto("Iniciando SD", 20);
  delay(1000);

  red->conectar(ssid, password, pan);

  // Configurar botones
  pinMode(BOTON_NEXT, INPUT_PULLUP);
  pinMode(BOTON_SUBIR, INPUT_PULLUP);
  pinMode(BOTON_PAUSA, INPUT_PULLUP);
  pinMode(BOTON_BAJAR, INPUT_PULLUP);
  pinMode(BOTON_PREV, INPUT_PULLUP);
  pinMode(BOTON_WEBoSD, INPUT_PULLUP);

  // Obtener canciones
  listaCanciones = sd.obtenerListaCanciones();
  if (listaCanciones.empty()) {
    pan.mostrarTexto("No hay canciones en SD", 20);
    Serial.println("No se encontraron canciones en la SD");
    while (true); // Stop
  }

  // Inicializar radio 
  radio = new WebRadio(sd, puerto);
  radio->iniciar();

  // Iniciar reproducción SD por defecto
  i2s->begin_SD(listaCanciones, 0);
  pan.mostrarVolumen(i2s->getGain());
  pan.mostrarNombreCancion(i2s->getNombreCancionActual());
  pan.mostrarNombreEstacion("Reproduciendo SD");

  // Crear tareas
  xTaskCreatePinnedToCore(tareaBotones, "Botones", 2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(tareaAudio, "Audio", 4096, NULL, 2, NULL, 1);
  xTaskCreatePinnedToCore(tareaPantalla, "Pantalla", 2048, NULL, 1, NULL, 0);
}

void loop() {
  // Nada en loop, usamos RTOS
  vTaskDelay(portMAX_DELAY);
}
