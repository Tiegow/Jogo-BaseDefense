#include "Caixadrop.hpp"

Caixadrop::Caixadrop()
{
}

Caixadrop::Caixadrop(char tipo, sf::Texture* textura)
{
    this->sprite.setTexture(*textura);
    this->munQtd = 0;
    this->vidaQtd = 0;
    if (tipo == 'M')
    {
        this->munMaxQtd = 25;
        this->munMinQtd = 10;
        this->munQtd = rand() % (this->munMaxQtd - this->munMinQtd + 1) + this->munMinQtd;
    }
    else if (tipo == 'V')
    {
        this->vidaMaxQtd = 15;
        this->vidaMinQtd = 5;
        this->vidaQtd = rand() % (this->vidaMaxQtd - this->vidaMinQtd + 1) + this->vidaMinQtd;
    }
}

Caixadrop::~Caixadrop()
{
}

int Caixadrop::getMunicao()
{
    return this->munQtd;
}

int Caixadrop::getVida()
{
    return this->vidaQtd;
}
