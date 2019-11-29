/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Map.hpp"
#include "TextureManager.hpp"

Map::Map(int mapa) {
    Vermelho = TextureManager::LoadTexture("Imagens/Vermelho.png");
    Amarelo = TextureManager::LoadTexture("Imagens/Amarelo.png");
    Verde = TextureManager::LoadTexture("Imagens/Verde.png");
    Azul = TextureManager::LoadTexture("Imagens/Azul.png");
    Laranja = TextureManager::LoadTexture("Imagens/Laranja.png");
    Marrom = TextureManager::LoadTexture("Imagens/Marrom.png");
    CorDePele = TextureManager::LoadTexture("Imagens/CorDePele.png");
    Rosa = TextureManager::LoadTexture("Imagens/Rosa.png");
    Branco = TextureManager::LoadTexture("Imagens/Branco.png");
    

    if (mapa == 1) {
        LoadMap(lvl1);
    } else {
        if (mapa == 2) {
            LoadMap(lvl2);
        } else {
            if (mapa == 3) {
                LoadMap(lvl3);
            }
        }
    }

    src.x = src.y = 0;
    src.w = dest.w = 16;
    src.h = dest.h = 16;

    dest.x = dest.y = 0;
}

Map::~Map() {

}

void Map::LoadMap(int arr[40][40]) {
    for (int row = 0; row < 40; row++) {
        for (int column = 0; column < 40; column++) {
            map[row][column] = arr[row][column];
        }
    }
}

void Map::DrawMap() {
    int type;

    for (int row = 0; row < 40; row++) {
        for (int column = 0; column < 40; column++) {
            type = map[row][column];

            dest.x = column * 16;
            dest.y = row * 16;

            switch (type) {
                case 1:
                    TextureManager::Draw(Vermelho, src, dest);
                    break;
                case 2:
                    TextureManager::Draw(Amarelo, src, dest);
                    break;
                case 3:
                    TextureManager::Draw(Verde, src, dest);
                    break;
                case 4:
                    TextureManager::Draw(Azul, src, dest);
                    break;
                case 5:
                    TextureManager::Draw(Laranja, src, dest);
                    break;
                case 6:
                    TextureManager::Draw(Marrom, src, dest);
                    break;
                case 7:
                    TextureManager::Draw(CorDePele, src, dest);
                    break;
                case 8:
                    TextureManager::Draw(Rosa, src, dest);
                    break;
                case 9:
                    TextureManager::Draw(Branco, src, dest);
                    break;
            }
        }
    }
}

int Map::GetMap(int x[40][40]) {
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            x[i][j] = map[i][j];
        }
    }
}

SDL_Rect Map::GetRect() {
    return dest;
}

void Map::SetMap(int x[40][40]) {
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            map[i][j] = x[i][j];
        }
    }
}

void Map::SetQuantBlocos(int x) {
    QuantBlocosFinal = x;
}

int Map::GetQuantBlocosFinal() {
    return QuantBlocosFinal;
}
