#ifndef BASE_HPP
#define BASE_HPP

#include <SFML/Graphics/RectangleShape.hpp>

class Base
{
private:
    int vida;
    int corVida;
public:
    sf::RectangleShape baseBody;
    
    Base();
    ~Base();

    void receberDano(int dano);
    void update();
};

#endif