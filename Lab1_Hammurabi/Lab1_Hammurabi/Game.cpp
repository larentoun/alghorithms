#include "Header.h"

City generateNewCity() {
    City newCity;
    newCity.peopleAmount = 100;
    newCity.wheatAmount = 2800;
    newCity.acreAmount = 1000;
    return newCity;
}

TurnInfo generateNewTurn(City& city, TurnInfo& lastTurn, PlayerTurnInput& playerTurnInput) {
    TurnInfo turnInfo;
    RuleBook ruleBook;
    //Generating new values
    turnInfo.acreCost = random(17, 26);
    turnInfo.wheatPerAcre = random(1, 6);
    turnInfo.wheatCollected = std::clamp(turnInfo.wheatPerAcre * city.acreAmount, 0.0, city.peopleAmount * ruleBook.wheatPerAcre);
    double plagueProc = random(1, 100);
    if (plagueProc <= ruleBook.plagueChance) {
        turnInfo.plagueHappened = true;
    }

    //Managing wheat
    city.wheatAmount += turnInfo.wheatCollected;
    wheat wheatDestroyedMax = floor(0.07 * city.wheatAmount);
    wheat wheatDestoyedMin = 0.0;
    turnInfo.wheatDestroyed = random(wheatDestoyedMin, wheatDestroyedMax);
    city.wheatAmount -= turnInfo.wheatDestroyed;

    //Managing people
    int peopleBeforeCalc = city.peopleAmount;
    for (int counter = 0; counter < peopleBeforeCalc; counter++) {
        if (city.wheatAmount >= ruleBook.wheatPerPop) {
            city.wheatAmount -= ruleBook.wheatPerPop;
        }
        else {
            city.peopleAmount -= 1;
            turnInfo.peopleDiedHungry += 1;
        }
    }
    if (city.peopleAmount / peopleBeforeCalc <= 1 - ruleBook.gameOverPopCoeff) {
        std::cout << "Too many people died. Game Over";
        std::exit(EXIT_SUCCESS);
    }
    turnInfo.peopleArrived = (people)floor(std::clamp(turnInfo.peopleDiedHungry / 2 + (5 - turnInfo.wheatPerAcre) * city.wheatAmount / 600 + 1, 0.0, 50.0));
    city.peopleAmount += turnInfo.peopleArrived;
    if (turnInfo.plagueHappened) {
        city.peopleAmount /= 2;
    }
    return turnInfo;
}

void showTurnInfo(TurnInfo& turnInfo, City& city) {
    //Round information
    std::cout << "Round number: " << turnInfo.year << "\n";
    if (turnInfo.peopleDiedHungry) {
        std::cout << "People died from hunger: " << turnInfo.peopleDiedHungry << "\n";
    }
    if (turnInfo.peopleArrived) {
        std::cout << "People arrived to the city: " << turnInfo.peopleArrived << "\n";
    }
    if (turnInfo.plagueHappened)
    {
        std::cout << "The plague was in place!\n";
    }
    std::cout << "Stats: \n";
    std::cout << "People in the city: " << city.peopleAmount << "\n";
    std::cout << "Wheat collected: " << turnInfo.wheatCollected << "\n";
    std::cout << "Wheat collected from each Acre: " << turnInfo.wheatPerAcre << "\n";
    std::cout << "Wheat eaten by rats: " << turnInfo.wheatDestroyed << "\n";
    std::cout << "Acres in the city: " << city.acreAmount << "\n";
    std::cout << "Acre cost today (in wheat): " << turnInfo.acreCost << "\n";
}

PlayerTurnInput playerInput(TurnInfo& turnInfo, City& city) {
    bool invalidInput = false;
    acre acresToBuy;
    acre acresToSell;
    wheat wheatForPops;
    wheat wheatForAcres;
    showTurnInfo(turnInfo, city);
    while (true) {
        invalidInput = false;
        std::cout << "How much Acre do you want to buy: ";
        std::cin >> acresToBuy;
        std::cout << "How much Acre do you want to sell: ";
        std::cin >> acresToSell;
        std::cout << "How much wheat to use for feeding your people: ";
        std::cin >> wheatForPops;
        std::cout << "How much wheat to use for seeding acres: ";
        std::cin >> wheatForAcres;
        if (acresToBuy < 0 || acresToSell < 0 || wheatForPops < 0 || wheatForAcres < 0) {
            std::cout << "Invalid number detected.\n";
            invalidInput = true;
        }
        wheat requstedWheat = (acresToBuy - acresToSell) * turnInfo.wheatPerAcre + wheatForPops + wheatForAcres;
        if (requstedWheat > city.wheatAmount) {
            std::cout << "You want to use " << requstedWheat << " amount of wheat, but you don't have enough!\n";
            invalidInput = true;
        }
        if (!invalidInput) {
            break;
        }
        std::cout << std::endl;
    }
    PlayerTurnInput playerTurnInput;
    playerTurnInput.acresToBuy = acresToBuy;
    playerTurnInput.acresToSell = acresToSell;
    playerTurnInput.wheatForPops = wheatForPops;
    playerTurnInput.wheatForAcres = wheatForAcres;
    return playerTurnInput;
}