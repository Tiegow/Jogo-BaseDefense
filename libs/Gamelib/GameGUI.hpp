#ifndef GAMEGUI_HPP
#define GAMEGUI_HPP

#include <sstream>
#include "GameInterfaces.hpp"

class GameGUI
{
private:
    sf::Font font;
    sf::Text statsTxt;
    sf::Text faseTxt;
    sf::Text scoreTxt;

    float margin;
public:
    GameGUI(/* args */);
    ~GameGUI();

    void update(int vida, int municao, int fase, int tempo, int score);
    void render(sf::RenderTarget& target);
};

#endif