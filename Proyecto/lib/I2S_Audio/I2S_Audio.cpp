#include "I2S_Audio.h"

I2S_Audio::I2S_Audio(int bclk, int lrc, int dout) {
    out = new AudioOutputI2S();
    out->SetPinout(bclk, lrc, dout);
    
}



/////////   Metodos Audio Web    /////////  

void I2S_Audio::begin_web( const char* streamURL) {
    wfile = new AudioFileSourceICYStream(streamURL);
    wfile->SetReconnect(5, 1000);
    mp3 = new AudioGeneratorMP3();
    mp3->begin(wfile, out);
}

void I2S_Audio::loop_web( const char* streamURL  ) {
    if (mp3 && !mp3->loop()) {
            Serial.println("Stream terminado o error. Reiniciando...");
            mp3->stop();
            delete mp3;

            wfile->close();
            delete wfile;
            begin_web(streamURL);
        
    }
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
    if (mp3 && mp3->isRunning()) {
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

uint32_t I2S_Audio::getDuracionEstimado() {
    if (canciones.empty()) return 0;
    String nombre = canciones[indiceActual];
    File archivo = SD.open("/" + nombre);
    if (!archivo) return 0;

    uint32_t tamanio = archivo.size();  // bytes
    archivo.close();

    const uint32_t bitrate = 8000; // 128 kbps = 16,000 bytes/s
    return tamanio / bitrate; // segundos aproximados
}



/////////   Metodos Generales    /////////    

bool I2S_Audio::isPaused() {
    return paused;
}

bool I2S_Audio::isPlaying() {
  return mp3 && mp3->isRunning();
}

String I2S_Audio::getNombreCancionActual() {
    if (canciones.empty()) return "";
    return canciones[indiceActual];
}

void I2S_Audio::stop() {
  if (mp3 && mp3->isRunning()) {
    mp3->stop();
    delete mp3;
    
  }

  if (wfile && mp3->isRunning()) {
    wfile->close();
    delete wfile;
    
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

void I2S_Audio::Pausa() {
    if (mp3 && mp3->isRunning()) {
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

uint32_t I2S_Audio::getTiempoActual() {
    if (paused) {
        return tiempoAcumulado;
    } else {
        return tiempoAcumulado + (millis() - tiempoInicio) / 1000;
    }
}




