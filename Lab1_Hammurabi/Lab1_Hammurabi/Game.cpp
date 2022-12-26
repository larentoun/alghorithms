#include "Header.h"

City generateNewCity() {
    City newCity;
    newCity.peopleAmount = kStartingPeople;
    newCity.wheatAmount = kStartingWheat;
    newCity.acreAmount = kStartingAcre;
    newCity.peopleDiedHungryTotal = 0;

    std::cout << std::endl << "Мой повелитель, соизволь поведать тебе" << std::endl;
    std::cout << "Население города сейчас составляет " << newCity.peopleAmount << " человек;" << std::endl;
    std::cout << "Город сейчас занимает " << newCity.acreAmount << " акров;" << std::endl;
    std::cout << "В амбарах имеется " << newCity.wheatAmount << " бушелей пшеницы." << std::endl;
    return newCity;
}

void randomizeValuesForRound(RuleBook& ruleBook) {
    ruleBook.acreCost = random(17, 26);
    ruleBook.wheatPerAcre = random(1, 6);

    double plagueProc = random(1, 100);
    if (plagueProc <= ruleBook.plagueChance) {
        ruleBook.plagueHappened = true;
    }
    else {
        ruleBook.plagueHappened = false;
    }
}

void generateNewTurn(City& city, TurnInfo& turnInfo, PlayerTurnInput& playerTurnInput, RuleBook& ruleBook) {
    turnInfo.year += 1;

    //Wheat collected from acres
    acre wheatedAcres = std::clamp(playerTurnInput.acresToWheat, 0, city.acreAmount);
    acre workableAcres = std::clamp(city.peopleAmount * ruleBook.acrePerPop, 0, wheatedAcres);
    turnInfo.wheatCollected = workableAcres * ruleBook.wheatPerAcre;

    //Managing wheat
    city.wheatAmount += turnInfo.wheatCollected;
    wheat wheatDestroyedMax = floor(0.07 * city.wheatAmount);
    wheat wheatDestoyedMin = 0.0;
    turnInfo.wheatDestroyed = random(wheatDestoyedMin, wheatDestroyedMax);
    city.wheatAmount -= turnInfo.wheatDestroyed;

    //Managing people
    turnInfo.peopleArrived = 0;
    turnInfo.peopleDiedHungry = 0;
    int peopleBeforeCalc = city.peopleAmount;
    for (int counter = 0; counter < peopleBeforeCalc; counter++) {
        if (playerTurnInput.wheatForPops >= ruleBook.wheatPerPop) {
            playerTurnInput.wheatForPops -= ruleBook.wheatPerPop;
            city.wheatAmount -= ruleBook.wheatPerPop;
        }
        else {
            city.peopleAmount -= 1;
            city.peopleDiedHungryTotal += 1;
            turnInfo.peopleDiedHungry += 1;
        }
    }
    if (1 - (double)city.peopleAmount / (double)peopleBeforeCalc > ruleBook.gameOverPopCoeff) {
        std::cout << "Погибло слишком много людей из-за голода. Вы были свергнуты!";
        std::remove("saveFile.dat");
        std::exit(EXIT_SUCCESS);
    }
    turnInfo.peopleArrived = (people)floor(std::clamp(turnInfo.peopleDiedHungry / 2.0 + (5.0 - ruleBook.wheatPerAcre) * city.wheatAmount / 600.0 + 1.0, 0.0, 50.0));
    city.peopleAmount += turnInfo.peopleArrived;
    if (ruleBook.plagueHappened) {
        city.peopleAmount /= 2;
    }
}

void showTurnInfo(TurnInfo& turnInfo, City& city, RuleBook& ruleBook) {
    //Round information
    std::cout << std::endl << "Мой повелитель, соизволь поведать тебе" << std::endl;
    std::cout << "в году " << turnInfo.year << " твоего высочайшего правления" << std::endl;
    std::cout << turnInfo.peopleDiedHungry << " человек умерли с голоду, и " << std::endl;
    std::cout << turnInfo.peopleArrived << " человек прибыли в наш великий город;" << std::endl;

    if (ruleBook.plagueHappened)
    {
        std::cout << "Чума уничтожила половину населения;" << std::endl;
    }
    std::cout << "Население города сейчас составляет " << city.peopleAmount << " человек;" << std::endl;
    std::cout << "Мы собрали " << turnInfo.wheatCollected << " бушелей пшеницы, по ";
    std::cout << ruleBook.wheatPerAcre << " бушеля с акра;" << std::endl;
    std::cout << "Крысы истребили " << turnInfo.wheatDestroyed << " бушелей пшеницы, оставив ";
    std::cout << city.wheatAmount << " бушеля в амбарах" << std::endl;
    std::cout << "Город сейчас занимает " << city.acreAmount << " акров;" << std::endl;
    std::cout << "1 акр земли стоит сейчас " << ruleBook.acreCost << " бушель." << std::endl;
}

void manageAcreChanges(RuleBook& ruleBook, City& city, PlayerTurnInput& playerTurnInput) {
    city.acreAmount += playerTurnInput.acresToBuy - playerTurnInput.acresToSell;
    city.wheatAmount += (playerTurnInput.acresToBuy - playerTurnInput.acresToSell) * ruleBook.acreCost;
}

