#ifndef BASE_HPP
#define BASE_HPP

#include "GameInterfaces.hpp"
#include "GameLevelStats.hpp"

class Base
{
private:
    sf::Clock baseClock;

    BaseLevelStats stats;
    int vida;
    int maxVida;
    int corVida;

    void curar(); //Cura automatica
public:
    sf::RectangleShape baseBody;
    
    Base();
    ~Base();

    //Funções
    int getVida();
    bool destruida();
    void spawn(sf::RenderTarget& tela);
    void curar(int cura);
    void receberDano(int dano);   

    void resetBase();

    void update();
    void render(sf::RenderTarget& tela);
};

#endif