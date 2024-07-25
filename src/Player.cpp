#include "Player.hpp"
#include <iostream>

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
    this->intervaloAtaqueMax = 10.f;
    this->intervaloAtaque = this->intervaloAtaqueMax;
    this->movendo = true;
}
Player::~Player(){

}

//Funções
void Player::mover(){
    if (this->destino.y > 0 && this->destino.x > 0)
    {
        sf::Vector2f direcao = this->destino - this->posicaoCentro; //Vetor de direção ao ponto do click
        
        float comprimento = std::sqrt(direcao.x * direcao.x + direcao.y * direcao.y);
        /*
            Calcula a magnitude do vetor de direção (Teorema de Pitágoras)
            - A magnitude do vetor é equivale à hipotenusa do triângulo formado pelos eixos do vetor
        */

        if (comprimento != 0) //Normalizando vetor direção para obter um vetor unitário
        {
            direcao.x /= comprimento;
            direcao.y /= comprimento;
        }

        sf::Vector2f movimento = direcao * this->velocidade;

        //Verifica se o jogador deve continuar andando
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

sf::Vector2f Player::getPos()
{
    return this->sprite.getPosition();
}

sf::FloatRect Player::getBounds()
{
    return this->sprite.getGlobalBounds();
}

void Player::updateAtaque()
{
    if (this->intervaloAtaque < this->intervaloAtaqueMax)
    {
        this->intervaloAtaque += 0.5;
    }
}

void Player::setDestino(sf::Vector2f mouseClick)
{
    this->destino = mouseClick;
}

bool Player::podeAtacar()
{
    if (this->intervaloAtaque >= this->intervaloAtaqueMax)
    {
        this->intervaloAtaque = 0;
        return true;
    }
    
    return false;
}

void Player::receberDano(int dano)
{
    this->vida -= dano;
}

void Player::setIntervAtaque(float max)
{
    this->intervaloAtaqueMax = max;
}

float Player::getIntervAtaque()
{
    return this->intervaloAtaqueMax;
}

void Player::update(){
    this->updateAtaque();
    this->posicaoCentro = this->getPosCentro();
    this->mover();
}

void Player::render(sf::RenderTarget& tela){
    tela.draw(this->sprite);
}