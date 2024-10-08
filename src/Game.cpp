#include "Game.hpp"
#include <iostream>

//Funções private
void Game::initVars(){
    this->janela = nullptr;
    this->paused = false;
    this->over = false;
    this->up = false;
    this->tempo = this->stats.tempoLevel;

    //Iniciando o arquivo de score
    std::ifstream saveScore("score.txt"); //Abre o arquivo somente para leitura
    if (!saveScore.good())  //Se houver algum erro (arquivo nao existir), crie um arquivo com o score salvo 0
    {
        std::fstream saveScore("score.txt", std::ios::out);
        saveScore << 0;
        saveScore.close();
    }
    saveScore.close();
}

void Game::initTexturas(){
    /*
        Carrega as texturas de objetos no jogo
        - Evita ter que rodar .loadFromFile toda vez que surgir um objeto novo
    */
    this->texturas["TIRO"] = new sf::Texture;
    this->texturas["TIRO"]->loadFromFile("./assets/Tiro.png");

    //Texturas de inimigos
    this->texturas["INIMIGO1"] = new sf::Texture;
    this->texturas["INIMIGO1"]->loadFromFile("./assets/Inimigo1.png");

    this->texturas["INIMIGO2"] = new sf::Texture;
    this->texturas["INIMIGO2"]->loadFromFile("./assets/Inimigo2.png");

    this->texturas["INIMIGO3"] = new sf::Texture;
    this->texturas["INIMIGO3"]->loadFromFile("./assets/Inimigo3.png");

    this->texturas["INIMIGO4"] = new sf::Texture;
    this->texturas["INIMIGO4"]->loadFromFile("./assets/Inimigo4.png");

    //Texturas de itens
    this->texturas["MUNICAO"] = new sf::Texture;
    this->texturas["MUNICAO"]->loadFromFile("./assets/Munbox1.png");

    this->texturas["VIDA"] = new sf::Texture;
    this->texturas["VIDA"]->loadFromFile("./assets/Vidabox.png");

    //Texturas da GUI
    this->texturas["BOTAO1"] = new sf::Texture;
    this->texturas["BOTAO1"]->loadFromFile("./assets/contBot.png");

    this->texturas["BOTAO2"] = new sf::Texture;
    this->texturas["BOTAO2"]->loadFromFile("./assets/sairBot.png");

    this->texturas["PAUSETXT"] = new sf::Texture;
    this->texturas["PAUSETXT"]->loadFromFile("./assets/pauseSprite.png");

    this->texturas["OVERTXT"] = new sf::Texture;
    this->texturas["OVERTXT"]->loadFromFile("./assets/overSprite.png");

    this->texturas["UPV"] = new sf::Texture;
    this->texturas["UPV"]->loadFromFile("./assets/UpgradeV.png");

    this->texturas["UPS"] = new sf::Texture;
    this->texturas["UPS"]->loadFromFile("./assets/UpgradeS.png");

    this->texturas["UPT"] = new sf::Texture;
    this->texturas["UPT"]->loadFromFile("./assets/UpgradeT.png");

    this->texturas["UPTS"] = new sf::Texture;
    this->texturas["UPTS"]->loadFromFile("./assets/UpgradeTS.png");

    this->texturas["UPVB"] = new sf::Texture;
    this->texturas["UPVB"]->loadFromFile("./assets/UpgradeVB.png");

    this->texturas["UPCB"] = new sf::Texture;
    this->texturas["UPCB"]->loadFromFile("./assets/UpgradeCB.png");

    this->texturas["UPEB"] = new sf::Texture;
    this->texturas["UPEB"]->loadFromFile("./assets/UpgradeEB.png");
}

