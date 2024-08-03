#ifndef INTERFACES_HPP
#define INTERFACES_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

sf::Vector2f centrObjeto(sf::Vector2u tamJanela, sf::Vector2f tamObj);
sf::Vector2f centrObjeto(sf::Vector2u tamJanela, sf::FloatRect objBounds);
sf::Vector2f getMouseCoords(sf::RenderWindow& janela);
sf::Vector2f getPosCentro(sf::Sprite& sprite);
sf::Vector2f getPosCentro(sf::RectangleShape& rect);
bool botaoPres(sf::RenderWindow& janela, sf::FloatRect sprite);

#endif