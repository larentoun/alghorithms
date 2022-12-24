#pragma once
#include "Helpers.h"
#include <stdbool.h>
#include <iostream>

typedef double wheat;
typedef int acre;
typedef int people;
typedef bool plague;
typedef int year;

struct City {
    people peopleAmount;
    acre acreAmount;
    wheat wheatAmount;
};

struct TurnInfo {
    year year = 0;
    people peopleDiedHungry = 0;
    people peopleArrived = 0;
    plague plagueHappened = false;
    wheat wheatCollected = 0;
    wheat wheatPerAcre = 0;
    wheat wheatDestroyed = 0;
    wheat acreCost = 0;
};

struct PlayerTurnInput {
    acre acresToBuy = 0;
    acre acresToSell = 0;
    wheat wheatForPops = -1;
    wheat wheatForAcres = 0;
};

struct RuleBook {
    wheat wheatPerPop = 20;
    acre acrePerPop = 10;
    wheat wheatPerAcre = 0.5;
    double gameOverPopCoeff = 0.45;
    double plagueChance = 15;
};

City generateNewCity();
TurnInfo generateNewTurn(City& city, TurnInfo& lastTurn, PlayerTurnInput& playerTurnInput);
void showTurnInfo(TurnInfo& turnInfo, City& city);
PlayerTurnInput playerInput(TurnInfo& turnInfo, City& city);