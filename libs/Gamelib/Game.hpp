#ifndef GAME_HPP
#define GAME_HPP

#include <map>
#include <list>
#include "Base.hpp"
#include "Player.hpp"
#include "Tiro.hpp"

class Game
{
private:
    sf::VideoMode videoMode; //especificações da janela
    sf::Event evento;
    sf::Vector2f mousePos; //coordenada do mouse na janela
    std::map <std::string, sf::Texture*> texturas;
    bool paused;
    bool over;

    Player heroi;
    Base base;
    std::list <Tiro*> tiros;

    void initVars();
    void initTexturas();
    void initJanela();
public:
    sf::RenderWindow * janela;

    Game();
    ~Game();

    //Funções
    bool isRunning();
    void tratarEventos();
    void tratarTiros();
    void update();
    void render();
};

#endif