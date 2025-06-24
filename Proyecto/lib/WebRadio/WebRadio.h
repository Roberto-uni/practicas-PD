#ifndef WEBRADIO_H
#define WEBRADIO_H

#include <WebServer.h>
#include "Lector_SD.h"

class WebRadio {
public:
    // Recibe referencia a Lector_SD externo y puerto del servidor (default 80)
    WebRadio(Lector_SD& lectorSd, uint16_t puerto);

    void iniciar();
    void manejarClientes();

    bool estaTransmitiendo = false;

private:
    WebServer server;
    Lector_SD& lector;  // Referencia a objeto externo

    void manejarRaiz();
    void manejarStream();
};

#endif // WEBRADIO_H

