#include "I2S_Audio.h"

I2S_Audio::I2S_Audio(int bclk, int lrc, int dout) {
    out = new AudioOutputI2S();
    out->SetPinout(bclk, lrc, dout);
    
}


/////////   Metodos Audio SD    /////////  

void I2S_Audio::begin_SD(const std::vector<String>& lista, int index) {
    canciones = lista;
    indiceActual = index % canciones.size();
    tiempoInicio = millis();
    tiempoAcumulado = 0;

    sfile = new AudioFileSourceSD(("/" + canciones[indiceActual]).c_str());
    mp3 = new AudioGeneratorMP3();

    if (!mp3->begin(sfile, out)) {
        Serial.println("Error al iniciar el decodificador MP3.");
        while (true) delay(1000);
    }

    paused = false;
    Serial.println("Reproduciendo: " + canciones[indiceActual]);
}

void I2S_Audio::loop_SD(  ){
    
    if (paused) {
        return;  // No hacer nada si está en pausa
    }
    if (isPlaying()) {
        if (!mp3->loop()) {
            mp3->stop();
        Serial.println("Reproducción finalizada.");
        }
    } 
    else {
        delay(1000);
    }
}

void I2S_Audio::siguienteCancion() {
    if (canciones.empty()) return;

    indiceActual = (indiceActual + 1) % canciones.size();  // vuelve al inicio si llega al final
    stop();
    begin_SD(canciones, indiceActual);  // Reproduce siguiente
}

void I2S_Audio::AnteriorCancion() {
    if (canciones.empty()) return;

    if (indiceActual == 0) {
        indiceActual = canciones.size() - 1;
    } else {
        indiceActual--;
    }
    stop();
    begin_SD(canciones, indiceActual);  // Reproduce siguiente
}

void I2S_Audio::Pausa() {
    if (isPlaying()) {
        paused = !paused;
        if (paused) {
            tiempoAcumulado += (millis() - tiempoInicio) / 1000;
            Serial.println("⏸ Pausado");
        } else {
            tiempoInicio = millis();
            Serial.println("▶ Reanudado");
        }
    }
}

String I2S_Audio::getNombreCancionActual() {
    if (canciones.empty()) return "";
    return canciones[indiceActual];
}

/////////   Metodos Generales    /////////    

bool I2S_Audio::isPaused() {
    return paused;
}

bool I2S_Audio::isPlaying() {
  return mp3 && mp3->isRunning();
}



void I2S_Audio::stop() {
  if (isPlaying() && mp3) {
    mp3->stop();
    delete mp3;
    
  }

  

  if (sfile && mp3->isRunning()) {
    sfile->close();
    delete sfile;
    
  }
}

void I2S_Audio::subirVolumen() {
    gain += 0.3;
    if (gain > 3.0) gain = 3.0;
    out->SetGain(gain);
    Serial.println(String("subiendo volumen: ") + gain);
}

void I2S_Audio::bajarVolumen() {
    
    gain -= 0.3;
    if (gain < 0.0) gain = 0.0;
    out->SetGain(gain);
    Serial.println(String("Bajando volumen: ") + gain);
;
}



uint32_t I2S_Audio::getTiempoActual() {
    if (paused) {
        return tiempoAcumulado;
    } else {
        return tiempoAcumulado + (millis() - tiempoInicio) / 1000;
    }
}




