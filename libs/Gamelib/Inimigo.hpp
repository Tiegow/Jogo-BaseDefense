#ifndef INIMIGO_HPP
#define INIMIGO_HPP

#include "GameInterfaces.hpp"

class Inimigo
{
private:
    sf::Clock enemyClock;
    sf::Vector2f destino;
    sf::Vector2f posicaoCentro;
    sf::Sprite sprite;

    int vida;
    float velocidade;
    float cadenciaAtaque; //Tempo entre um ataque e outro em segundos
    bool movendo;
public:
    Inimigo();
    ~Inimigo();

    //Funções
    sf::Vector2f getPosCentro();
    sf::Vector2f getPos();
    sf::FloatRect getBounds();
    void mover();
    void update(sf::Vector2f playerPos);
    void render(sf::RenderTarget& tela);
};

#endif