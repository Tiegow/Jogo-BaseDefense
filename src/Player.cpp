#include "Player.hpp"

void Player::initTextura(){
    this->textura.loadFromFile("./assets/Player.png"); //Carrega a textura a partir de um arquivo
}

void Player::initSprite(){
    this->sprite.setTexture(this->textura); //Define a textura do sprite
    this->sprite.scale(3.45,3.45);
}

Player::Player(){
    this->initTextura();
    this->initSprite();

    this->movendo = true;
    this->playerClock.restart();
}
Player::~Player(){

}

void Player::mover(){
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

    sf::Vector2f movimento = direcao * this->playerStats.velocidadePlayer;

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

//Funções
sf::Vector2f Player::getCentro(){
    return this->posicaoCentro;
}

sf::Vector2f Player::getPos()
{
    return this->sprite.getPosition();
}

sf::FloatRect Player::getBounds()
{
    return this->sprite.getGlobalBounds();
}

bool Player::podeAtacar()
{
    sf::Time dt = this->playerClock.getElapsedTime();
    if (dt.asSeconds() >= this->playerStats.cadenciaAtaquePlayer)
    {
        if (this->playerStats.municaoPlayer > 0)
        {
            this->playerClock.restart();
            return true;
        }
    }
    
    return false;
}

void Player::coletarCaixa(int munQtd, int vidaQtd)
{
    if (this->playerStats.vidaPlayer < this->playerStats.vidaMaxima)
    {
        if (this->playerStats.vidaPlayer + vidaQtd > this->playerStats.vidaMaxima)
        {
            int cura = this->playerStats.vidaMaxima - this->playerStats.vidaPlayer;
            this->playerStats.vidaPlayer += cura;
        }
        else this->playerStats.vidaPlayer += vidaQtd;
    }
    
    this->playerStats.municaoPlayer += munQtd;
}

void Player::updateMun()
{
    this->playerStats.municaoPlayer--;
}

void Player::setDestino(sf::Vector2f mouseClick)
{
    this->destino = mouseClick;
}

void Player::setPos(sf::Vector2f posicao)
{
    this->sprite.setPosition(posicao);
}

void Player::receberDano(int dano)
{
    this->playerStats.vidaPlayer -= dano;
}

void Player::update(sf::RenderTarget& tela){
    this->posicaoCentro = getPosCentro(this->sprite);
    if (this->destino.y > 0 && this->destino.x > 0 && this->destino.x < tela.getSize().x && this->destino.y < tela.getSize().y)
    {
        this->mover();
    }
}

void Player::render(sf::RenderTarget& tela){
    tela.draw(this->sprite);
}