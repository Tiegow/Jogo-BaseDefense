#ifndef INTERFACES_HPP
#define INTERFACES_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

sf::Vector2f centrObjeto(sf::Vector2u tamJanela, sf::Vector2f tamObj);
sf::Vector2f getMouseCoords(sf::RenderWindow& janela);
void pause(sf::RenderTarget& target);
void gameOver(sf::RenderTarget& target);

#endif