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
    float cadenciaAtaque; //Tempo entre um ataque e outro em segundos
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
    bool podeAtacar(sf::Time deltaTime);
    float getCadAtaque();
    void setCadAtaque(float tempo);
    void setDestino(sf::Vector2f mouseClick);
    void receberDano(int dano);
    void mover();
    void update();
    void render(sf::RenderTarget& tela);
};

#endif