void Game::initSom()
{
    this->audios.musica1.openFromFile("./assets/Audio/TowerDefenseTheme.wav");

    this->audios.bufferT1.loadFromFile("./assets/Audio/laser1.wav");
    this->audios.tiroBaixoSom.setBuffer(this->audios.bufferT1);

    this->audios.bufferT2.loadFromFile("./assets/Audio/laser4.wav");
    this->audios.tiroSom.setBuffer(this->audios.bufferT2);

    this->audios.bufferAtbase.loadFromFile("./assets/Audio/hit.wav");
    this->audios.atingidoBaseSom.setBuffer(this->audios.bufferAtbase);

    this->audios.bufferAtinim.loadFromFile("./assets/Audio/kill.wav");
    this->audios.atingidoInimSom.setBuffer(this->audios.bufferAtinim);

    this->audios.bufferUpgrade.loadFromFile("./assets/Audio/powerUp.wav");
    this->audios.upgradeSom.setBuffer(this->audios.bufferUpgrade);

    this->audios.bufferColetar.loadFromFile("./assets/Audio/colect.wav");
    this->audios.coletarSom.setBuffer(this->audios.bufferColetar);

    this->audios.musica1.setVolume(30);
    this->audios.musica1.play();
    this->audios.musica1.setLoop(true);
}

void Game::initJanela(){
    this->videoMode.width = 1800;
    this->videoMode.height = 1300;
    this->janela = new sf::RenderWindow(this->videoMode, "Base Defense", sf::Style::Titlebar | sf::Style::Close);
    this->janela->setFramerateLimit(60);
}

//Construtores | Destrutores
Game::Game(){
    this->initVars();
    this->initJanela();
    this->initSom();
    this->initTexturas();
    this->base.spawn(*this->janela);
    this->heroi.setPos(centrObjeto(this->janela->getSize(), this->heroi.getBounds()));
}

Game::~Game(){
    this->audios.musica1.stop();

    delete this->janela;
    this->janela = nullptr;
    
    //Itera sobre o map texturas para deletar os ponteiros pra sf::Texture
    for(auto &textura : this->texturas){
        delete textura.second;
        textura.second = nullptr;
    }

    this->limparGame();
}
//----------------------------------------//
bool Game::isRunning(){
    return this->janela->isOpen();
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

    //Mouse
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (botaoPres(*this->janela, contBot.getGlobalBounds()))
        {
            this->paused = false;
        }
        if (botaoPres(*this->janela, sairBot.getGlobalBounds()))
        {
            this->janela->close();
        }
    }

    this->janela->clear(sf::Color(23,21,35,255));
    this->janela->draw(pauseText);
    this->janela->draw(contBot);
    this->janela->draw(sairBot);
}

void Game::renderOver()
{
    this->levelClock.restart();
    this->spawnClock.restart();

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

    //Mouse
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (botaoPres(*this->janela, contBot.getGlobalBounds()))
        {
            this->stats.statsReset();
            this->heroi.playerStats.statsReset();
            this->base.resetBase();

            this->limparGame();

            this->tempo = this->stats.tempoLevel;
            this->over = false;
        }
        if (botaoPres(*this->janela, sairBot.getGlobalBounds()))
        {
            this->janela->close();
        }
    }

    this->janela->clear(sf::Color(22,9,9,255));
    this->janela->draw(overText);
    this->janela->draw(contBot);
    this->janela->draw(sairBot);
}

