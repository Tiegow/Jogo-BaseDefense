#ifndef CAIXADROP_HPP
#define CAIXADROP_HPP

#include <stdlib.h>
#include "GameInterfaces.hpp"

class Caixadrop
{
private:
    sf::Sprite sprite;
    char tipo;
    int munQtd; //Quantidade de munição dada pela caixa
    int munMaxQtd;
    int munMinQtd;
    int vidaQtd; //Quantidade de vida dada pela caixa
    int vidaMaxQtd;
    int vidaMinQtd;
public:
    Caixadrop();
    Caixadrop(char tipo, sf::Texture* textura);
    ~Caixadrop();

    int getMunicao();
    int getVida();
};

#endif