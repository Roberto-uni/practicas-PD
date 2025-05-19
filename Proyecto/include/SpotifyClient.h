#pragma once
#include <WiFiClientSecure.h>
#include <SpotifyESP32.h>

class SpotifyController {
public:
    SpotifyController(WiFiClientSecure &client, const char *clientId, const char *clientSecret, const char *refreshToken);
    bool connect();
    void update();
    String getTrackName();
    String getArtistName();
    String getPlaybackTime();
    void togglePlayPause();
    void nextTrack();
    void previousTrack();

private:
    Spotify *spotify;
    //CurrentlyPlaying currentTrack;
};
