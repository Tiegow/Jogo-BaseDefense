#include "Tiro.hpp"
#include <iostream>

Tiro::Tiro()
{
}

Tiro::Tiro(sf::Texture* textura, sf::Vector2f posicao, sf::Vector2f dir, float vel)
{
    this->sprite.setTexture(*textura);
    this->sprite.setScale(2.5, 2.5);
    this->sprite.setPosition(posicao);
    this->direcao = dir - posicao;
    this->velocidade = vel;
    this->hit = false;
}

Tiro::~Tiro()
{
}

sf::FloatRect Tiro::getBounds()
{
    return this->sprite.getGlobalBounds();
}

bool Tiro::atingido()
{
    return this->hit;
}

void Tiro::atingir()
{
    this->hit = true;
}

void Tiro::setDirecao(sf::Vector2f mouseClick)
{
    this->direcao = mouseClick;
}

void Tiro::mover()
{
    float comprimento = std::sqrt(this->direcao.x * this->direcao.x + this->direcao.y * this->direcao.y);
    /*
        Calcula a magnitude do vetor de direção (Teorema de Pitágoras)
        - A magnitude do vetor é equivale à hipotenusa do triângulo formado pelos eixos do vetor
    */

    if (comprimento != 0) //Normalizando vetor para obter um vetor unitário
    {
        this->direcao.x /= comprimento;
        this->direcao.y /= comprimento;
    }

    sf::Vector2f movimento = this->direcao * this->velocidade;

    float angulo = std::atan2(this->direcao.y, this->direcao.x) * 180 / 3.14; //Calcula o angulo em radianos a partir do vetor de direção
    this->sprite.setRotation(angulo + 90);
    this->sprite.move(movimento);
    
}

void Tiro::update()
{
    this->mover();
}

void Tiro::render(sf::RenderTarget &tela)
{
    tela.draw(this->sprite);
}
