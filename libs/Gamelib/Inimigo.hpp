#ifndef INIMIGO_HPP
#define INIMIGO_HPP

#include <stdlib.h>
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
    int distAtaque; //Distancia máxima em que o inimigo pode atacar o jogador
    bool movendo;
    int safeDist;
public:
    Inimigo();
    Inimigo(sf::Texture* textura, sf::RenderTarget &tela);
    ~Inimigo();

    //Funções
    sf::Vector2f getCentro();
    sf::FloatRect getBounds();
    int getVida();
    void moverIA();
    void mover();
    bool atacar();
    void receberDano(int dano);
    void update(sf::Vector2f playerPos);
    void render(sf::RenderTarget& tela);
};

#endif