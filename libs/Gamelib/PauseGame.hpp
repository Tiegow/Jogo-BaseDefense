#ifndef PAUSEGAME_HPP
#define PAUSEGAME_HPP

#include <SFML/Graphics.hpp>

class PauseGame
{
private:
    sf::RenderWindow * janela;
    sf::Event evento;
    bool paused;
    
public:
    PauseGame();
    ~PauseGame();

    void pause(sf::RenderWindow* & janela);

    void tratarEventos();
    void update();
    void render();
};

void pausef(sf::RenderWindow* & jan);

#endif