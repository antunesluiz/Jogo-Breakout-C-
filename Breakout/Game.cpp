/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Game.hpp"

SDL_Renderer* Game::renderer = nullptr;

Game::Game() {
    Maplvl0 = 0;
    vidas = 4;
    blocos = 0;
    blocosMap = 0;
    instrucoes = false;
    QuantFrames = 0;
    Perdeu = false;
    Ganhou = false;
}

Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;

    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        cout << "Subsistemas da sdl inicializada!..." << endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window) {
            cout << "Janela criada!" << endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            cout << "Renderizacao criada" << endl;
        }

        isRunning = true;
    } else {
        isRunning = false;
    }

    bola = new Bola(1000, 500, 20, 20, "Imagens/Bolinha.png", 0);
    coracao[0] = new Coracoes(540, 0, 100, 80, "Imagens/Coracao.png");
    coracao[1] = new Coracoes(480, 0, 100, 80, "Imagens/Coracao.png");
    coracao[2] = new Coracoes(420, 0, 100, 80, "Imagens/Coracao.png");
    mapa = new Map(Maplvl0);
    plataforma = new Plataforma(320, 590, 120, 50, 5, "Imagens/Plataforma.png");
    MenuPrincipal = new Menus(0, 0, 640, 640, "Imagens/Menu.png");
    Instrucoes = new Menus(0, 0, 640, 640, "Imagens/Instrucoes.png");
    MenuGanhou = new Menus(0, 0, 640, 640, "Imagens/Ganhou.png");
    MenuPerdeu = new Menus(0, 0, 640, 640, "Imagens/Perdeu.png");
    Fundo = new Menus(0, 0, 640, 640, "Imagens/Fundo.png");
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    QuantFrames++;
                    plataforma->Left(&QuantFrames);
                    break;
                case SDLK_RIGHT:
                    QuantFrames++;
                    plataforma->Right(&QuantFrames);
                    break;
                case SDLK_SPACE:
                    if (Maplvl0 != 0) {
                        delete(bola);
                        bola = new Bola(plataforma->GetRect().x, plataforma->GetRect().y - 40, 20, 20, "Imagens/Bolinha.png", 1);
                    }
                    break;
                case SDLK_RETURN:
                    if (Maplvl0 == 0 && instrucoes == false) {
                        vidas = 3;
                        Perdeu = false;
                        Ganhou = false;

                        delete(mapa);
                        srand(time(NULL));
                        RandMap = rand() % 6 + 1;

                        if (RandMap <= 2) {
                            mapa = new Map(1);
                            Maplvl0 = 1;
                            blocosMap = 102;
                        } else {
                            if (RandMap <= 4) {
                                mapa = new Map(2);
                                Maplvl0 = 2;
                                blocosMap = 122;
                            } else {
                                if (RandMap <= 6) {
                                    mapa = new Map(3);
                                    Maplvl0 = 3;
                                    blocosMap = 155;
                                }
                            }
                        }
                    }
                    break;
                case SDLK_i:
                    instrucoes = true;
                    break;
                case SDLK_b:
                    instrucoes = false;
                    break;
                case SDLK_m:
                    vidas = 4;
                    Perdeu = false;
                    Ganhou = false;

                    delete(bola);
                    bola = new Bola(1000, 500, 16, 16, "Imagens/Bolinha.png", 1);

                    Maplvl0 = 0;
                    delete(mapa);
                    mapa = new Map(Maplvl0);
                    break;
                case SDLK_r:
                    vidas = 3;
                    Perdeu = false;
                    Ganhou = false;

                    delete(mapa);
                    srand(time(NULL));
                    RandMap = rand() % 6 + 1;

                    if (RandMap <= 2) {
                        mapa = new Map(1);
                        Maplvl0 = 1;
                        blocosMap = 102;
                    } else {
                        if (RandMap <= 4) {
                            mapa = new Map(2);
                            Maplvl0 = 2;
                            blocosMap = 122;
                        } else {
                            if (RandMap <= 6) {
                                mapa = new Map(3);
                                Maplvl0 = 3;
                                blocosMap = 155;
                            }
                        }
                    }
                default:
                    break;
            }
        default:
            break;
    }
}

void Game::update() {
    bola->ColisaoPlataforma(plataforma);
    bola->ColisaoMapa(mapa);
    bola->Update();

    if (bola->ForaTela() == true) {
        vidas -= 1;
    }

    if (vidas == 0) {
        Maplvl0 = 0;
        delete(mapa);
        mapa = new Map(Maplvl0);
        Perdeu = true;
    }

    if (mapa->GetQuantBlocosFinal() == blocosMap) {
        if (blocosMap != 0) {
            Maplvl0 = 0;
            delete(mapa);
            mapa = new Map(Maplvl0);
            Ganhou = true;
        }
    }
}

void Game::render() {
    SDL_RenderClear(renderer);
    Fundo->Render();
    mapa->DrawMap();

    if (Maplvl0 == 0) {
        MenuPrincipal->Render();
    }

    if (instrucoes == true && Maplvl0 == 0) {
        SDL_RenderClear(renderer);
        Instrucoes->Render();
    }

    if (Perdeu == true && Maplvl0 == 0) {
        SDL_RenderClear(renderer);
        MenuPerdeu->Render();
    }

    if (Ganhou == true && Maplvl0 == 0) {
        SDL_RenderClear(renderer);
        MenuGanhou->Render();
    }

    if (Maplvl0 != 0) {
        plataforma->Render();
    }

    if (vidas == 3 && Maplvl0 != 0) {
        coracao[0]->Render();
        coracao[1]->Render();
        coracao[2]->Render();
    } else {
        if (vidas == 2 && Maplvl0 != 0) {
            coracao[0]->Render();
            coracao[1]->Render();
        } else {
            if (vidas == 1 && Maplvl0 != 0) {
                coracao[0]->Render();
            }
        }
    }

    bola->Render();
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    delete(mapa);
    delete(plataforma);
    delete(bola);
    delete(coracao[0]);
    delete(coracao[1]);
    delete(coracao[2]);
    delete(MenuPrincipal);
    delete(Instrucoes);
    delete(MenuGanhou);
    delete(MenuPerdeu);
    delete(Fundo);
    
    cout << "Jogo finalizado!" << endl;
}

bool Game::running() {
    return isRunning;
}
