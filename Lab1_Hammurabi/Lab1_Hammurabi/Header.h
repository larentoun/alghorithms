#pragma once
#include "Helpers.h"
#include <stdbool.h>
#include <iostream>
#include <string>
#include <fstream>

typedef double wheat;
typedef int acre;
typedef int people;
typedef bool plague;
typedef int year;

constexpr int kMaxRounds = 2;
constexpr int kStartingPeople = 100;
constexpr wheat kStartingWheat = 2800;
constexpr acre kStartingAcre = 1000;

struct City {
    people peopleAmount = 100;
    acre acreAmount = 2800;
    wheat wheatAmount = 1000;
    people peopleDiedHungryTotal = 0;
};

struct TurnInfo {
    year year = 0;
    people peopleDiedHungry = 0;
    people peopleArrived = 0;
    wheat wheatCollected = 0;
    wheat wheatDestroyed = 0;
};

struct PlayerTurnInput {
    acre acresToBuy = 0;
    acre acresToSell = 0;
    wheat wheatForPops = -1;
    acre acresToWheat = 0;
};

struct RuleBook {
    wheat wheatPerPop = 20;
    acre acrePerPop = 10;
    wheat wheatPerAcre = 1;
    wheat wheatForAcre = 0.5;
    wheat acreCost = 1;
    plague plagueHappened = false;
    double gameOverPopCoeff = 0.45;
    double plagueChance = 15;
};

City generateNewCity();
void randomizeValuesForRound(RuleBook& ruleBook);
void generateNewTurn(City& city, TurnInfo& lastRound, PlayerTurnInput& playerTurnInput, RuleBook& ruleBook);
void showTurnInfo(TurnInfo& turnInfo, City& city, RuleBook& ruleBook);
PlayerTurnInput playerInput(City& city, RuleBook& ruleBook);
int getIntInput();
void manageAcreChanges(RuleBook& ruleBook, City& city, PlayerTurnInput& playerTurnInput);
void finishGame(City& city);
void loadGame(City& city, TurnInfo& turnInfo, RuleBook& ruleBook);
void saveGame(City& city, TurnInfo& turnInfo, RuleBook& ruleBook);
void shouldContinue();
void startNewGame(City& city, TurnInfo& turnInfo, PlayerTurnInput& playerTurnInput, RuleBook& ruleBook);