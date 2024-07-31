#ifndef LEVELSTATS_HPP
#define LEVELSTATS_HPP

struct GameLevelStats
{
    //Fase
    unsigned level = 1;
    float inimSpawnVel = 4; //tempo em segundos para surgir inimigos
    int maxInim = 5;
    float chancesDropMun = 0.36; //chance de inimigos deixarem munições no jogo
    float chancesDropVida = 0.2; //chance de inimigos deixarem curas no jogo

    void statsNext();
    void statsReset();
};

struct PlayerLevelStats
{
    unsigned vidaLevel = 1;
    unsigned velLevel = 1;
    unsigned cadLevel = 1;

    int vidaPlayer = 100;
    int municaoPlayer = 25;
    float velocidadePlayer = 4;
    float cadenciaAtaquePlayer = 1; //Tempo entre um ataque e outro em segundos
    
    int statsUpgradeVida();
    void statsReset();
};

struct BaseLevelStats
{
    unsigned velLevel = 1;
    unsigned curaLevel = 1;
    unsigned resistLevel = 1;

    int velCuraBase = 1; //Tempo em segundos entre as curas automaticas da base
    int autoCuraBase = 2; //Quantidade de vida que a base recupera a cada cura automatica
    int resistenciaBase = 0; //Reduz o dano sofrido pela base
    
    void statsUpgrade();
    void statsReset();
};

#endif