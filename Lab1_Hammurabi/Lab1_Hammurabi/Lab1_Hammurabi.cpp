#include "Header.h"

/*
        Описание игры
Количество раундов - 10
Игрок распоряжается ресурсами города
Ресурсы:
- Население
- Акр земли
- Бушели пшеницы
Каждый раунд - один год правления
Каждый гражданин возделывает некоторое количество акр земли
Акры земли производят некоторое количество бушелей пшеницы
Пшеница используется либо для еды, либо для семян в следующий год
Акры земли могут быть куплены и проданы за пшеницу

        Процесс игры
Каждый раунд начинается со статуса текущих дел в городе, состоит из:
- Сбор пшеницы за прошлый раунд
- Акры земли города
- Изменения населения

Игрок может:
- Купить или продать землю
- Использовать пшеницу для семян
- Использовать пшеницу для еды
(Все в интегерах)

        Ключевая информация
Игра скрывает от игрока некоторую важную информацию, такие как правила и коэффициенты расчета параметров за раунд
Используется RNG в начале раунда для:
- Цена земли
- Количество пшеницы с земли
- Количество пшеницы, съеденной крысами
- Количество населения, прибывших в город
- Ивент чумы, который делит пополам население.

Игра заканчивается через 10 раундов, когда город вымрет, или если более 45% населения умрут от голода в течении одного раунда.
*/

int main() {
    setlocale(LC_ALL, "");

    City city;
    TurnInfo turnInfo;
    RuleBook ruleBook;
    PlayerTurnInput playerTurnInput;
    bool loadedFile = false;
    std::ifstream saveFile;
    saveFile.open("saveFile.dat");
    while (true) {
        if (saveFile) {
            saveFile.close();
            std::cout << "Была найдена игра, продолжить? 1/0" << std::endl;
            int input;
            while (true)
            {
                input = getIntInput();
                if (input == 1) {
                    loadGame(city, turnInfo, ruleBook);
                    loadedFile = true;
                    break;
                }
                if (input == 0) {
                    startNewGame(city, turnInfo, playerTurnInput, ruleBook);
                    std::remove("saveFile.dat");
                    break;
                }
            }
        }
        else {
            startNewGame(city, turnInfo, playerTurnInput, ruleBook);
        }
        if (loadedFile) {
            showTurnInfo(turnInfo, city, ruleBook);
            playerTurnInput = playerInput(city, ruleBook);
            manageAcreChanges(ruleBook, city, playerTurnInput);
        }
        while (turnInfo.year < kMaxRounds) {
            randomizeValuesForRound(ruleBook);
            generateNewTurn(city, turnInfo, playerTurnInput, ruleBook);
            saveGame(city, turnInfo, ruleBook);
            showTurnInfo(turnInfo, city, ruleBook);
            shouldContinue();
            playerTurnInput = playerInput(city, ruleBook);
            manageAcreChanges(ruleBook, city, playerTurnInput);
        }
        finishGame(city);
    }
    
    return EXIT_SUCCESS;
}
