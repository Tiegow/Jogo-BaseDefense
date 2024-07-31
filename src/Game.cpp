#include "Game.hpp"
#include <iostream>

//Funções private
void Game::initVars(){
    this->janela = nullptr;
    this->gameLevel = 1;
    this->paused = false;
    this->over = false;
    this->chancesDropMun = 0.36; //(x * 100)%
    this->chancesDropVida = 0.2; //(x * 100)%

    this->spawnInimVel = 4;
    this->maxInimigos = 5;
    this->clock.restart();
}

void Game::initTexturas(){
    /*
        Carrega as texturas de objetos no jogo
        - Evita ter que rodar .loadFromFile toda vez que surgir um objeto novo
    */
    this->texturas["TIRO"] = new sf::Texture;
    this->texturas["TIRO"]->loadFromFile("./assets/Tiro.png");

    this->texturas["INIMIGO1"] = new sf::Texture;
    this->texturas["INIMIGO1"]->loadFromFile("./assets/Inimigo1.png");

    //Texturas da GUI
    this->texturas["BOTAO1"] = new sf::Texture;
    this->texturas["BOTAO1"]->loadFromFile("./assets/contBot.png");
    this->texturas["BOTAO2"] = new sf::Texture;
    this->texturas["BOTAO2"]->loadFromFile("./assets/sairBot.png");
    this->texturas["PAUSETXT"] = new sf::Texture;
    this->texturas["PAUSETXT"]->loadFromFile("./assets/pauseSprite.png");
    this->texturas["OVERTXT"] = new sf::Texture;
    this->texturas["OVERTXT"]->loadFromFile("./assets/overSprite.png");
}

void Game::initJanela(){
    this->videoMode.width = 1800;
    this->videoMode.height = 1300;
    this->janela = new sf::RenderWindow(this->videoMode, "Base Defense", sf::Style::Titlebar | sf::Style::Close);
    this->janela->setFramerateLimit(60);
}

void Game::renderPause()
{
    sf::Sprite pauseText;
    sf::Vector2f textPos;
    pauseText.setTexture(*this->texturas["PAUSETXT"]);
    pauseText.setScale(4.f, 4.f);
    textPos = centrObjeto(this->janela->getSize(), pauseText.getGlobalBounds());
    pauseText.setPosition(textPos.x, 30.f);

    sf::Sprite contBot;
    sf::Sprite sairBot;
    sf::Vector2f botPos;
    float botaoScale = 2.f;
    contBot.setTexture(*this->texturas["BOTAO1"]);
    contBot.setScale(botaoScale, botaoScale);
    botPos = centrObjeto(this->janela->getSize(), contBot.getGlobalBounds());
    contBot.setPosition(botPos);

    sairBot.setTexture(*this->texturas["BOTAO2"]);
    sairBot.setScale(botaoScale, botaoScale);
    botPos = centrObjeto(this->janela->getSize(), sairBot.getGlobalBounds());
    sairBot.setPosition(botPos.x, botPos.y + 300.f);

    this->janela->clear(sf::Color(23,21,35,255));
    this->janela->draw(pauseText);
    this->janela->draw(contBot);
    this->janela->draw(sairBot);
}

void Game::renderOver()
{
    sf::Sprite overText;
    sf::Vector2f textPos;
    overText.setTexture(*this->texturas["OVERTXT"]);
    overText.setScale(4.f, 4.f);
    textPos = centrObjeto(this->janela->getSize(), overText.getGlobalBounds());
    overText.setPosition(textPos.x, 30.f);

    sf::Sprite contBot;
    sf::Sprite sairBot;
    sf::Vector2f botPos;
    float botaoScale = 2.f;
    contBot.setTexture(*this->texturas["BOTAO1"]);
    contBot.setScale(botaoScale, botaoScale);
    botPos = centrObjeto(this->janela->getSize(), contBot.getGlobalBounds());
    contBot.setPosition(botPos);

    sairBot.setTexture(*this->texturas["BOTAO2"]);
    sairBot.setScale(botaoScale, botaoScale);
    botPos = centrObjeto(this->janela->getSize(), sairBot.getGlobalBounds());
    sairBot.setPosition(botPos.x, botPos.y + 300.f);

    this->janela->clear(sf::Color(22,9,9,255));
    this->janela->draw(overText);
    this->janela->draw(contBot);
    this->janela->draw(sairBot);
}
//----------------------------------------//

//Construtores | Destrutores
Game::Game(){
    this->initVars();
    this->initJanela();
    this->initTexturas();
    this->base.spawn(*this->janela);
}

Game::~Game(){
    delete this->janela;
    this->janela = nullptr;
    
    //Itera sobre o map texturas para deletar os ponteiros pra sf::Texture
    for(auto &textura : this->texturas){
        delete textura.second;
        textura.second = nullptr;
    }

    //Itera sobre a list tiros para deletar os ponteiros pra Tiro
    for(auto *tiro : this->tiros){
        delete tiro;
        tiro = nullptr;
    }

    //Itera sobre a list inimigos para deletar os ponteiros pra Inimigo
    for(auto *inim : this->inimigos){
        delete inim;
        inim = nullptr;
    }
}
//----------------------------------------//


