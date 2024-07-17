#include "Game.hpp"
#include <iostream>

//Funções private
void Game::initVars(){
    this->janela = nullptr;
}

void Game::initJanela(){
    this->videoMode.width = 1800;
    this->videoMode.height = 1200;
    this->janela = new sf::RenderWindow(this->videoMode, "Base Defense", sf::Style::Titlebar | sf::Style::Close);
    this->janela->setFramerateLimit(60);
}

void Game::initBase(){
    sf::Vector2u tamJanela = this->janela->getSize(); //tamanho da janela
    sf::Vector2f tamBase = this->base.baseBody.getSize(); //tamanho da base

    sf::Vector2f posicaoBase;
    posicaoBase.x = (tamJanela.x - tamBase.x) / 2;
    posicaoBase.y = (tamJanela.y - tamBase.y) / 2;
    this->base.baseBody.setPosition(posicaoBase);
}
//----------------------------------------//


//Construtores | Destrutores
Game::Game(){
    this->initVars();
    this->initJanela();
    this->initBase();
}

Game::~Game(){
    delete this->janela;
    std::cout << "Deletando janela /n";
}
//----------------------------------------//


//Funções public
bool Game::isRunning(){
    return this->janela->isOpen();
}

void Game::tratarEventos(){
    //Tratando eventos
    while (this->janela->pollEvent(this->evento))
    {
        switch (this->evento.type)
        {
            case sf::Event::Closed:
                this->janela->close();
                break;

            case sf::Event::KeyPressed:
            //ESC
                if(this->evento.key.code == sf::Keyboard::Escape){ 
                    // this->pauseGame.pause(janela);
                    pausef(janela);
                }
                if(this->evento.key.code == sf::Keyboard::Space)
                    base.receberDano();
                break;
                
            default:
                break;
        }
    }
}

void Game::update(){
    this->tratarEventos();
    
    this->base.update();
}

void Game::render(){
    //Limpa os frames antigos e renderiza um novo frame
    this->janela->clear(sf::Color::White);

    this->janela->draw(this->base.baseBody);

    this->janela->display();
}