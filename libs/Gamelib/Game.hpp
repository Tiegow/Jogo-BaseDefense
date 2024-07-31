#ifndef GAME_HPP
#define GAME_HPP

#include <map>
#include <list>
#include <string>
#include "Base.hpp"
#include "Player.hpp"
#include "Inimigo.hpp"
#include "Tiro.hpp"
#include "GameGUI.hpp"

class Game
{
private:
    sf::Clock clock;
    sf::VideoMode videoMode; //especificações da janela
    sf::Event evento;
    sf::Vector2f mousePos; //coordenada do mouse na janela
    std::map <std::string, sf::Texture*> texturas;
    
    //VARS
    unsigned gameLevel;
    bool paused;
    bool over;
    float spawnInimVel; //tempo em segundos para surgir inimigos
    int maxInimigos;
    float chancesDropMun; //chance de inimigos deixarem munições no jogo
    float chancesDropVida; //chance de inimigos deixarem curas no jogo

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
    void tratarEventos();
    void tratarTiros();
    void tratarInimigos();
    void update();
    void render();
};

#endif