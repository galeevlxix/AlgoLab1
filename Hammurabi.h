#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include <algorithm>
#include <string>
#include <ctime>
#include "math.h"

#include "Structures.h"
#include "FileIO.h"

using namespace std;

class Hammurabi
{
public:
	Hammurabi();
	void BeginGameplayLoop();

private:
    Villagers villagers;
    Bushels bushels;
    Acres acres;

    bool gameOver;
    bool gameStarted; //для проверки
    int round;

    string gamestateFile = "..\\AlgoLab1\\GameState.txt";
    string constFile = "..\\AlgoLab1\\Const.txt";

    void GetReport();
    void InputParameters();
    bool CheckInputParameters();
    void OnGameOver();

    void VillagersHungerMortality();
    void VillagersPlagueMortality();
    void VillagersGrowth();

    void BushelsHarvest();
    void BusehlsDestructionByRats();

    void BuyAcres();
    void SellAcres();
    void SowAcres();
};

