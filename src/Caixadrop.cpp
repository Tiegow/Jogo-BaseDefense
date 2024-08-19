#include "Caixadrop.hpp"

Caixadrop::Caixadrop()
{
}

Caixadrop::Caixadrop(char tipo, sf::Texture* textura, sf::Vector2f posicao)
{
    this->sprite.setTexture(*textura);
    this->sprite.setPosition(posicao);
    this->sprite.setScale(1.5, 1.5);
    this->munQtd = 0;
    this->vidaQtd = 0;
    if (tipo == 'M')
    {
        this->munMaxQtd = 50;
        this->munMinQtd = 20;
        this->munQtd = rand() % (this->munMaxQtd - this->munMinQtd + 1) + this->munMinQtd;
    }
    else if (tipo == 'V')
    {
        this->vidaMaxQtd = 20;
        this->vidaMinQtd = 10;
        this->vidaQtd = rand() % (this->vidaMaxQtd - this->vidaMinQtd + 1) + this->vidaMinQtd;
        this->sprite.setPosition(posicao.x + 40, posicao.y);
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

sf::FloatRect Caixadrop::getBounds()
{
    return this->sprite.getGlobalBounds();
}

void Caixadrop::render(sf::RenderTarget &tela)
{
    tela.draw(this->sprite);
}
