#include "GameLevelStats.hpp"
#include <iostream>

void GameLevelStats::statsNext()
{
    /*
        Atualiza os status da fase ao passar de nivel
    */
    this->level++;
    this->tempoLevel += 3; //Aumenta o tempo para sobreviver a fase

    //Aumenta a velocidade de surgimento de inimigos (maxima de 0.5s)
    if (this->inimSpawnVel > 0.5)
    {
        this->inimSpawnVel -= 0.25; //Reduz o tempo para surgir inimigos
    }
    
    if (this->level < 14)
    {
        this->maxInim++; //Aumenta a quantidade maxima de inimigos
    }    

    //Diminui as chances de caixas (minimo de 6%)
    if (this->chancesDropMun > 0.06)
    {
       this->chancesDropMun -= 0.04;  
    }
    if (this->chancesDropVida > 0.06)
    {
        this->chancesDropVida -= 0.04;
    }

    //Abilita outros inimigos ao passar de fases
    if (this->level == 3)
    {
        this->inim2chance += 0.30;
    }
    if (this->level == 6)
    {
        this->inim3chance += 0.20;
    }
    if (this->level == 9)
    {
        this->inim4chance += 0.10;
    }
}

void GameLevelStats::statsReset()
{
    this->level = 1;
    this->tempoLevel = 15;

    this->inimSpawnVel = 4;
    this->maxInim = 5;
    this->inim2chance = 0;
    this->inim3chance = 0;
    this->inim4chance = 0;

    this->chancesDropMun = 0.46;
    this->chancesDropVida = 0.36;
}

void PlayerLevelStats::statsUpgradeVida()
{
    int vidaUp = this->vidaMaxima + 10;
    this->vidaLevel++;
    this->vidaMaxima = vidaUp;
    this->vidaPlayer = vidaMaxima;
}

void PlayerLevelStats::statsUpgradeVelocidade()
{
    float velUp = this->velocidadePlayer + 1;
    this->velLevel++;
    this->velocidadePlayer = velUp;
}

void PlayerLevelStats::statsUpgradeCadencia()
{
    if (this->cadLevel < this->cadMaxLevel)
    {
        float cadUp = this->cadenciaAtaquePlayer - 0.25;
        this->cadenciaAtaquePlayer = cadUp;   
        this->municaoPlayer += 25;
        this->cadLevel++;
    }
    std::cout << this->cadenciaAtaquePlayer << "\n";
}

void PlayerLevelStats::statsUpgradeVelT()
{
    float velTUp = this->velTiroPlayer + 5;
    this->velTLevel++;
    this->velTiroPlayer = velTUp;
}

void PlayerLevelStats::statsReset()
{
    this->vidaLevel = 1;
    this->velLevel = 1;
    this->cadLevel = 1;
    this->velTLevel = 1;

    this->vidaPlayer = 100;
    this->vidaMaxima = 100;
    this->municaoPlayer = 25;
    this->velocidadePlayer = 4;
    this->cadenciaAtaquePlayer = 1;
    this->velTiroPlayer = 10;
}

void BaseLevelStats::statsUpgradeVel()
{
    if (this->velLevel < this->maxVelLevel)
    {
        float velUp = this->velCuraBase - 0.2;
        this->velCuraBase = velUp;
        this->velLevel++;
    }    
    std::cout << this->velCuraBase << "\n";
}

void BaseLevelStats::statsUpgradeCura()
{
    if (this->curaLevel < this->maxCuraLevel)
    {
        int curaUp = this->autoCuraBase + 3;
        this->autoCuraBase = curaUp;
        this->curaLevel++;
    }
    std::cout << this->autoCuraBase << "\n";
}

void BaseLevelStats::statsUpgradeEscudo()
{
    if (this->escudoLevel < this->maxEscudoLevel)
    {
        int escUp = this->escudoBase + 1;
        this->escudoBase = escUp;
        this->escudoLevel++;
    }   
    std::cout << this->escudoBase << "\n";
}

void BaseLevelStats::statsReset()
{   
    this->velLevel = 1;
    this->curaLevel = 1;
    this->escudoLevel = 1;

    this->velCuraBase = 1;
    this->autoCuraBase = 2;
    this->escudoBase = 0;
}
