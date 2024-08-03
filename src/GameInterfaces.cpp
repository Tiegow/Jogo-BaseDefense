#include "GameInterfaces.hpp"
#include <iostream>

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

sf::Vector2f centrObjeto(sf::Vector2u tamJanela, sf::FloatRect objBounds){
    /*
        - Recebe tamanho da janela
        - Recebe as extremidades do objeto

        Retorna o vetor com a posição necessária para centralizar um objeto na tela
    */
    sf::Vector2f posicaoObj;
    posicaoObj.x = (tamJanela.x - objBounds.width) / 2;
    posicaoObj.y = (tamJanela.y - objBounds.height) / 2;

    return posicaoObj;
}

sf::Vector2f getMouseCoords(sf::RenderWindow& janela){
    sf::Vector2i mouseWindow = sf::Mouse::getPosition(janela);
    sf::Vector2f mousePos = janela.mapPixelToCoords(mouseWindow);

    return mousePos; // Retorna o vetor coordenada do mouse em relação à janela do jogo
}

sf::Vector2f getPosCentro(sf::Sprite& sprite){
    /*
        Calcula a posição do ponto central do sprite
            *SFML não considera o centro do sprite como sendo as coordenadas da sua posição
    */
    sf::Vector2f spritePos = sprite.getPosition();
    sf::FloatRect spriteDimensoes = sprite.getGlobalBounds();
    sf::Vector2f centro(spritePos.x + spriteDimensoes.width / 2, spritePos.y + spriteDimensoes.height / 2);

    return centro;
}

sf::Vector2f getPosCentro(sf::RectangleShape& retangulo){
    /*
        Calcula a posição do ponto central do retangulo
            *SFML não considera o centro do retangulo como sendo as coordenadas da sua posição
    */
    sf::Vector2f retanguloPos = retangulo.getPosition();
    sf::FloatRect retanguloDimensoes = retangulo.getGlobalBounds();
    sf::Vector2f centro(retanguloPos.x + retanguloDimensoes.width / 2, retanguloPos.y + retanguloDimensoes.height / 2);

    return centro;
}

bool botaoPres(sf::RenderWindow &janela, sf::FloatRect botaoBounds)
{
    sf::Vector2f mousePosit = getMouseCoords(janela);
    if (botaoBounds.contains(mousePosit))
    {
        return true;
    }
        
    return false;
}