//Funções public
bool Game::isRunning(){
    return this->janela->isOpen();
}

void Game::tratarEventos(){
    //Tratando eventos
    while (this->janela->pollEvent(this->evento))
    {
        //Eventos da tela e da interface
        switch (this->evento.type)
        {
            case sf::Event::Closed:
                this->janela->close();
                break;
                
            case sf::Event::KeyPressed:
            //ESC
                if(this->evento.key.code == sf::Keyboard::Escape){ 
                    this->paused = !paused;
                }
                break;

            default:
                break;
        }
        //Eventos do jogo
        if (!this->paused && !this->over)
        {
            switch (this->evento.type)
            {
                case sf::Event::KeyPressed:
                //Q
                    if(this->evento.key.code == sf::Keyboard::Q && this->heroi.podeAtacar()){
                        this->mousePos = getMouseCoords(*this->janela);
                        this->tiros.push_back(new Tiro(this->texturas["TIRO"], this->heroi.getCentro(), mousePos, false));
                        this->heroi.updateMun();
                    }
                    break;
            
                default:
                    break;
            }

            //Mouse
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                this->mousePos = getMouseCoords(*this->janela);
                this->heroi.setDestino(this->mousePos);
            }
        }
    }
}

void Game::tratarTiros(){
    std::list<Tiro*>::iterator contador = this->tiros.begin();
    for(auto *tiro : this->tiros){
        tiro->update();

        //Colisões
        if (tiro->isEnemy())
        {
            //Base
            if (tiro->getBounds().intersects(this->base.baseBody.getGlobalBounds()))
            {
                this->base.receberDano(tiro->atingir());
            }
            //Player
            if (tiro->getBounds().intersects(this->heroi.getBounds()))
            {
                this->heroi.receberDano(tiro->atingir());
            }
        }
        else
        {
            //Inimigos
            for(auto *inimigo : this->inimigos){
                if (tiro->getBounds().intersects(inimigo->getBounds()))
                {
                    inimigo->receberDano(tiro->atingir());
                }
            }
        }
        
        //Removendo caso saia da tela ou atinja algo
        if
        (
            tiro->getBounds().top + tiro->getBounds().height < 0.f ||
            tiro->getBounds().left + tiro->getBounds().width < 0.f ||
            tiro->getBounds().top + tiro->getBounds().height > this->janela->getSize().y ||
            tiro->getBounds().left + tiro->getBounds().width > this->janela->getSize().x ||
            tiro->atingido()
        )
        {
            delete tiro;
            tiro = nullptr;
            this->tiros.erase(contador);
        }

        ++contador;
    }
}

void Game::tratarInimigos()
{
    //Spawnando inimigo
    sf::Time dt = this->clock.getElapsedTime();
    if (dt.asSeconds() >= this->spawnInimVel)
    {
        if (this->inimigos.size() < this->maxInimigos)
        {
            this->clock.restart();
            this->inimigos.push_back(new Inimigo(this->texturas["INIMIGO1"], *this->janela));
        }
    }

    std::list<Inimigo*>::iterator contador = this->inimigos.begin();
    for (auto *inimigo : this->inimigos)
    {
        inimigo->update(this->heroi.getCentro(), *this->janela);

        if (inimigo->atacar())
        {
            this->tiros.push_back(new Tiro(this->texturas["TIRO"], inimigo->getCentro(), this->heroi.getCentro(), true));
        }

        //Removendo ao morrer
        if (inimigo->getVida() <= 0)
        {
            if (static_cast<double>(rand()) / RAND_MAX < this->chancesDropMun)
            {
                std::cout << " Dropando caixa \n";
            }

            if (static_cast<double>(rand()) / RAND_MAX < this->chancesDropVida)
            {
                std::cout << " Dropando Vida \n";
            }
            
            delete inimigo;
            inimigo = nullptr;
            this->inimigos.erase(contador);
        }
        
        contador++;
    }
}

void Game::update(){
    if (this->base.getVida() <= 0 || this->heroi.getVida() <= 0)
    {
        this->over = true;
    }

    this->tratarEventos();
    
    if (!this->over)
    {
        if (this->paused)
        {
            //Abrir tela de pause
            this->renderPause();
        }
        else
        {
            //Fluxo normal do game
            this->base.update();
            this->heroi.update(*this->janela);
            this->tratarInimigos();
            this->tratarTiros();
            this->GUI.update(this->heroi.getVida(), this->heroi.getMun());
        }
    }
    else
    {
        // gameOver(*this->janela);
        this->renderOver();
    }
    
}

void Game::render(){
    //Renderiza os elementos do jogo
    if (!this->paused && !this->over)
    {
        this->janela->clear(sf::Color::White);

        this->base.render(*this->janela);
        this->heroi.render(*this->janela);
        
        for(auto *inimigo : this->inimigos){
            inimigo->render(*this->janela);
        }
        for(auto *tiro : this->tiros){
            tiro->render(*this->janela);
        }

        // this->janela->draw(this->vidaTxt);
        this->GUI.render(*this->janela);
    }
    this->janela->display();
}
//----------------------------------------//