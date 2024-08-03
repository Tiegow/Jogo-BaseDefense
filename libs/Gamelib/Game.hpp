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
#include "Caixadrop.hpp"
#include "GameGUI.hpp"

class Game
{
private:
    GameLevelStats stats;
    BaseLevelStats baseStats;

    sf::Clock spawnClock;
    sf::Clock levelClock;
    sf::VideoMode videoMode; //especificações da janela
    sf::Event evento;
    sf::Vector2f mousePos; //coordenada do mouse na janela
    std::map <std::string, sf::Texture*> texturas;
    
    //VARS
    bool paused;
    bool up;
    bool over;
    int tempo; //tempo restante ate a proxima fase

    Player heroi;
    Base base;
    GameGUI GUI;

    std::list <Inimigo*> inimigos;
    std::list <Caixadrop*> caixas;
    std::list <Tiro*> tiros;

    void initVars();
    void initTexturas();
    void initJanela();

    void renderPause();
    void renderOver();
    void renderUpgrade();
    void limparGame();
    void proximaFase();

    void spawnInimigos();
    void tratarEventos();
    void tratarTiros();
    void tratarInimigos();
    void tratarCaixas();
public:
    sf::RenderWindow * janela;

    Game();
    ~Game();

    //Funções
    bool isRunning();    
    void update();
    void render();
};

#endif