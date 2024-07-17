#ifndef BASE_HPP
#define BASE_HPP

#include <SFML/Graphics.hpp>

class Base
{
private:
    int vida;
    int corVida;
public:
    sf::RectangleShape baseBody;
    
    Base();
    ~Base();

    void receberDano();
    void update();
};

#endif