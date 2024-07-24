#include "Game.hpp"
#include <iostream>

//Funções private
void Game::initVars(){
    this->janela = nullptr;
    this->paused = false;
}

void Game::initTexturas(){
    this->texturas["TIRO"] = new sf::Texture;
    this->texturas["TIRO"]->loadFromFile("./assets/Tiro.png");
}

void Game::initJanela(){
    this->videoMode.width = 1800;
    this->videoMode.height = 1300;
    this->janela = new sf::RenderWindow(this->videoMode, "Base Defense", sf::Style::Titlebar | sf::Style::Close);
    this->janela->setFramerateLimit(60);
}
//----------------------------------------//


//Construtores | Destrutores
Game::Game(){
    this->initVars();
    this->initJanela();
    this->initTexturas();
    this->base.spawn(*this->janela);
}

Game::~Game(){
    delete this->janela;
    
    //Itera sobre o map texturas para deletar os ponteiros pra sf::Texture
    for(auto &t : this->texturas){
        delete t.second;
    }

    //Itera sobre a list tiros para deletar os ponteiros pra Tiro
    for(auto *t : this->tiros){
        delete t;
    }
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
                //Q
                    if(this->evento.key.code == sf::Keyboard::Q){
                        this->mousePos = getMouseCoords(*this->janela);
                        this->tiros.push_back(new Tiro(this->texturas["TIRO"], this->heroi.getPosCentro(), mousePos, 10.f));
                    }
                    break;
            
                default:
                    break;
            }

            //Mouse
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                this->mousePos = getMouseCoords(*this->janela);
                this->heroi.setDestino(this->mousePos);
            }
        }
    }
}

void Game::tratarTiros(){
    std::list<Tiro*>::iterator contador = this->tiros.begin();
    for(auto *tiro : this->tiros){
        tiro->update();

        //Removendo caso saia da tela ou atinja algo
        if
        (
            tiro->getBounds().top + tiro->getBounds().height < 0.f ||
            tiro->getBounds().left + tiro->getBounds().width < 0.f ||
            tiro->getBounds().top + tiro->getBounds().height > this->janela->getSize().y ||
            tiro->getBounds().left + tiro->getBounds().width > this->janela->getSize().x ||
            tiro->atingido()
        )
        {
            delete tiro;
            this->tiros.erase(contador);
            --contador;
        }

        ++contador;
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
        this->heroi.update();
        this->tratarTiros();
    }
}

void Game::render(){
    //Limpa os frames antigos e renderiza um novo frame
    if (!this->paused)
    {
        this->janela->clear(sf::Color::White);

        this->base.render(*this->janela);
        this->heroi.render(*this->janela);

        for(auto *tiro : this->tiros){
            tiro->render(*this->janela);
        }
    }
    this->janela->display();
}
//----------------------------------------//