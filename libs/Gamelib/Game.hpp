#ifndef GAME_HPP
#define GAME_HPP

#include "PauseGame.hpp"
#include "Base.hpp"

class Game
{
private:
    sf::VideoMode videoMode; //especificações da janela
    sf::Event evento;

    PauseGame pauseGame;
    Base base;
    
    void initVars();
    void initJanela();
    void initBase();
public:
    sf::RenderWindow * janela;

    Game();
    ~Game();

    //Funções
    bool isRunning();

    void tratarEventos();
    void update();
    void render();
};

#endif