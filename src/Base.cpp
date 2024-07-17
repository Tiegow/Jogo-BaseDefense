#include "Base.hpp"

Base::Base()
{
    this->vida = 100;
    this->corVida = 0;
    this->baseBody.setPosition(10.f, 10.f);
    this->baseBody.setSize(sf::Vector2f(500.f,300.f));
    this->baseBody.setOutlineColor(sf::Color::Red);
    this->baseBody.setOutlineThickness(15.f);
}

Base::~Base()
{
}

//Funções
void Base::receberDano(){
    if (this->vida < 0) //Reseta a vida pra 100 (TESTE)
    {
        this->vida = 100;
    }
    this->vida -= 10;
}

void Base::update(){
    //Muda a cor da base conforme a vida diminui
    this->corVida = int(vida * 2.55);
    this->baseBody.setOutlineColor(sf::Color(255-corVida,corVida,0,255)); //Aumenta o tom de vermelho e diminui o tom de verde
}