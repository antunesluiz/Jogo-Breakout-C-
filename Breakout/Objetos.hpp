/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Objetos.hpp
 * Author: Luiz Antunes
 *
 * Created on 20 de Setembro de 2018, 17:28
 */

#ifndef OBJETOS_HPP
#define OBJETOS_HPP

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

#include "Map.hpp"
#include "Som.hpp"

class Objetos {
protected:
    SDL_Texture* objeto;
    SDL_Rect src, dest;

    Som som;
public:
    Objetos();
    ~Objetos();
};

class Plataforma : public Objetos {
private:
    int VelX, VelY;
public:
    Plataforma(int x, int y, int w, int h, int velx, const char* TextureName);

    void Left(int *Tempo);
    void Right(int *Tempo);

    void LimiteTela();
    void Render();

    SDL_Rect GetRect();

};

class Bola : public Objetos {
private:
    int NumeroBlocosRestantes;
    SDL_Rect* result;
    SDL_bool colisao;
    int VelX, VelY;
public:
    Bola(int x, int y, int h, int w, const char* TextureName, int confirma);

    void Update();
    void Render();
    
    bool ForaTela();

    SDL_Rect GetRect();

    void ColisaoPlataforma(Plataforma *plataforma);
    void ColisaoMapa(Map *mapa);
};

class Menus : public Objetos {
public:
    Menus(int x, int y, int w, int h, const char* nome);

    void Render();
};

class Coracoes : public Objetos {
public:
    Coracoes(int x, int y, int w, int h, const char* nome);

    void Render();
};

#endif /* OBJETOS_HPP */

