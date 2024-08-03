#ifndef BASE_HPP
#define BASE_HPP

#include "GameInterfaces.hpp"
#include "GameLevelStats.hpp"

class Base
{
private:
    sf::Clock baseClock;

    int vida;
    int maxVida;
    int corVida;

    void curar(); //Cura automatica
public:
    BaseLevelStats stats;
    sf::RectangleShape baseBody;
    sf::Vector2f centro;

    Base();
    ~Base();

    //Funções
    int getVida();
    bool destruida();
    void spawn(sf::RenderTarget& tela);
    void restaurar();
    void receberDano(int dano);   

    void resetBase();

    void update();
    void render(sf::RenderTarget& tela);
};

#endif