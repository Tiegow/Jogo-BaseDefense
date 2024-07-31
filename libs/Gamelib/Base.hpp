#ifndef BASE_HPP
#define BASE_HPP

#include "GameInterfaces.hpp"

class Base
{
private:
    sf::Clock baseClock;
    int velCura; //Tempo em segundos entre as curas automaticas da base
    int autoCura; //Quantidade de vida que a base recupera a cada cura automatica
    int vida;
    int maxVida;
    int resistencia; //Reduz o dano sofrido pela base
    int corVida;

    void curar(); //Cura automatica
public:
    sf::RectangleShape baseBody;
    
    Base();
    ~Base();

    //Funções
    void curar(int cura);
    int getVida();
    void spawn(sf::RenderTarget& tela);
    bool destruida();
    void receberDano(int dano);    
    void update();
    void render(sf::RenderTarget& tela);
};

#endif