#include "GameInterfaces.hpp"

sf::Vector2f centrObjeto(sf::Vector2u tamJanela, sf::Vector2f tamObj){
    /*
        @Vector2f

        - Recebe tamanho da janela
        - Recebe tamanho do objeto

        Retorna o vetor com a posição necessária para centralizar um objeto na tela
    */
    sf::Vector2f posicaoObj;
    posicaoObj.x = (tamJanela.x - tamObj.x) / 2;
    posicaoObj.y = (tamJanela.y - tamObj.y) / 2;

    return posicaoObj;
}

void pause(sf::RenderTarget& target){
    target.clear(sf::Color::Black);

    sf::RectangleShape botao;
    botao.setFillColor(sf::Color::Red);
    botao.setSize(sf::Vector2f(400.f,200.f));

    sf::Vector2f botaoPos = centrObjeto(target.getSize(), botao.getSize());
    botao.setPosition(botaoPos);

    target.draw(botao);
}

