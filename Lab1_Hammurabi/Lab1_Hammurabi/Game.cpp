#include "Header.h"

constexpr int kStartingPeople = 100;
constexpr wheat kStartingWheat = 2800;
constexpr acre kStartingAcre = 1000;

City generateNewCity() {
    City newCity;
    newCity.peopleAmount = kStartingPeople;
    newCity.wheatAmount = kStartingWheat;
    newCity.acreAmount = kStartingAcre;
    std::cout << "We curently have:" << std::endl;
    std::cout << "People in the city:" << newCity.peopleAmount << std::endl;
    std::cout << "Wheat available: " << newCity.wheatAmount << std::endl;
    std::cout << "Acres available: " << newCity.acreAmount << std::endl;
    return newCity;
}

TurnInfo generateNewTurn(City& city, TurnInfo& lastRound, PlayerTurnInput& playerTurnInput, RuleBook& ruleBook) {
    TurnInfo turnInfo;
    turnInfo.year = lastRound.year + 1;
    //Generating new values
    turnInfo.acreCost = random(17, 26);
    ruleBook.wheatPerAcre = random(1, 6);
    turnInfo.wheatCollected = std::clamp(ruleBook.wheatPerAcre * city.acreAmount, 0.0, city.peopleAmount * ruleBook.wheatPerAcre);
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
        if (playerTurnInput.wheatForPops >= ruleBook.wheatPerPop) {
            std::cout << playerTurnInput.wheatForPops << std::endl;
            playerTurnInput.wheatForPops -= ruleBook.wheatPerPop;
        }
        else {
            city.peopleAmount -= 1;
            turnInfo.peopleDiedHungry += 1;
        }
    }
    if (1 - city.peopleAmount / peopleBeforeCalc > ruleBook.gameOverPopCoeff) {
        std::cout << "Too many people died. Game Over";
        std::exit(EXIT_SUCCESS);
    }
    turnInfo.peopleArrived = (people)floor(std::clamp(turnInfo.peopleDiedHungry / 2 + (5 - ruleBook.wheatPerAcre) * city.wheatAmount / 600 + 1, 0.0, 50.0));
    city.peopleAmount += turnInfo.peopleArrived;
    if (turnInfo.plagueHappened) {
        city.peopleAmount /= 2;
    }
    return turnInfo;
}

void showTurnInfo(TurnInfo& turnInfo, City& city, RuleBook& ruleBook) {
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
    std::cout << "Wheat collected from each Acre: " << ruleBook.wheatPerAcre << "\n";
    std::cout << "Wheat eaten by rats: " << turnInfo.wheatDestroyed << "\n";
    std::cout << "Acres in the city: " << city.acreAmount << "\n";
    std::cout << "Acre cost today (in wheat): " << turnInfo.acreCost << "\n";
}

PlayerTurnInput playerInput(City& city, RuleBook& ruleBook) {
    bool invalidInput = false;
    acre acresToBuy;
    acre acresToSell;
    wheat wheatForPops;
    wheat wheatForAcres;
    while (true) {
        invalidInput = false;
        std::cout << "How much Acre do you want to buy: ";
        acresToBuy = getIntInput();
        std::cout << "How much Acre do you want to sell: ";
        acresToSell = getIntInput();
        std::cout << "How much wheat to use for feeding your people: ";
        wheatForPops = getIntInput();
        std::cout << "How much wheat to use for seeding acres: ";
        wheatForAcres = getIntInput();
        wheat requstedWheat = (acresToBuy - acresToSell) * ruleBook.wheatPerAcre + wheatForPops + wheatForAcres;
        if (requstedWheat > city.wheatAmount) {
            std::cout << "You want to use " << requstedWheat << " amount of wheat, but you don't have enough!\n" << city.wheatAmount;
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

int getIntInput() {
    std::string input = "";
    int output = -1;
    while (output < 0) {
        std::cin >> input;
        try {
            output = std::stoi(input);
        }
        catch (std::invalid_argument const& ex) {
            std::cout << "You need to enter a number!" << std::endl;
        }
        catch (std::out_of_range const& ex) {
            std::cout << "This value is out of bounds!" << std::endl;
        }
        if (output < 0) {
            std::cout << "You need to enter a positive number!" << std::endl;
        }
    }
    return output;
}