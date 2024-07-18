#include "Game.hpp"
#include <iostream>

//Funções private
void Game::initVars(){
    this->janela = nullptr;
    this->paused = false;
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

    sf::Vector2f posicaoBase = centrObjeto(tamJanela, tamBase);
    this->base.baseBody.setPosition(posicaoBase); //Inicia a base no centro da tela
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
        //Eventos da tela e da interface
        switch (this->evento.type)
        {
            case sf::Event::Closed:
                this->janela->close();
                break;
                
            case sf::Event::KeyPressed:
            //ESC
                if(this->evento.key.code == sf::Keyboard::Escape){ 
                    this->paused = !paused;
                }

            default:
                break;
        }

        //Eventos do jogo
        if (!this->paused)
        {
            switch (this->evento.type)
            {
                case sf::Event::KeyPressed:
                //SPACE
                    if(this->evento.key.code == sf::Keyboard::Space)
                        base.receberDano(10);
                    break;
            
                default:
                    break;
            }   
        }
    }
}

void Game::update(){
    this->tratarEventos();
    
    if (this->paused)
    {
        //Abrir tela de pause
        pause(*this->janela);
    }
    else{
        //Fluxo normal do game
        this->base.update();
    }
}

void Game::render(){
    //Limpa os frames antigos e renderiza um novo frame
    if (!this->paused)
    {
        this->janela->clear(sf::Color::White);

        this->janela->draw(this->base.baseBody);
    }
    this->janela->display();
}
//----------------------------------------//