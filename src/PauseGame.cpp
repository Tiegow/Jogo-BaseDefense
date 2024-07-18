#include "PauseGame.hpp"

PauseGame::PauseGame(){
    this->paused = false;
}

PauseGame::~PauseGame(){

}

void PauseGame::tratarEventos(sf::RenderWindow* & jan){
    //Tratando eventos
    while (jan->pollEvent(this->evento))
    {
        tratarJanela(jan,this->evento);

        switch (this->evento.type)
        {
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

void PauseGame::update(sf::RenderWindow* & jan){
    this->tratarEventos(jan);
}

void PauseGame::render(sf::RenderWindow* & jan){
    //Limpa os frames antigos e renderiza a tela de pause
    jan->clear(sf::Color::Red);

    jan->display();
}

void PauseGame::pause(sf::RenderWindow* & jan){
    this->paused = true;
    while (this->paused)
    {
        this->update(jan);

        this->render(jan);
    }
}