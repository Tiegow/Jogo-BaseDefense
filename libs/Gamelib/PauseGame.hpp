#ifndef PAUSEGAME_HPP
#define PAUSEGAME_HPP

#include "janFuncs.hpp"

class PauseGame
{
private:
    sf::Event evento;
    bool paused;
    
public:
    PauseGame();
    ~PauseGame();

    //Funções
    void tratarEventos(sf::RenderWindow* & jan);
    void update(sf::RenderWindow* & jan);
    void render(sf::RenderWindow* & jan);
    void pause(sf::RenderWindow* & jan);
};

#endif