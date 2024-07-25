#ifndef BASE_HPP
#define BASE_HPP

#include "GameInterfaces.hpp"

class Base
{
private:
    int vida;
    int corVida;
public:
    sf::RectangleShape baseBody;
    
    Base();
    ~Base();

    //Funções
    int getVida();
    void spawn(sf::RenderTarget& tela);
    void receberDano(int dano);
    void update();
    void render(sf::RenderTarget& tela);
};

#endif