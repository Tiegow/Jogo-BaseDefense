#ifndef TIRO_HPP
#define TIRO_HPP

#include "GameInterfaces.hpp"

class Tiro
{
private:
    sf::Sprite sprite;
    sf::Vector2f direcao;
    float velocidade;
    int dano;
    bool hit;
    bool inimigo;
public:
    Tiro();
    Tiro(sf::Texture* textura, sf::Vector2f posicao, sf::Vector2f dir, bool inimigo);
    ~Tiro();

    sf::FloatRect getBounds();
    int atingir();
    bool atingido();
    bool isEnemy();
    void setDirecao(sf::Vector2f mouseClick);
    void mover();
    void update();
    void render(sf::RenderTarget& tela);
};

#endif