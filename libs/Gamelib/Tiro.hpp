#ifndef TIRO_HPP
#define TIRO_HPP

#include "GameInterfaces.hpp"

class Tiro
{
private:
    sf::Sprite sprite;
    sf::Vector2f direcao;
    float velocidade;
    bool hit;
    bool enemy;
public:
    Tiro();
    Tiro(sf::Texture* textura, sf::Vector2f posicao, sf::Vector2f dir, float vel);
    ~Tiro();

    sf::FloatRect getBounds();

    bool atingido();
    void atingir();
    void setDirecao(sf::Vector2f mouseClick);
    void mover();
    void update();
    void render(sf::RenderTarget& tela);
};

#endif