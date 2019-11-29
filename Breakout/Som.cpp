#include "Som.hpp"

Som::Som() {

}

Som::~Som() {
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(Buffer_Wav);
}

void Som::init(const char* NomeArquivo) {
    SDL_LoadWAV(NomeArquivo, &Tipo_Wav, &Buffer_Wav, &Tamanho_Wav);
    deviceId = SDL_OpenAudioDevice(NULL, 0, &Tipo_Wav, NULL, 0);
}

void Som::toca(int pause) {
    SDL_QueueAudio(deviceId, Buffer_Wav, Tamanho_Wav);
    SDL_PauseAudioDevice(deviceId, pause);
}
