#pragma once
#include <AudioOutputI2S.h>
#include <AudioFileSourceICYStream.h>
#include "AudioFileSourceSD.h"
#include <AudioGeneratorMP3.h>
#include <AudioOutputI2S.h>  
#include <vector>

#define I2S_DOUT 40
#define I2S_BCLK 41
#define I2S_LRC  42

class I2S_Audio {
public:
    I2S_Audio(int bclk, int lrc, int dout);

    //metodos web
    void begin_web( const char* streamURL);
    void loop_web(const char* url  ) ;

    //metodos sd
    void begin_SD( const std::vector<String>& lista, int index);
    void loop_SD(  ) ;
    void siguienteCancion();
    void AnteriorCancion();
    String getNombreCancionActual();
    uint32_t getTiempoActual();   // tiempo transcurrido en segundos
    uint32_t getDuracionEstimado();



    AudioOutputI2S* get();
    void stop();

    bool isPlaying();
    bool isPaused();

    void subirVolumen();
    void bajarVolumen();
    void Pausa();

    float getGain() const { return gain; };

private:
    AudioFileSourceICYStream* wfile;//para gestionar la reproduccion de audio desde una https
    AudioFileSourceSD* sfile; //para gestionar la reproduccion de audio desde una sd

    AudioGeneratorMP3* mp3;
    AudioOutputI2S* out;
    float gain = 1.5 ;
    bool paused = false;

    //----- vector para poder pasar de cancion-------
    std::vector<String> canciones;
    int indiceActual = 0;
    private:
     unsigned long tiempoInicio = 0;    // millis() en que empezó la canción
    uint32_t tiempoAcumulado = 0;      // segundos acumulados antes de pausar

};
