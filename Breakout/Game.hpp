/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.hpp
 * Author: Luiz Antunes
 *
 * Created on 21 de Junho de 2018, 20:36
 */

#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <random>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Map.hpp"
#include "Objetos.hpp"
#include "Som.hpp"

using namespace std;

class Game {
private:
    SDL_Window* window;
    bool isRunning;

    Bola *bola;
    Coracoes *coracao[3];
    Map *mapa;
    Menus *MenuPrincipal;
    Menus* Instrucoes;
    Menus* MenuGanhou;
    Menus* MenuPerdeu;
    Menus* Fundo;
    Plataforma *plataforma;

    int RandMap, Maplvl0;
    int vidas, blocos, blocosMap;
    bool instrucoes, Ganhou, Perdeu;
    int QuantFrames;
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    bool running();

    static SDL_Renderer* renderer;
};

#endif /* GAME_HPP */

