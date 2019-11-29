/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Objetos.hpp"
#include "TextureManager.hpp"

#include <cmath>

Objetos::Objetos() {
    som.init("Sounds/Beep2.wav");
}

Objetos::~Objetos() {

}

//------------------------------------------------------------------------------

Bola::Bola(int x, int y, int h, int w, const char* TextureName, int confirma) {
    objeto = TextureManager::LoadTexture(TextureName);

    dest.x = x;
    dest.y = y;
    dest.h = h;
    dest.w = w;

    VelX = -2;
    VelY = -3;

    if (confirma == 0) {
        NumeroBlocosRestantes = 0;
    }

}

void Bola::Update() {
    if (dest.x < 0 || dest.x + dest.w >= 640) {
        VelX = -VelX;
    }

    if (dest.y < 0) {
        VelY = -VelY;
    }

    dest.x += VelX;
    dest.y += VelY;

    if (dest.y > 624) {
        dest.y = 650;
        VelX = 0;
        VelY = 0;
    }
}

void Bola::Render() {
    SDL_RenderCopy(Game::renderer, objeto, NULL, &dest);
}

void Bola::ColisaoMapa(Map* mapa) {
    int type, map[40][40];
    SDL_Rect destM;

    mapa->GetMap(map);

    for (int row = 0; row < 40; row++) {
        for (int column = 0; column < 40; column++) {
            type = map[row][column];

            destM.x = column * 16;
            destM.y = row * 16;

            switch (type) {
                case 0:
                    break;
                default:
                    if ((destM.x <= dest.x) && (dest.x <= (destM.x + 16)) && dest.y <= destM.y + 16) {
                        if (dest.y + dest.h >= destM.y && (destM.x <= dest.x) && (dest.x <= (destM.x + 16))) {
                            map[row][column] = 0;
                            VelY = -VelY;
                            NumeroBlocosRestantes += 1;
                        }
                    }
                    break;
            }
            mapa->SetMap(map);
            mapa->SetQuantBlocos(NumeroBlocosRestantes);
        }
    }
}

void Bola::ColisaoPlataforma(Plataforma* plataforma) {
    const SDL_Rect *teste1 = &dest;
    const SDL_Rect teste2 = plataforma->GetRect();

    colisao = SDL_HasIntersection(teste1, &teste2);

    if (colisao == SDL_TRUE) {
        VelY = -VelY;
        som.toca(0);
    }
}

bool Bola::ForaTela() {
    if (dest.y > 640) {
        dest.y = 300;
        dest.x = 1000;
        return true;
    } else {
        return false;
    }
}

SDL_Rect Bola::GetRect() {
    return dest;
}

//------------------------------------------------------------------------------

Plataforma::Plataforma(int x, int y, int w, int h, int velx, const char* TextureName) {
    objeto = TextureManager::LoadTexture(TextureName);

    dest.h = h;
    dest.w = w;
    dest.x = x;
    dest.y = y;

    VelX = velx;
}

void Plataforma::Render() {
    Plataforma::LimiteTela();

    SDL_RenderCopy(Game::renderer, objeto, NULL, &dest);
}

void Plataforma::LimiteTela() {
    if (dest.x + dest.w >= 640) {
        dest.x = 640 - 120;
    }

    if (dest.x < 0) {
        dest.x = 0;
    }
}

void Plataforma::Left(int *Tempo) {
    dest.x = dest.x - VelX * (*Tempo) - 5 * ((*Tempo)*(*Tempo));
    *Tempo = 0;

}

void Plataforma::Right(int *Tempo) {
    dest.x = dest.x + VelX * (*Tempo) + 5 * ((*Tempo)*(*Tempo));
    *Tempo = 0;
}

SDL_Rect Plataforma::GetRect() {
    return dest;
}

//------------------------------------------------------------------------------

Menus::Menus(int x, int y, int w, int h, const char* nome) {
    objeto = TextureManager::LoadTexture(nome);

    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;
}

void Menus::Render() {
    SDL_RenderCopy(Game::renderer, objeto, NULL, &dest);
}

//------------------------------------------------------------------------------

Coracoes::Coracoes(int x, int y, int w, int h, const char* nome) {
    objeto = TextureManager::LoadTexture(nome);

    dest.x = x;
    dest.y = y;
    dest.h = h;
    dest.w = w;
}

void Coracoes::Render() {
    SDL_RenderCopy(Game::renderer, objeto, NULL, &dest);
}

