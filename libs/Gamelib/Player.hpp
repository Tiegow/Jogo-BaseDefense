#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameInterfaces.hpp"

class Player
{
private:
    sf::Vector2f destino;
    sf::Vector2f posicaoCentro;
    sf::Sprite sprite;
    sf::Texture textura;

    int vida;
    int municao;
    float velocidade;
    float intervaloAtaque;
    float intervaloAtaqueMax; //Define o intervalo entre os ataques do jogador (quanto menor, mais rápido vai atirar)
    bool movendo;

    void initTextura();
    void initSprite();
public:
    Player();
    ~Player();

    //Funções
    sf::Vector2f getPosCentro();
    sf::Vector2f getPos();
    sf::FloatRect getBounds();
    void updateAtaque();
    bool podeAtacar();
    void setIntervAtaque(float max);
    float getIntervAtaque();
    void setDestino(sf::Vector2f mouseClick);
    void receberDano(int dano);
    void mover();
    void update();
    void render(sf::RenderTarget& tela);
};

#endif