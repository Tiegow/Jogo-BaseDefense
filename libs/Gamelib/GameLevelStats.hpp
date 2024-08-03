#ifndef LEVELSTATS_HPP
#define LEVELSTATS_HPP

struct GameLevelStats
{
    //Fase
    unsigned level = 1;
    float tempoLevel = 15; //tempo em segundos para passar de nivel

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

struct PlayerLevelStats
{
    unsigned vidaLevel = 1;
    unsigned velLevel = 1;
    unsigned cadLevel = 1;
    unsigned cadMaxLevel = 5;
    unsigned velTLevel = 1;

    int vidaPlayer = 100;
    int vidaMaxima = 100;
    int municaoPlayer = 25;
    float velocidadePlayer = 4;
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
    unsigned maxVelLevel = 5;
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