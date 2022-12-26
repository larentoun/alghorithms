#include "Header.h"

City generateNewCity() {
    City newCity;
    newCity.peopleAmount = kStartingPeople;
    newCity.wheatAmount = kStartingWheat;
    newCity.acreAmount = kStartingAcre;
    newCity.peopleDiedHungryTotal = 0;

    std::cout << std::endl << "��� ����������, �������� �������� ����" << std::endl;
    std::cout << "��������� ������ ������ ���������� " << newCity.peopleAmount << " �������;" << std::endl;
    std::cout << "����� ������ �������� " << newCity.acreAmount << " �����;" << std::endl;
    std::cout << "� ������� ������� " << newCity.wheatAmount << " ������� �������." << std::endl;
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
        std::cout << "������� ������� ����� ����� ��-�� ������. �� ���� ���������!";
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
    std::cout << std::endl << "��� ����������, �������� �������� ����" << std::endl;
    std::cout << "� ���� " << turnInfo.year << " ������ ����������� ���������" << std::endl;
    std::cout << turnInfo.peopleDiedHungry << " ������� ������ � ������, � " << std::endl;
    std::cout << turnInfo.peopleArrived << " ������� ������� � ��� ������� �����;" << std::endl;

    if (ruleBook.plagueHappened)
    {
        std::cout << "���� ���������� �������� ���������;" << std::endl;
    }
    std::cout << "��������� ������ ������ ���������� " << city.peopleAmount << " �������;" << std::endl;
    std::cout << "�� ������� " << turnInfo.wheatCollected << " ������� �������, �� ";
    std::cout << ruleBook.wheatPerAcre << " ������ � ����;" << std::endl;
    std::cout << "����� ��������� " << turnInfo.wheatDestroyed << " ������� �������, ������� ";
    std::cout << city.wheatAmount << " ������ � �������" << std::endl;
    std::cout << "����� ������ �������� " << city.acreAmount << " �����;" << std::endl;
    std::cout << "1 ��� ����� ����� ������ " << ruleBook.acreCost << " ������." << std::endl;
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
        std::cout << "��� ���������, ����������?" << std::endl;
        std::cout << "������� ����� ����� ����������� ������? ";
        acresToBuy = getIntInput();
        std::cout << "������� ����� ����� ����������� �������? ";
        acresToSell = getIntInput();
        std::cout << "������� ������� ������� ����������� ������? ";
        wheatForPops = getIntInput();
        std::cout << "������� ����� ����� ����������� �������? ";
        acresToWheat = getIntInput();
        wheat requstedWheat = (acresToBuy - acresToSell) * ruleBook.wheatPerAcre + wheatForPops + acresToWheat * ruleBook.wheatForAcre;
        if (acresToSell - acresToBuy > city.acreAmount || requstedWheat > city.wheatAmount) {
            std::cout << "�, ����������, ������ ���! � ��� ������" << city.peopleAmount << " �������, " << city.wheatAmount << " ������� ������� � " << city.acreAmount << " ����� �����!" << std::endl;
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
    std::cout << "����:" << std::endl;
    std::cout << "������������� ������� ������� �� ������: " << P * 100 << "%" << std::endl;
    std::cout << "���������� ����� ����� �� ������ ������: " << L << std::endl;

    if (P > 0.33 && L < 7) {
        std::cout << "������: �����!" << std::endl;
        std::cout << "��-�� ����� ���������������� �  ����������, ����� ������� ����, � ������ ��� �� ������.������ �� ��������� ������� ������ ������������� � ��������" << std::endl;
        return;
    }
    if (P > 0.10 && L < 9) {
        std::cout << "������: �����������������!" << std::endl;
        std::cout << "�� ������� ��������  �����, ������� ������ � ����� ��������.����� �������� � �����������, � ����� ������ �� ������ ������ ��� ����������" << std::endl;
        return;
    }
    if (P > 0.33 && L < 7) {
        std::cout << "������: ������!" << std::endl;
        std::cout << "�� ���������� ������ �������, � ���, �������, ���� ���������������, �� ������ ������ �� ������� ��� �� ����� ������ �����" << std::endl;
        return;
    }
    std::cout << "������: �������!" << std::endl;
    std::cout << "����������! ���� �������, �������� � ���������� ������ �� ���������� �� �����" << std::endl;
}

void shouldContinue() {
    std::cout << "������ ����������? 1/0" << std::endl;
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