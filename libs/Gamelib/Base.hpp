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
    int corVida;
public:
    sf::RectangleShape baseBody;
    
    Base();
    ~Base();

    //Funções
    void curar(int cura);
    void curar(); //Cura automatica
    int getVida();
    void spawn(sf::RenderTarget& tela);
    bool destruida();
    void receberDano(int dano);    
    void update();
    void render(sf::RenderTarget& tela);
};

#endif