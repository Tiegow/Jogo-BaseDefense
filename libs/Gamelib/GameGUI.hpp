#ifndef GAMEGUI_HPP
#define GAMEGUI_HPP

#include <sstream>
#include "GameInterfaces.hpp"

class GameGUI
{
private:
    sf::Font font;
    sf::Text vidaTxt;
    sf::Text munTxt;
public:
    GameGUI(/* args */);
    ~GameGUI();

    void update(int vida, int municao);
    void render(sf::RenderTarget& target);
};

#endif