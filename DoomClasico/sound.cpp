#include <SDL.h>
#include <SDL_mixer.h>
#include "sound.h"
#include <iostream>

SDL_AudioDeviceID dispositivoAudio;
SDL_AudioSpec especificacionAudio;
Uint8* audioBuffer;
Uint32 audioLength;

bool inicializarSonido() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "Error al inicializar SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    if (SDL_LoadWAV("./sound/shotgun.wav", &especificacionAudio, &audioBuffer, &audioLength) == NULL) {
        std::cerr << "Error al cargar el sonido: " << SDL_GetError() << std::endl;
        return false;
    }

    dispositivoAudio = SDL_OpenAudioDevice(NULL, 0, &especificacionAudio, NULL, 0);
    if (dispositivoAudio == 0) {
        std::cerr << "Error al abrir el dispositivo de audio: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void reproducirSonidoDisparo() {
    if (dispositivoAudio != 0) {
        SDL_QueueAudio(dispositivoAudio, audioBuffer, audioLength);
        SDL_PauseAudioDevice(dispositivoAudio, 0);
    }
}

void limpiarSonido() {
    SDL_CloseAudioDevice(dispositivoAudio);
    SDL_FreeWAV(audioBuffer);
    SDL_Quit();
}