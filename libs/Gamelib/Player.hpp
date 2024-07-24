#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameInterfaces.hpp"

class Player
{
private:
    int vida;
    int municao;
    float velocidade;
    bool movendo;
    sf::Vector2f destino;
    sf::Vector2f posicaoCentro;

    sf::Sprite sprite;
    sf::Texture textura;
    sf::Clock clock;

    void initTextura();
    void initSprite();
public:
    Player();
    ~Player();

    //Funções
    sf::Vector2f getPosCentro();
    sf::Vector2f getPos();
    void setDestino(sf::Vector2f mouseClick);
    void mover();
    void update();
    void render(sf::RenderTarget& tela);
};

#endif