void Game::renderUpgrade()
{
    float botaoScale = 2;
    sf::Vector2f botPos;
    this->janela->clear(sf::Color(23,21,35,255));

    sf::Sprite playerVUp;
    playerVUp.setTexture(*this->texturas["UPV"]);
    playerVUp.setScale(botaoScale, botaoScale);
    botPos = centrObjeto(this->janela->getSize(), playerVUp.getGlobalBounds());
    playerVUp.setPosition(botPos.x - playerVUp.getLocalBounds().width * 6, botPos.y);
    this->janela->draw(playerVUp);

    sf::Sprite playerSUp;
    playerSUp.setTexture(*this->texturas["UPS"]);
    playerSUp.setScale(botaoScale, botaoScale);
    botPos = centrObjeto(this->janela->getSize(), playerSUp.getGlobalBounds());
    playerSUp.setPosition(botPos.x - playerSUp.getLocalBounds().width * 2, botPos.y);
    this->janela->draw(playerSUp);

    sf::Sprite playerTUp;
    if (this->heroi.playerStats.cadLevel < this->heroi.playerStats.cadMaxLevel)
    {
        playerTUp.setTexture(*this->texturas["UPT"]);
        playerTUp.setScale(botaoScale, botaoScale);
        botPos = centrObjeto(this->janela->getSize(), playerTUp.getGlobalBounds());
        playerTUp.setPosition(botPos.x + playerTUp.getLocalBounds().width * 2, botPos.y);

        this->janela->draw(playerTUp);
    }

    sf::Sprite playerTSUp;
    playerTSUp.setTexture(*this->texturas["UPTS"]);
    playerTSUp.setScale(botaoScale, botaoScale);
    botPos = centrObjeto(this->janela->getSize(), playerTSUp.getGlobalBounds());
    playerTSUp.setPosition(botPos.x + playerTSUp.getLocalBounds().width * 6, botPos.y);
    this->janela->draw(playerTSUp);

    //BASE
    //Vida recebida por cura
    sf::Sprite baseVUp;
    if (this->base.stats.curaLevel < this->base.stats.maxCuraLevel)
    {
        baseVUp.setTexture(*this->texturas["UPVB"]);
        baseVUp.setScale(botaoScale, botaoScale);
        botPos = centrObjeto(this->janela->getSize(), baseVUp.getGlobalBounds());
        baseVUp.setPosition(botPos.x, botPos.y + 200);
        this->janela->draw(baseVUp);
    }

    //Velocidade da cura
    sf::Sprite baseCUp;
    if (this->base.stats.velLevel < this->base.stats.maxVelLevel)
    {
        baseCUp.setTexture(*this->texturas["UPCB"]);
        baseCUp.setScale(botaoScale, botaoScale);
        botPos = centrObjeto(this->janela->getSize(), baseCUp.getGlobalBounds());
        baseCUp.setPosition(botPos.x + baseCUp.getLocalBounds().width * 4, botPos.y + 200);
        this->janela->draw(baseCUp);
    }

    //Escudo
    sf::Sprite baseEUp;
    if (this->base.stats.escudoLevel < this->base.stats.maxEscudoLevel)
    {
        baseEUp.setTexture(*this->texturas["UPEB"]);
        baseEUp.setScale(botaoScale, botaoScale);
        botPos = centrObjeto(this->janela->getSize(), baseEUp.getGlobalBounds());
        baseEUp.setPosition(botPos.x - baseEUp.getLocalBounds().width * 4, botPos.y + 200);
        this->janela->draw(baseEUp);
    }

    //Mouse
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        //Upgrade Vida
        if (botaoPres(*this->janela, playerVUp.getGlobalBounds()))
        {
            this->audios.upgradeSom.play();
            this->heroi.playerStats.statsUpgradeVida();

            //Começando nova fase
            this->levelClock.restart();
            this->proximaFase();
        }
        //Upgrade Cadencia
        else if (botaoPres(*this->janela, playerTUp.getGlobalBounds()))
        {
            this->audios.upgradeSom.play();
            this->heroi.playerStats.statsUpgradeCadencia();

            //Começando nova fase
            this->levelClock.restart();
            this->proximaFase();
        }
        //Upgrade Velocidade
        else if (botaoPres(*this->janela, playerSUp.getGlobalBounds()))
        {
            this->audios.upgradeSom.play();
            this->heroi.playerStats.statsUpgradeVelocidade();

            //Começando nova fase
            this->levelClock.restart();
            this->proximaFase();
        }
        //Upgrade Velocidade Projétil
        else if (botaoPres(*this->janela, playerTSUp.getGlobalBounds()))
        {
            this->audios.upgradeSom.play();
            this->heroi.playerStats.statsUpgradeVelT();

            //Começando nova fase
            this->levelClock.restart();
            this->proximaFase();
        }
        //Upgrade Cura Base
        else if (botaoPres(*this->janela, baseVUp.getGlobalBounds()))
        {
            this->audios.upgradeSom.play();
            this->base.stats.statsUpgradeCura();
            this->base.restaurar();

            //Começando nova fase
            this->levelClock.restart();
            this->proximaFase();
        }
        //Upgrade Velocidade Cura Base
        else if (botaoPres(*this->janela, baseCUp.getGlobalBounds()))
        {
            this->audios.upgradeSom.play();
            this->base.stats.statsUpgradeVel();

            //Começando nova fase
            this->levelClock.restart();
            this->proximaFase();
        }
        //Upgrade Velocidade Escudo Base
        else if (botaoPres(*this->janela, baseEUp.getGlobalBounds()))
        {
            this->audios.upgradeSom.play();
            this->base.stats.statsUpgradeEscudo();

            //Começando nova fase
            this->levelClock.restart();
            this->proximaFase();
        }
    }
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
        if (!this->paused && !this->over && !this->up)
        {
            switch (this->evento.type)
            {
                case sf::Event::KeyPressed:
                //Q
                    if(this->evento.key.code == sf::Keyboard::Q && this->heroi.podeAtacar()){
                        this->mousePos = getMouseCoords(*this->janela);
                        this->audios.tiroSom.play();
                        this->tiros.push_back(new Tiro(this->texturas["TIRO"], this->heroi.getCentro(), mousePos, this->heroi.playerStats.velTiroPlayer, 10, false));
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

void Game::limparGame()
{
    //Itera sobre a list tiros para deletar os ponteiros pra Tiro
    for(auto *tiro : this->tiros){
        delete tiro;
        tiro = nullptr;
    }
    this->tiros.clear();

    //Itera sobre a list inimigos para deletar os ponteiros pra Inimigo
    for(auto *inim : this->inimigos){
        delete inim;
        inim = nullptr;
    }
    this->inimigos.clear();

    //Itera sobre a list caixas para deletar os ponteiros pra Caixadrop
    for(auto *caixa : this->caixas){
        delete caixa;
        caixa = nullptr;
    }
    this->caixas.clear();

    this->spawnClock.restart();
    this->levelClock.restart();
}

void Game::proximaFase()
{
    //Salvando o novo score em arquivo
        int score = this->stats.level; //Nivel atual
        int salvo; //Score salvo no arquivo

        std::fstream saveScore("score.txt", std::ios::in | std::ios::out);
        if (!saveScore.is_open())
        {
            std::cerr << "Erro ao abrir\n";
        }

        saveScore >> salvo;

        if (salvo < score)
        {
            saveScore.clear();
            saveScore.seekp(0); //Move o ponteiro de escrita para o inicio
            saveScore << score; //Salva o novo score mais alto
            saveScore.flush();
        }
        
        saveScore.close();

    this->limparGame();
    this->stats.statsNext();
    this->tempo = this->stats.tempoLevel;
    this->up = false;
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
                this->audios.atingidoBaseSom.play();
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
                    this->audios.atingidoInimSom.play();
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

void Game::spawnInimigos()
{
    if (static_cast<double>(rand()) / RAND_MAX < this->stats.inim4chance)
    {
        this->inimigos.push_back(new Inimigo(4, this->texturas["INIMIGO4"], *this->janela));
    }
    else if (static_cast<double>(rand()) / RAND_MAX < this->stats.inim3chance)
    {
        this->inimigos.push_back(new Inimigo(3, this->texturas["INIMIGO3"], *this->janela));
    }
    else if (static_cast<double>(rand()) / RAND_MAX < this->stats.inim2chance)
    {
        this->inimigos.push_back(new Inimigo(2, this->texturas["INIMIGO2"], *this->janela));
    }
    else
    {
        this->inimigos.push_back(new Inimigo(1, this->texturas["INIMIGO1"], *this->janela));
    }

    if (this->stats.level >= 12)
    {
        this->inimigos.push_back(new Inimigo(1, this->texturas["INIMIGO1"], *this->janela));
        this->inimigos.push_back(new Inimigo(2, this->texturas["INIMIGO2"], *this->janela));
    }
    else if (this->stats.level >= 3)
    {
        this->inimigos.push_back(new Inimigo(1, this->texturas["INIMIGO1"], *this->janela));
    }
}

void Game::tratarInimigos()
{
    //Spawnando inimigo
    sf::Time dt = this->spawnClock.getElapsedTime();
    if (dt.asSeconds() >= this->stats.inimSpawnVel)
    {
        if (this->inimigos.size() < this->stats.maxInim)
        {
            this->spawnClock.restart();
            this->spawnInimigos();
        }
    }

    std::list<Inimigo*>::iterator contador = this->inimigos.begin();
    for (auto *inimigo : this->inimigos)
    {
        if (inimigo->getTipo() == 4 || inimigo->getTipo() == 3)
        {
            inimigo->update(this->base.centro, *this->janela);
        }
        else
        {
            inimigo->update(this->heroi.getCentro(), *this->janela);
        }

        //Ataque inimigo
        if (inimigo->atacar())
        {
            if (inimigo->getTipo() == 4)
            {
                this->audios.tiroBaixoSom.play();
                this->tiros.push_back(new Tiro(
                    this->texturas["TIRO"], 
                    inimigo->getCentro(), 
                    this->base.centro, 
                    10, 
                    this->base.stats.escudoBase + 3, //Dano com base no escudo da base
                    true
                ));
            }
            else if (inimigo->getTipo() == 3)
            {
                this->audios.tiroBaixoSom.play();
                this->tiros.push_back(new Tiro(
                    this->texturas["TIRO"], 
                    inimigo->getCentro(), 
                    this->base.centro, 
                    10, 
                    8, 
                    true
                ));
            }
            else
            {
                this->audios.tiroSom.play();
                this->tiros.push_back(new Tiro(this->texturas["TIRO"], inimigo->getCentro(), this->heroi.getCentro(), 10, 5, true));
            }
        }

        //Removendo ao morrer
        if (inimigo->getVida() <= 0)
        {
            //Surgimento randomico das caixas
            if (static_cast<double>(rand()) / RAND_MAX < this->stats.chancesDropMun)
            {
                this->caixas.push_back(new Caixadrop('M', this->texturas["MUNICAO"], inimigo->getCentro()));
            }

            if (static_cast<double>(rand()) / RAND_MAX < this->stats.chancesDropVida)
            {
                this->caixas.push_back(new Caixadrop('V', this->texturas["VIDA"], inimigo->getCentro()));
            }
            
            delete inimigo;
            inimigo = nullptr;
            this->inimigos.erase(contador);
        }
        
        contador++;
    }
}

void Game::tratarCaixas()
{
    std::list<Caixadrop*>::iterator contador = this->caixas.begin();
    for(auto *caixa : this->caixas)
    {
        if (caixa->getBounds().intersects(this->heroi.getBounds()))
        {
            this->audios.coletarSom.play();
            this->heroi.coletarCaixa(caixa->getMunicao(), caixa->getVida());
            delete caixa;
            caixa = nullptr;
            this->caixas.erase(contador);
        }
        contador++;
    }
}

void Game::update(){
    sf::Time dt = this->levelClock.getElapsedTime();
    this->tempo = this->stats.tempoLevel - dt.asSeconds();

    int scoreSalvo; //Score salvo no arquivo
    std::fstream saveScore("score.txt", std::ios::in);

    saveScore >> scoreSalvo;

    if (dt.asSeconds() >= this->stats.tempoLevel)
    {
        this->up = true;
    }

    if (this->base.getVida() <= 0 || this->heroi.playerStats.vidaPlayer <= 0)
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
        else if (this->up)
        {
            //Abrir tela de upgrade
            this->renderUpgrade();
        }
        else
        {
            //Fluxo normal do game
            this->base.update();
            this->heroi.update(*this->janela);
            this->tratarInimigos();
            this->tratarTiros();
            this->tratarCaixas();
            this->GUI.update(
                this->heroi.playerStats.vidaPlayer, 
                this->heroi.playerStats.municaoPlayer, 
                this->stats.level, this->tempo,
                scoreSalvo);
        }
    }
    else
    {
        this->renderOver();
    }
}

void Game::render(){
    //Renderiza os elementos do jogo
    if (!this->paused && !this->over && !this->up)
    {
        this->janela->clear(sf::Color(224, 225, 221, 255));

        this->base.render(*this->janela);
        this->heroi.render(*this->janela);
        
        for(auto *inimigo : this->inimigos){
            inimigo->render(*this->janela);
        }
        for(auto *tiro : this->tiros){
            tiro->render(*this->janela);
        }
        for(auto *caixa : this->caixas){
            caixa->render(*this->janela);
        }

        this->GUI.render(*this->janela);
    }
    this->janela->display();
}
//----------------------------------------//