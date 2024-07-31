#ifndef INIMIGO_HPP
#define INIMIGO_HPP

#include <stdlib.h>
#include "GameInterfaces.hpp"

class Inimigo
{
private:
    sf::Clock atackClock;
    sf::Clock positionClock;
    sf::Vector2f destino;
    sf::Vector2f posicaoCentro;
    sf::Sprite sprite;

    int vida;
    float velocidade;
    float cadenciaAtaque; //Tempo entre um ataque e outro em segundos
    int distAtaque; //Distancia máxima em que o inimigo pode atacar o jogador
    bool movendo;
    bool fora;
    int safeDist;

    void moverIA();
    void mover();
    void foraTela(sf::RenderTarget &tela); //Verifica se o inimigo esta muito tempo fora da tela
public:
    Inimigo();
    Inimigo(sf::Texture* textura, sf::RenderTarget &tela);
    ~Inimigo();

    //Funções
    sf::Vector2f getCentro();
    sf::FloatRect getBounds();
    int getVida();
    bool atacar();
    void receberDano(int dano);
    void update(sf::Vector2f playerPos, sf::RenderTarget &tela);
    void render(sf::RenderTarget& tela);
};

#endif