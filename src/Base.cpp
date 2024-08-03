#include "Base.hpp"
#include <iostream>

Base::Base()
{
    this->vida = 100;
    this->maxVida = 100;
    this->corVida = 0;

    this->baseBody.setSize(sf::Vector2f(500.f,300.f));
    this->baseBody.setOutlineColor(sf::Color::Red);
    this->baseBody.setFillColor(sf::Color(224, 225, 221, 255));
    this->baseBody.setOutlineThickness(15.f);
    this->baseClock.restart();
}

Base::~Base()
{
}

void Base::curar()
{
    this->vida += this->stats.autoCuraBase;
}

int Base::getVida()
{
    return this->vida;
}

// Funções
void Base::spawn(sf::RenderTarget& tela){
    sf::Vector2u tamJanela = tela.getSize(); //tamanho da janela
    sf::Vector2f tamBase = this->baseBody.getSize(); //tamanho da base

    sf::Vector2f posicaoBase = centrObjeto(tamJanela, tamBase);
    this->baseBody.setPosition(posicaoBase); //Inicia a base no centro da tela
}

void Base::restaurar()
{
    this->vida = this->maxVida;
}

bool Base::destruida()
{
    if (this->vida <= 0)
    {
        return true;
    }
    
    return false;
}

void Base::receberDano(int dano){
    if (this->vida > 0) 
    {
        this->vida -= (dano - this->stats.escudoBase);
    }
}

void Base::resetBase()
{
    this->stats.statsReset();
    this->vida = maxVida;
}

void Base::update(){ 
    this->centro = getPosCentro(this->baseBody);
    //Muda a cor da base conforme a vida diminui
    this->corVida = vida * 2;
    this->baseBody.setOutlineColor(sf::Color(255-corVida,corVida,0,255)); //Aumenta o tom de vermelho e diminui o tom de verde

    //Cura automatica
    sf::Time dt = this->baseClock.getElapsedTime();
    if (dt.asSeconds() >= this->stats.velCuraBase)
    {
        if (this->vida < this->maxVida)
        {
            this->baseClock.restart();
            this->curar();
        }
    }
    
}

void Base::render(sf::RenderTarget& tela){
    tela.draw(this->baseBody);
}