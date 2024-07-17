#include "PauseGame.hpp"

void pausef(sf::RenderWindow* & jan){
    sf::Event ev;
    bool paused = true;
    jan->clear(sf::Color::Red);
    jan->display();
    while (paused)
    {
        while (jan->pollEvent(ev))
        {
            switch (ev.type)
            {
            case sf::Event::Closed:
                jan->close();
                break;
            
            case sf::Event::KeyPressed:
            //ESC
                if(ev.key.code == sf::Keyboard::Escape){ 
                    if (paused)
                    {
                        paused = false;
                    }
                }
                break;

            default:
                break;
            }
        }
        
    }
    
}

PauseGame::PauseGame(){
    this->janela = nullptr;
    this->paused = true;
}

PauseGame::~PauseGame(){
    delete this->janela;
}

void PauseGame::pause(sf::RenderWindow* & jan){
    this->paused = true;
    this->janela = jan;
    while (this->paused)
    {
        this->update();

        this->render();
    }
}

void PauseGame::tratarEventos(){
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
                    if (this->paused)
                    {
                        this->paused = false;
                    }
                }
                break;

            default:
                break;
        }
    }
}

void PauseGame::update(){
    this->tratarEventos();
}

void PauseGame::render(){
    //Limpa os frames antigos e renderiza um novo frame
    this->janela->clear(sf::Color::Red);

    this->janela->display();
}