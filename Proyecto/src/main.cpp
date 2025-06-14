#include "WebRadio.h"
#include "I2S_Audio.h"
#include "wifi_connect.h"
#include "Pantalla_SPI.h"
#include "Lector_SD.h"

// Pines botones
#define BOTON_NEXT 15  // BOTON SIGUIENTE CANCION/ESTACION
#define BOTON_SUBIR 7 // BOTON PARA SUBIR EL VOLUMEN
#define BOTON_PAUSA 6 // BOTON PARA PAUSAR/REANUDAR LA REPRODUCCION
#define BOTON_BAJAR 5 // BOTON PARA BAJAR VOLUMEN
#define BOTON_PREV 4 // BOTON VOLVER CANCION/ESTACION

#define BOTON_WEBoSD 19 // BOTON VOLVER CANCION/ESTACION
// WiFi
wifi_connect* red;
const char* ssid = "DIGIFIBRA-EH74"; //DIGIFIBRA-EH74    RedmiNote7
const char* password = "FCPTEX5t35"; // FCPTEX5t35      estacosa


// Stream
const char* streamURL = "http://media-ice.musicradio.com/ClassicFMMP3";
const char* cancion = "/Korn_Blind.mp3";

// Reproduccion desde web o desde SD
bool webosd = false;  // false == SD, true == web
std::vector<String> listaCanciones;

//Mostrar tiempo pantalla
unsigned long ultimoTiempoActual = 0;
unsigned long ultimoUpdateMillis = 0;

// Objetos
I2S_Audio* i2s;
WebRadio* radio;
Pantalla_SPI pan;
Lector_SD sd;

void setup() {
  Serial.begin(115200);
  pan.iniciar();
  sd.iniciar();
  pan.mostrarTexto("iniciando sd",20);
  delay(1000);
  red->conectar(ssid, password,pan);

  //asignacion de pines de botones
  pinMode(BOTON_NEXT, INPUT_PULLUP);
  pinMode(BOTON_SUBIR, INPUT_PULLUP);
  pinMode(BOTON_PAUSA, INPUT_PULLUP);
  pinMode(BOTON_BAJAR, INPUT_PULLUP);
  pinMode(BOTON_PREV, INPUT_PULLUP);
  pinMode(BOTON_WEBoSD, INPUT_PULLUP);

  i2s = new I2S_Audio(I2S_BCLK, I2S_LRC, I2S_DOUT);
  

  pan.mostrarTexto("iniciando sd",20);
  pan.mostrarVolumen(i2s->getGain());
  Serial.println("prueba1");

  listaCanciones = sd.obtenerListaCanciones();
  Serial.println("prueba2");

  i2s->begin_SD(listaCanciones, 0);
  Serial.println("prueba3");

  pan.mostrarNombreCancion(i2s->getNombreCancionActual());
  pan.mostrarNombreEstacion("Reproduciendo desde SD");
  
}

void loop() {

  // Cambiar modo SD/Web
  if (digitalRead(BOTON_WEBoSD) == LOW) {
    webosd = !webosd;
    Serial.println("webos");

    // Detener reproducción actual
    if (i2s->isPlaying()) {
      i2s->stop();  
    }

    // Iniciar nuevo modo
    if (webosd) {
      i2s->begin_web(streamURL);
      pan.limpiar();
      pan.mostrarNombreEstacion("ClassicFMMP3");
    } else {
      i2s->begin_SD(listaCanciones, 0);
      pan.mostrarNombreCancion(i2s->getNombreCancionActual());
      pan.limpiar();
      pan.mostrarNombreEstacion("Reproduciendo desde SD");
      pan.mostrarNombreCancion(i2s->getNombreCancionActual());
      pan.mostrarEstadoReproduccion(i2s->isPaused());
    }

    delay(300); // Evita múltiples cambios por rebote
  }

  // Ejecutar loop según el modo actual
  if (webosd) {
    i2s->loop_web(streamURL);
  } else {
    i2s->loop_SD(cancion);
  }

  // Controles de volumen
  if (digitalRead(BOTON_SUBIR) == LOW) {
    i2s->subirVolumen();
    pan.mostrarVolumen(i2s->getGain());
    delay(300); 
  }

  if (digitalRead(BOTON_BAJAR) == LOW) {
    i2s->bajarVolumen();
    pan.mostrarVolumen(i2s->getGain());
    delay(300); 
  }

  // Pausar/Reanudar solo si se está en SD
  if (!webosd && digitalRead(BOTON_PAUSA) == LOW) {
   i2s->Pausa();
   pan.mostrarEstadoReproduccion(i2s->isPaused());
   delay(300);
  }

  //Cambiar de cancion
  // Siguiente canción (solo en modo SD)
  if ((!webosd && digitalRead(BOTON_NEXT) == LOW) || !i2s->isPlaying() ) {
    i2s->siguienteCancion();
    pan.mostrarNombreCancion(i2s->getNombreCancionActual());
    pan.mostrarEstadoReproduccion(i2s->isPaused());
    delay(300);
  }

  if (!webosd && digitalRead(BOTON_PREV) == LOW) {
    i2s->AnteriorCancion();
    pan.mostrarNombreCancion(i2s->getNombreCancionActual());
    pan.mostrarEstadoReproduccion(i2s->isPaused());
    delay(300);
  }
  
static unsigned long ultimaActualizacion = 0;
if (!webosd && millis() - ultimaActualizacion >= 1000 && i2s->isPlaying()) {
  uint32_t actual = i2s->getTiempoActual();
  uint32_t total = 0;
  if (!i2s->isPaused()){
    pan.mostrarTiempo(actual, total);
  }
  
  ultimaActualizacion = millis();
}


}



