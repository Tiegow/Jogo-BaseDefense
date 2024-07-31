#ifndef GAME_HPP
#define GAME_HPP

#include <map>
#include <list>
#include <string>
#include "GameLevelStats.hpp"
#include "Base.hpp"
#include "Player.hpp"
#include "Inimigo.hpp"
#include "Tiro.hpp"
#include "GameGUI.hpp"

class Game
{
private:
    GameLevelStats stats;
    BaseLevelStats baseStats;

    sf::Clock clock;
    sf::VideoMode videoMode; //especificações da janela
    sf::Event evento;
    sf::Vector2f mousePos; //coordenada do mouse na janela
    std::map <std::string, sf::Texture*> texturas;
    
    //VARS
    bool paused;
    bool over;

    Player heroi;
    Base base;
    std::list <Inimigo*> inimigos;
    std::list <Tiro*> tiros;
    GameGUI GUI;

    void initVars();
    void initTexturas();
    void initJanela();

    void renderPause();
    void renderOver();
public:
    sf::RenderWindow * janela;

    Game();
    ~Game();

    //Funções
    bool isRunning();
    void limparGame();
    void tratarEventos();
    void tratarTiros();
    void tratarInimigos();
    void update();
    void render();
};

#endif