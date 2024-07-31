#include "GameGUI.hpp"
#include <iostream>

GameGUI::GameGUI()
{
    this->font.loadFromFile("./assets/Simply Rounded.ttf");
    
    this->vidaTxt.setFont(this->font);
    this->vidaTxt.setCharacterSize(37);
    this->vidaTxt.setFillColor(sf::Color::Black);
    this->vidaTxt.setString("Teste");

    this->munTxt.setFont(this->font);
    this->munTxt.setCharacterSize(37);
    this->munTxt.setFillColor(sf::Color::Black);
    this->munTxt.setString("Teste");
}

GameGUI::~GameGUI()
{
}

void GameGUI::update(int vida, int municao)
{
    std::stringstream strGUI;
    strGUI << "Vida: " << vida;
    this->vidaTxt.setString(strGUI.str());
    strGUI << "Municao: " << municao;
    this->munTxt.setString(strGUI.str());
}

void GameGUI::render(sf::RenderTarget &target)
{
    target.draw(this->vidaTxt);
    target.draw(this->munTxt);
}
