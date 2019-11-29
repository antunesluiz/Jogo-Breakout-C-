#ifndef SOM_HPP
#define SOM_HPP

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

class Som {
private:
    SDL_AudioSpec Tipo_Wav;
    Uint32 Tamanho_Wav;
    Uint8 *Buffer_Wav;
    SDL_AudioDeviceID deviceId;
public:
    Som();
    ~Som();
    
    void init(const char* NomeArquivo);
    void toca(int pause);
};

#endif /* SOM_HPP */

