#include "GameLevelStats.hpp"
#include <iostream>

void GameLevelStats::statsNext()
{
    this->level++;
    this->inimSpawnVel -= 0.2; //Reduz o tempo para surgir inimigos
    this->maxInim++; //Aumenta a quantidade maxima de inimigos

    //Diminui as chances de caixas (minimo de 5%)
    if (this->chancesDropMun > 0.05)
    {
       this->chancesDropMun -= 0.02;  
    }
    if (this->chancesDropVida > 0.05)
    {
        this->chancesDropVida += 0.02;
    }
}

void GameLevelStats::statsReset()
{
    this->level = 1;
    this->inimSpawnVel = 4;
    this->maxInim = 5;
    this->chancesDropMun = 0.36;
    this->chancesDropVida = 0.2;
}

int PlayerLevelStats::statsUpgradeVida()
{
    int novaVida = 100 + (10 * this->vidaLevel);
    this->vidaLevel++;
    return novaVida;
}

void PlayerLevelStats::statsReset()
{
    this->vidaLevel = 1;
    this->velLevel = 1;
    this->cadLevel = 1;

    this->vidaPlayer = 100;
    this->municaoPlayer = 25;
    this->velocidadePlayer = 4;
    this->cadenciaAtaquePlayer = 1;
}

void BaseLevelStats::statsReset()
{   
    this->velLevel = 1;
    this->curaLevel = 1;
    this->resistLevel = 1;

    this->velCuraBase = 1;
    this->autoCuraBase = 2;
    this->resistenciaBase = 0;
}
