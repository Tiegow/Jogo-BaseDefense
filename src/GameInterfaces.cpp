#include "GameInterfaces.hpp"

sf::Vector2f centrObjeto(sf::Vector2u tamJanela, sf::Vector2f tamObj){
    /*
        - Recebe tamanho da janela
        - Recebe tamanho do objeto

        Retorna o vetor com a posição necessária para centralizar um objeto na tela
    */
    sf::Vector2f posicaoObj;
    posicaoObj.x = (tamJanela.x - tamObj.x) / 2;
    posicaoObj.y = (tamJanela.y - tamObj.y) / 2;

    return posicaoObj;
}

sf::Vector2f getMouseCoords(sf::RenderWindow& janela){
    sf::Vector2i mouseWindow = sf::Mouse::getPosition(janela);
    sf::Vector2f mousePos = janela.mapPixelToCoords(mouseWindow);

    return mousePos; // Retorna o vetor coordenada do mouse em relação à janela do jogo
}

void pause(sf::RenderTarget& target){ // "Desenha" a tela de pause
    target.clear(sf::Color::Black);

    sf::RectangleShape botao;
    botao.setFillColor(sf::Color::Blue);
    botao.setSize(sf::Vector2f(400.f,200.f));

    sf::Vector2f botaoPos = centrObjeto(target.getSize(), botao.getSize());
    botao.setPosition(botaoPos);

    target.draw(botao);
}

void gameOver(sf::RenderTarget& target){ // "Desenha" a tela de fim de jogo
    target.clear(sf::Color::Black);

    sf::RectangleShape botao;
    botao.setFillColor(sf::Color::Red);
    botao.setSize(sf::Vector2f(400.f,200.f));

    sf::Vector2f botaoPos = centrObjeto(target.getSize(), botao.getSize());
    botao.setPosition(botaoPos);

    target.draw(botao);
}

