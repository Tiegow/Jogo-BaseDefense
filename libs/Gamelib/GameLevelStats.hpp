#ifndef LEVELSTATS_HPP
#define LEVELSTATS_HPP

#include <SFML/Audio.hpp>

struct GameLevelStats
{
    //Fase
    unsigned level = 1;
    float tempoLevel = 12; //tempo em segundos para passar de nivel

    float inimSpawnVel = 4; //tempo em segundos para surgir inimigos
    int maxInim = 5;
    float inim2chance = 0;
    float inim3chance = 0;
    float inim4chance = 0;

    float chancesDropMun = 0.46; //chance de inimigos deixarem munições no jogo
    float chancesDropVida = 0.36; //chance de inimigos deixarem curas no jogo

    void statsNext();
    void statsReset();
};

struct GameLevelAudios
{
    sf::SoundBuffer bufferT1;
    sf::Sound tiroBaixoSom;

    sf::SoundBuffer bufferT2;
    sf::Sound tiroSom;

    sf::SoundBuffer bufferAtbase;
    sf::Sound atingidoBaseSom;

    sf::SoundBuffer bufferAtinim;
    sf::Sound atingidoInimSom;

    sf::SoundBuffer bufferUpgrade;
    sf::Sound upgradeSom;

    sf::SoundBuffer bufferColetar;
    sf::Sound coletarSom;
    
    sf::Music musica1;
};

struct PlayerLevelStats
{
    unsigned vidaLevel = 1;
    unsigned velLevel = 1;
    unsigned cadLevel = 1;
    unsigned cadMaxLevel = 5;
    unsigned velTLevel = 1; //Nivel da velocidade do projétil

    int vidaPlayer = 100;
    int vidaMaxima = 100;
    int municaoPlayer = 25;
    float velocidadePlayer = 4.5;
    float cadenciaAtaquePlayer = 1; //Tempo entre um ataque e outro em segundos
    float velTiroPlayer = 10; //Velocidade do projétil
    
    void statsUpgradeVida();
    void statsUpgradeVelocidade();
    void statsUpgradeCadencia();
    void statsUpgradeVelT();
    void statsReset();
};

struct BaseLevelStats
{
    //Base
    unsigned velLevel = 1;
    unsigned maxVelLevel = 4;
    unsigned curaLevel = 1;
    unsigned maxCuraLevel = 5;
    unsigned escudoLevel = 1;
    unsigned maxEscudoLevel = 5;

    float velCuraBase = 1; //Tempo em segundos entre as curas automaticas da base
    int autoCuraBase = 2; //Quantidade de vida que a base recupera a cada cura automatica
    int escudoBase = 0; //Reduz o dano sofrido pela base
    
    void statsUpgradeVel();
    void statsUpgradeCura();
    void statsUpgradeEscudo();
    void statsReset();
};

#endif