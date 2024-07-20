#include "Player.hpp"

void Player::initTextura(){
    this->textura.loadFromFile("./assets/Player.png"); //Carrega a textura a partir de um arquivo
}

void Player::initSprite(){
    this->sprite.setTexture(this->textura); //Define a textura do sprite
    this->sprite.scale(3.45,3.45);
    this->sprite.setPosition(30.f,30.f);
}

Player::Player(){
    this->initTextura();
    this->initSprite();

    this->vida = 100;
    this->municao = 25;
    this->velocidade = 5;
    this->movendo = true;
}
Player::~Player(){

}

//Funções
void Player::mover(sf::Vector2f mouseClick){
    if (mouseClick.y > 0 && mouseClick.x > 0)
    {
        sf::Vector2f moverPara = mouseClick - this->posicao; //Vetor de direção ao ponto do click

        float comprimento = std::sqrt(moverPara.x * moverPara.x + moverPara.y * moverPara.y);
        /*
            Calcula a magnitude do vetor de direção (Teorema de Pitágoras)
            - A magnitude do vetor é equivale à hipotenusa do triângulo formado pelos eixos do vetor
        */

        if (comprimento != 0) //Normalizando vetor para obter um vetor unitário
        {
            moverPara.x /= comprimento;
            moverPara.y /= comprimento;
        }

        sf::Vector2f movimento = moverPara * this->velocidade;

        if (std::sqrt(movimento.x * movimento.x + movimento.y * movimento.y) >= comprimento)
        {
            this->movendo = false;
        } else {
            this->movendo = true;
        }

        if (movendo)
        {
            this->sprite.move(movimento);
        }   
    }
}

sf::Vector2f Player::getPosCentro(){
    /*
        Calcula a posição do ponto central do sprite
            *SFML não considera o centro do sprite como sendo as coordenadas da sua posição
    */
    sf::Vector2f spritePos = sprite.getPosition();
    sf::FloatRect spriteDimensoes = sprite.getGlobalBounds();
    sf::Vector2f centro(spritePos.x + spriteDimensoes.width / 2, spritePos.y + spriteDimensoes.height / 2);

    return centro;
}

void Player::update(sf::Vector2f mouseClick){
    this->posicao = this->getPosCentro();
    this->mover(mouseClick);
}

void Player::render(sf::RenderTarget& tela){
    tela.draw(this->sprite);
}