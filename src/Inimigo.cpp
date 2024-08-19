#include "Inimigo.hpp"
#include <time.h>

Inimigo::Inimigo()
{
}

Inimigo::Inimigo(int type, sf::Texture *textura, sf::RenderTarget &tela)
{
    this->tipo = type;
    this->sprite.setTexture(*textura);

    if (this->tipo == 4)
    {
        this->sprite.scale(7, 7);
    }
    else this->sprite.scale(3.45,3.45);

    //Surgimento aleatorio do inimigo
    srand(time(0));
    int bordaRand = rand() % 4; //Um numero de 0 a 3;
    switch (bordaRand) //Escolhendo uma das 4 bordas
    {
        case 0:
            this->sprite.setPosition(rand() % tela.getSize().x, 0.f); //Superior (y = 0)
            break;
        
        case 1:
            this->sprite.setPosition(rand() % tela.getSize().x, tela.getSize().y); //Inferior (y = maximo)
            break;
        
        case 2:
            this->sprite.setPosition(0.f, rand() % tela.getSize().y); //Esquerda (x = 0)
            break;

        case 3:
            this->sprite.setPosition(tela.getSize().x, rand() % tela.getSize().y); //Direita (x = maximo)
            break;

        default:
            break;
    }

    switch (this->tipo)
    {
    case 1:
        this->vida = 10;
        this->distAtaque = 150;
        this->safeDist = 300;
        this->velocidade = 3;
        this->cadenciaAtaque = 2; //segundos        
        break;
    
    case 2:
        this->vida = 10;
        this->distAtaque = 150;
        this->safeDist = 300;
        this->velocidade = 7;
        this->cadenciaAtaque = 0.5; 
        break;

    case 3:
        this->vida = 10;
        this->distAtaque = 1000;
        this->safeDist = 600;
        this->velocidade = 1;
        this->cadenciaAtaque = 1; 
        break;
    
    case 4:
        this->vida = 30;
        this->distAtaque = 200;
        this->safeDist = 300;
        this->velocidade = 1;
        this->cadenciaAtaque = 0.2; 
        break;

    default:
        break;
    }

    this->movendo = true;
    this->fora = false;
}

Inimigo::~Inimigo()
{
}

void Inimigo::moverIA()
{
    //Manter certa distancia do alvo
    if (this->destino.x - this->posicaoCentro.x < 0)
    {
        this->destino.x += this->safeDist;
    }
    else
    {
        this->destino.x -= this->safeDist;
    }

    if (this->destino.y - this->posicaoCentro.y < 0)
    {
        this->destino.y += this->safeDist;
    }
    else
    {
        this->destino.y -= this->safeDist;
    }
}

void Inimigo::teleport(sf::RenderTarget &tela)
{
    sf::Time tempoTP = this->tpClock.getElapsedTime();
    if (tempoTP.asSeconds() >= 2)
    {
        sf::Vector2f telPoint;
        telPoint.x = rand() % tela.getSize().x;
        telPoint.y = rand() % tela.getSize().y;
        this->sprite.setPosition(telPoint);   
        this->tpClock.restart();
    }
}

void Inimigo::mover()
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

    //Verifica se deve continuar andando
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

void Inimigo::foraTela(sf::RenderTarget &tela)
{
    /*
        Verifica se o inimigo esta muito tempo fora da tela por algum motivo
            - Quando o inimigo é expulso pelas laterais do mapa, ele volta por cima
            - Quando o inimigo é expulso por cima ou por baixo, ele volta pela esquerda
    */
    if (!this->fora)
    {
        this->positionClock.restart();
    }
    
    if (this->posicaoCentro.x > tela.getSize().x || this->posicaoCentro.x < 0)
    {   
        this->fora = true;
        sf::Time dt = this->positionClock.getElapsedTime();
        if (dt.asSeconds() >= 4) //4 segundos fora da tela
        {
            this->positionClock.restart();
            this->sprite.setPosition(rand() % tela.getSize().x, 0.f);
            this->fora = false;
        }
    }
    else if (this->posicaoCentro.y > tela.getSize().y || this->posicaoCentro.y < 0)
    {   
        this->fora = true;
        sf::Time dt = this->positionClock.getElapsedTime();
        if (dt.asSeconds() >= 4) //4 segundos fora da tela
        {
            this->positionClock.restart();
            this->sprite.setPosition(0.f, rand() % tela.getSize().y);
            this->fora = false;
        }
    }
    else this->fora = false;
}

sf::Vector2f Inimigo::getCentro()
{
    return this->posicaoCentro;
}

sf::FloatRect Inimigo::getBounds()
{
    return this->sprite.getGlobalBounds();
}

int Inimigo::getTipo()
{
    return this->tipo;
}

int Inimigo::getVida()
{
    return this->vida;
}

bool Inimigo::atacar()
{
    //Ataca de acordo com a cadencia de ataque e se o alvo estiver dentro do alcance
    sf::Time dt = this->atackClock.getElapsedTime();    
    if (dt.asSeconds() >= this->cadenciaAtaque)
    {   
        if (this->destino.x - this->posicaoCentro.x <= this->distAtaque && this->destino.y - this->posicaoCentro.y <= this->distAtaque)
        {
            this->atackClock.restart();
            return true;          
        }
    }
    return false;
}

void Inimigo::receberDano(int dano)
{
    this->vida -= dano;
}

void Inimigo::update(sf::Vector2f destPos, sf::RenderTarget &tela)
{
    this->posicaoCentro = getPosCentro(this->sprite);
    this->destino = destPos;
    this->moverIA();
    if (this->tipo == 3)
    {
        this->teleport(tela);
        this->mover();
    }
    else
    {
        this->mover();
        this->foraTela(tela);
    }
}

void Inimigo::render(sf::RenderTarget &tela)
{
    tela.draw(this->sprite);
}
