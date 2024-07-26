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
    int distAtaque; //Distancia máxima em que o inimigo pode atacar o jogador
    int safeDist;
    float velocidade;
    float cadenciaAtaque; //Tempo entre um ataque e outro em segundos
    bool movendo;
public:
    Inimigo();
    Inimigo(sf::Texture* textura);
    ~Inimigo();

    //Funções
    sf::Vector2f getPosCentro();
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