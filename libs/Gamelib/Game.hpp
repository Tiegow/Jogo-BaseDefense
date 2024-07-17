#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "PauseGame.hpp"
#include "Base.hpp"

class Game
{
private:
    sf::RenderWindow * janela;
    sf::VideoMode videoMode; //especificações da janela
    sf::Event evento;

    // PlayGame play;
    PauseGame pauseGame;
    Base base;
    
    void initVars();
    void initJanela();
    void initBase();
public:
    Game();
    ~Game();

    //Funções
    bool isRunning();

    void tratarEventos();
    void update();
    void render();
};

#endif