#include <SDL.h>
#include <iostream>

SDL_AudioSpec wavSpec;
Uint32 wavLength;
Uint8* wavBuffer;
SDL_AudioDeviceID deviceId;

void audioCallback(void* userdata, Uint8* stream, int len) {
    static Uint32 audioPos = 0;
    static Uint32 remaining = 0;

    if (remaining == 0) {
        audioPos = 0;
        remaining = wavLength;
    }

    int bytesToCopy = (len > remaining) ? remaining : len;

    SDL_memcpy(stream, wavBuffer + audioPos, bytesToCopy);

    audioPos += bytesToCopy;
    remaining -= bytesToCopy;
}

void generarAudioMision(const char* ruta) {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "Error al inicializar SDL: " << SDL_GetError() << std::endl;
        return;
    }

    if (SDL_LoadWAV(ruta, &wavSpec, &wavBuffer, &wavLength) == NULL) {
        std::cerr << "Error al cargar el archivo WAV: " << SDL_GetError() << std::endl;
        return;
    }

    wavSpec.callback = audioCallback;

    deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    if (deviceId == 0) {
        std::cerr << "Error al abrir el dispositivo de audio: " << SDL_GetError() << std::endl;
    }
    else {
        SDL_PauseAudioDevice(deviceId, 0);
    }
}

void liberarAudio() {
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
    SDL_Quit();
}