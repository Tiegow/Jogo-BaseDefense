#ifndef GAME_HPP
#define GAME_HPP

#include "Base.hpp"
#include "Player.hpp"

class Game
{
private:
    sf::VideoMode videoMode; //especificações da janela
    sf::Event evento;
    sf::Vector2f mousePos;
    bool paused;

    Player heroi;
    Base base;
    
    void initVars();
    void initJanela();
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