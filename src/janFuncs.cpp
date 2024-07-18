#include "janFuncs.hpp"

void tratarJanela(sf::RenderWindow* & jan, sf::Event ev){
    //Gerencia os eventos da janela
    switch (ev.type)
    {
    case sf::Event::Closed:
        jan->close();
        delete jan;
        break;
    
    default:
        break;
    }

    
}