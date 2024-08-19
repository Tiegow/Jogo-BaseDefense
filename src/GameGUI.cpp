#include "GameGUI.hpp"

GameGUI::GameGUI()
{
    this->margin = 30.f;
    this->font.loadFromFile("./assets/Simply Rounded.ttf");
    
    this->statsTxt.setFont(this->font);
    this->statsTxt.setCharacterSize(37);
    this->statsTxt.setFillColor(sf::Color::Black);

    this->faseTxt.setFont(this->font);
    this->faseTxt.setCharacterSize(37);
    this->faseTxt.setFillColor(sf::Color::Black);

    this->scoreTxt.setFont(this->font);
    this->scoreTxt.setCharacterSize(37);
    this->scoreTxt.setFillColor(sf::Color::Black);
}

GameGUI::~GameGUI()
{
}

void GameGUI::update(int vida, int municao, int fase, int tempo, int score)
{
    std::stringstream strStatsGUI;
    strStatsGUI << "Vida: " << vida << "\nMunicao: " << municao ;
    this->statsTxt.setString(strStatsGUI.str());

    std::stringstream strRecordeGUI;
    strRecordeGUI << "Recorde: " << score;
    this->scoreTxt.setString(strRecordeGUI.str());

    std::stringstream strLevelGUI;
    strLevelGUI << "Fase: " << fase << "\n" << tempo << " s";
    this->faseTxt.setString(strLevelGUI.str());
}

void GameGUI::render(sf::RenderTarget &target)
{
    float textPos = target.getSize().x - this->faseTxt.getGlobalBounds().width - this->margin;
    this->faseTxt.setPosition(textPos, this->margin);

    sf::Vector2f scorePos = centrObjeto(target.getSize(), this->scoreTxt.getGlobalBounds());
    this->scoreTxt.setPosition(scorePos.x, this->margin);

    this->statsTxt.setPosition(this->margin, this->margin);
    target.draw(this->statsTxt);
    target.draw(this->scoreTxt);
    target.draw(this->faseTxt);
}