PlayerTurnInput playerInput(City& city, RuleBook& ruleBook) {
    bool invalidInput = false;
    acre acresToBuy;
    acre acresToSell;
    wheat wheatForPops;
    acre acresToWheat;
    while (true) {
        invalidInput = false;
        std::cout << "Что пожелаешь, повелитель?" << std::endl;
        std::cout << "Сколько акров земли повелеваешь купить? ";
        acresToBuy = getIntInput();
        std::cout << "Сколько акров земли повелеваешь продать? ";
        acresToSell = getIntInput();
        std::cout << "Сколько бушелей пшеницы повелеваешь съесть? ";
        wheatForPops = getIntInput();
        std::cout << "Сколько акров земли повелеваешь засеять? ";
        acresToWheat = getIntInput();
        wheat requstedWheat = (acresToBuy - acresToSell) * ruleBook.wheatPerAcre + wheatForPops + acresToWheat * ruleBook.wheatForAcre;
        if (acresToSell - acresToBuy > city.acreAmount || requstedWheat > city.wheatAmount) {
            std::cout << "О, повелитель, пощади нас! У нас только" << city.peopleAmount << " человек, " << city.wheatAmount << " бушелей пшеницы и " << city.acreAmount << " акров земли!" << std::endl;
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
    playerTurnInput.acresToWheat = acresToWheat;
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

void finishGame(City& city) {
    std::remove("saveFile.dat");

    double P = (double)city.peopleDiedHungryTotal / kMaxRounds;
    int L = floor((double)city.acreAmount / (double)city.peopleAmount);
    std::cout << "Счет:" << std::endl;
    std::cout << "Среднегодовой процент умерших от голода: " << P * 100 << "%" << std::endl;
    std::cout << "Количество акров земли на одного жителя: " << L << std::endl;

    if (P > 0.33 && L < 7) {
        std::cout << "Оценка: ПЛОХО!" << std::endl;
        std::cout << "Из-за вашей некомпетентности в  управлении, народ устроил бунт, и изгнал вас их города.Теперь вы вынуждены влачить жалкое существование в изгнании" << std::endl;
        return;
    }
    if (P > 0.10 && L < 9) {
        std::cout << "Оценка: Удовлетворительно!" << std::endl;
        std::cout << "Вы правили железной  рукой, подобно Нерону и Ивану Грозному.Народ вздохнул с облегчением, и никто больше не желает видеть вас правителем" << std::endl;
        return;
    }
    if (P > 0.33 && L < 7) {
        std::cout << "Оценка: Хорошо!" << std::endl;
        std::cout << "Вы справились вполне неплохо, у вас, конечно, есть недоброжелатели, но многие хотели бы увидеть вас во главе города снова" << std::endl;
        return;
    }
    std::cout << "Оценка: ОТЛИЧНО!" << std::endl;
    std::cout << "Фантастика! Карл Великий, Дизраэли и Джефферсон вместе не справились бы лучше" << std::endl;
}

void shouldContinue() {
    std::cout << "Хотите продолжить? 1/0" << std::endl;
    int input;
    while (true)
    {
        input = getIntInput();
        if (input == 1) {
            return;
        }
        if (input == 0) {
            exit(EXIT_SUCCESS);
        }
    }
}

void startNewGame(City& city, TurnInfo& turnInfo, PlayerTurnInput& playerTurnInput, RuleBook& ruleBook) {
    std::cout << "[DEBUG]: New game started!" << std::endl;
    city = generateNewCity();
    turnInfo.year = 0;
    randomizeValuesForRound(ruleBook);
    playerTurnInput = playerInput(city, ruleBook);
    manageAcreChanges(ruleBook, city, playerTurnInput);
}

void loadGame(City& city, TurnInfo& turnInfo, RuleBook& ruleBook) {
    std::ifstream saveFile;
    saveFile.open("saveFile.dat");
    saveFile >> city.acreAmount;
    saveFile >> city.peopleAmount;
    saveFile >> city.peopleDiedHungryTotal;
    saveFile >> city.wheatAmount;
    saveFile >> turnInfo.peopleArrived;
    saveFile >> turnInfo.peopleDiedHungry;
    saveFile >> turnInfo.wheatCollected;
    saveFile >> turnInfo.wheatDestroyed;
    saveFile >> turnInfo.year;
    saveFile >> ruleBook.acreCost;
    saveFile >> ruleBook.acrePerPop;
    saveFile >> ruleBook.gameOverPopCoeff;
    saveFile >> ruleBook.plagueChance;
    saveFile >> ruleBook.plagueHappened;
    saveFile >> ruleBook.wheatForAcre;
    saveFile >> ruleBook.wheatPerAcre;
    saveFile >> ruleBook.wheatPerPop;
    saveFile.close();
}
void saveGame(City& city, TurnInfo& turnInfo, RuleBook& ruleBook) {
    std::ofstream saveFile;
    saveFile.open("saveFile.dat");
    saveFile << city.acreAmount << std::endl;
    saveFile << city.peopleAmount << std::endl;
    saveFile << city.peopleDiedHungryTotal << std::endl;
    saveFile << city.wheatAmount << std::endl;
    saveFile << turnInfo.peopleArrived << std::endl;
    saveFile << turnInfo.peopleDiedHungry << std::endl;
    saveFile << turnInfo.wheatCollected << std::endl;
    saveFile << turnInfo.wheatDestroyed << std::endl;
    saveFile << turnInfo.year << std::endl;
    saveFile << ruleBook.acreCost << std::endl;
    saveFile << ruleBook.acrePerPop << std::endl;
    saveFile << ruleBook.gameOverPopCoeff << std::endl;
    saveFile << ruleBook.plagueChance << std::endl;
    saveFile << ruleBook.plagueHappened << std::endl;
    saveFile << ruleBook.wheatForAcre << std::endl;
    saveFile << ruleBook.wheatPerAcre << std::endl;
    saveFile << ruleBook.wheatPerPop << std::endl;
    saveFile.close();
}