#include "WebRadio.h"

WebRadio::WebRadio(Lector_SD& lectorSd, uint16_t puerto) 
    : server(puerto), lector(lectorSd) {}

void WebRadio::iniciar() {
    server.on("/", [this]() { manejarRaiz(); });
    server.on("/stream", [this]() { manejarStream(); });

    server.begin();
    Serial.println("Servidor web iniciado.");
}

void WebRadio::manejarClientes() {
    server.handleClient();
    delay(100);
}

void WebRadio::manejarRaiz() {
    std::vector<String> canciones = lector.obtenerListaCanciones();
    String html = R"rawliteral(
    <!DOCTYPE html>
    <html>
    <head>
      <meta name="viewport" content="width=device-width, initial-scale=1">
      <style>
        body {
          background: #1e1e2f; color: #fff; font-family: sans-serif;
          display: flex; flex-direction: column; align-items: center;
          padding: 30px;
        }
        h1 { margin-bottom: 20px; }
        ul { list-style: none; padding: 0; }
        li { margin: 10px 0; }
        a {
          color: #90caf9;
          text-decoration: none;
          font-size: 18px;
        }
        audio { margin-top: 30px; width: 80%; }
        #nowPlaying {
          margin-top: 10px;
          font-size: 16px;
          color: #b0bec5;
        }
      </style>
    </head>
    <body>
      <h1> Reproductor MP3 Web</h1>
      <ul>
    )rawliteral";

    for (const String& nombre : canciones) {
        html += "<li><a href=\"#\" onclick=\"playSong('" + nombre + "')\">" + nombre + "</a></li>";
    }

    html += R"rawliteral(
      </ul>
      <audio id="player" controls>
        <source id="audioSource" src="" type="audio/mpeg">
        Tu navegador no soporta el elemento <code>audio</code>.
      </audio>
      <div id="nowPlaying"></div>
      <script>
        function playSong(filename) {
          const player = document.getElementById("player");
          const source = document.getElementById("audioSource");
          const nowPlaying = document.getElementById("nowPlaying");

          source.src = "/stream?file=" + filename;
          player.load();
          player.play();
          nowPlaying.textContent = "Reproduciendo: " + filename;
        }
      </script>
    </body>
    </html>
    )rawliteral";

    server.send(200, "text/html", html);
}

void WebRadio::manejarStream() {
    if (!server.hasArg("file")) {
        server.send(400, "text/plain", "Falta argumento 'file'");
        return;
    }

    String ruta = "/" + server.arg("file");
    File archivo = SD.open(ruta.c_str(), FILE_READ);

    if (!archivo) {
        server.send(404, "text/plain", "Archivo no encontrado");
        return;
    }

    server.streamFile(archivo, "audio/mpeg");
    archivo.close();
}
