#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameInterfaces.hpp"
#include "GameLevelStats.hpp"

class Player
{
private:
    sf::Clock playerClock;
    sf::Vector2f destino;
    sf::Vector2f posicaoCentro;
    sf::Sprite sprite;
    sf::Texture textura;
    bool movendo;

    void initTextura();
    void initSprite();
    void mover();
public:
    PlayerLevelStats playerStats;
    
    Player();
    ~Player();

    //Funções
    sf::Vector2f getCentro();
    sf::Vector2f getPos();
    sf::FloatRect getBounds();

    bool podeAtacar();

    void coletarCaixa(int munQtd, int vidaQtd);
    void updateMun();
    void setDestino(sf::Vector2f mouseClick);
    void setPos(sf::Vector2f posicao);
    void receberDano(int dano);
    void update(sf::RenderTarget& tela);
    void render(sf::RenderTarget& tela);
};

#endif