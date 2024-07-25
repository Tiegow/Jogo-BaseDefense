#include "Game.hpp"
#include <iostream>

//Funções private
void Game::initVars(){
    this->janela = nullptr;
    this->paused = false;
    this->over = false;
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
    this->janela = nullptr;
    
    //Itera sobre o map texturas para deletar os ponteiros pra sf::Texture
    for(auto &t : this->texturas){
        delete t.second;
        t.second = nullptr;
    }

    //Itera sobre a list tiros para deletar os ponteiros pra Tiro
    for(auto *t : this->tiros){
        delete t;
        t = nullptr;
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
                break;

            default:
                break;
        }

        //Eventos do jogo
        if (!this->paused && !this->over)
        {
            switch (this->evento.type)
            {
                case sf::Event::KeyPressed:
                //Q
                    if(this->evento.key.code == sf::Keyboard::Q && this->heroi.podeAtacar()){
                        this->mousePos = getMouseCoords(*this->janela);
                        this->tiros.push_back(new Tiro(this->texturas["TIRO"], this->heroi.getPosCentro(), mousePos, false));
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

        //Colisões
        if (tiro->isEnemy())
        {
            //Base
            if (tiro->getBounds().intersects(this->base.baseBody.getGlobalBounds()))
            {
                this->base.receberDano(tiro->atingir());
            }
            //Player
            if (tiro->getBounds().intersects(this->heroi.getBounds()))
            {
                this->heroi.receberDano(tiro->atingir());
            }
        }
        
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
            tiro = nullptr;
            this->tiros.erase(contador);
            --contador;
        }

        ++contador;
    }
}

void Game::update(){
    if (this->base.getVida() <= 0)
    {
        this->over = true;
    }

    this->tratarEventos();
    
    if (!this->over)
    {
        if (this->paused)
        {
            //Abrir tela de pause
            pause(*this->janela);
        }
        else
        {
            //Fluxo normal do game
            this->base.update();
            this->heroi.update();
            this->tratarTiros();
        }
    }
    else
    {
        gameOver(*this->janela);
    }
    
}

void Game::render(){
    //Renderiza os elementos do jogo
    if (!this->paused && !this->over)
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