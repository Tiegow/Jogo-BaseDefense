#include "Inimigo.hpp"

Inimigo::Inimigo()
{
}

Inimigo::Inimigo(sf::Texture *textura)
{
    this->sprite.setTexture(*textura);
    this->sprite.scale(3.45,3.45);
    this->sprite.setPosition(30.f,30.f);
    this->vida = 10;
    this->velocidade = 3;
    this->distAtaque = 150;
    this->safeDist = 300;
    this->cadenciaAtaque = 2;
    this->movendo = true;
}

Inimigo::~Inimigo()
{
}

sf::Vector2f Inimigo::getPosCentro()
{
    /*
        Calcula a posição do ponto central do sprite
            *SFML não considera o centro do sprite como sendo as coordenadas da sua posição
    */
    sf::Vector2f spritePos = sprite.getPosition();
    sf::FloatRect spriteDimensoes = sprite.getGlobalBounds();
    sf::Vector2f centro(spritePos.x + spriteDimensoes.width / 2, spritePos.y + spriteDimensoes.height / 2);

    return centro;
}

sf::FloatRect Inimigo::getBounds()
{
    return this->sprite.getGlobalBounds();
}

int Inimigo::getVida()
{
    return this->vida;
}

void Inimigo::moverIA()
{
    //Manter certa distancia do player
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

bool Inimigo::atacar()
{
    //Ataca de acordo com a cadencia de ataque e se o alvo estiver dentro do alcance
    sf::Time dt = this->enemyClock.getElapsedTime();    
    if (dt.asSeconds() >= this->cadenciaAtaque)
    {   
        if (this->destino.x - this->posicaoCentro.x <= this->distAtaque && this->destino.y - this->posicaoCentro.y <= this->distAtaque)
        {
            this->enemyClock.restart();
            return true;          
        }
    }
    return false;
}

void Inimigo::receberDano(int dano)
{
    this->vida -= dano;
}

void Inimigo::update(sf::Vector2f playerPos)
{
    this->posicaoCentro = this->getPosCentro();
    this->destino = playerPos;
    this->moverIA();
    this->mover();
}

void Inimigo::render(sf::RenderTarget &tela)
{
    tela.draw(this->sprite);
}
