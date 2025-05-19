#include "SpotifyClient.h"

SpotifyClient::SpotifyClient(const char* clientId, const char* clientSecret, const char* refreshToken, const char* deviceName) {
    spotify = new Spotify(clientId, clientSecret, refreshToken, deviceName);
    client.setInsecure(); // Usa certificado si prefieres seguridad TLS
    spotify->setClient(&client);
}

bool SpotifyClient::connect() {
    return spotify->checkAndRefreshAccessToken();
}

bool SpotifyClient::updateCurrentSong() {
    if (!spotify->getCurrentlyPlaying()) {
        return false;
    }

    songName = spotify->currentlyPlaying.trackName;
    artistName = spotify->currentlyPlaying.artists[0];
    progressMs = spotify->currentlyPlaying.progressMs;
    durationMs = spotify->currentlyPlaying.durationMs;

    return true;
}

String SpotifyClient::getSongName() const {
    return songName;
}

String SpotifyClient::getArtistName() const {
    return artistName;
}

int SpotifyClient::getProgressMs() const {
    return progressMs;
}

int SpotifyClient::getDurationMs() const {
    return durationMs;
}
