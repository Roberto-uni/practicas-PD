/*
    An example of how to authenticate with Spotify without using a refresh token and print Artist and Track via Serial

In this example your current track will be printed to the serial and as soon as you listen to a new track that tracks information will be printed.

    15.03.2024
    Created by: Finian Landes

    16.03.2024
    edited by: Sascha Seidel
        * added getting artist and trackname to print it Serial

    Documentation: https://github.com/FinianLandes/Spotify_Esp32
*/
// Include the required libraries
#include <Arduino.h>
#include <WiFi.h>
#include <SpotifyEsp32.h>

const char* SSID = "RedmiNote7";
const char* PASSWORD = "estacosa";
const char* CLIENT_ID = "c189e3a1cdb14e83b53a7b571f17243e";
const char* CLIENT_SECRET = "22b848a4fd0840e4af0787d6c1f70bb6" ;
const char* REFRESH_TOKEN = "AQBAxm5gwwGp2W_NQyFQLxNll_1L0bX02yfjqbRdEaH2Z0lE5tQTxSznikAsBe6DxEB2BSkhBmBPb2niWJtapaQyYXjpWYTVbgQCAz41WBv54ZjMoe3qPPNsazp-D2eeaPo";

Spotify sp(CLIENT_ID, CLIENT_SECRET);

void connect_to_wifi();

void setup() {
    Serial.begin(115200);
    connect_to_wifi();
    
    sp.begin();
    while(!sp.is_auth()){
        sp.handle_client();
    }
    Serial.println("Authenticated");
}

void loop() {
    static String lastArtist;
    static String lastTrackname;
    
    String currentArtist = sp.current_artist_names();
    String currentTrackname = sp.current_track_name();
    
    if (lastArtist != currentArtist && currentArtist != "Something went wrong" && !currentArtist.isEmpty()) {
        lastArtist = currentArtist;
        Serial.println("Artist: " + lastArtist);
    }
    
    if (lastTrackname != currentTrackname && currentTrackname != "Something went wrong" && currentTrackname != "null") {
        lastTrackname = currentTrackname;
        Serial.println("Track: " + lastTrackname);
    }
}

void connect_to_wifi(){
    WiFi.begin(SSID, PASSWORD);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.printf("\nConnected to WiFi\n");
}
