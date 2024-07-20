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
    sf::Vector2f posicao;

    sf::Sprite sprite;
    sf::Texture textura;
    sf::Clock clock;

    void initTextura();
    void initSprite();
public:
    // sf::CircleShape body;

    Player();
    ~Player();

    //Funções
    sf::Vector2f getPosCentro();
    void mover(sf::Vector2f mouseClick);
    void update(sf::Vector2f mouseClick);
    void render(sf::RenderTarget& tela);
};

#endif