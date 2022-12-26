#include "Header.h"

/*
        �������� ����
���������� ������� - 10
����� ������������� ��������� ������
�������:
- ���������
- ��� �����
- ������ �������
������ ����� - ���� ��� ���������
������ ��������� ����������� ��������� ���������� ��� �����
���� ����� ���������� ��������� ���������� ������� �������
������� ������������ ���� ��� ���, ���� ��� ����� � ��������� ���
���� ����� ����� ���� ������� � ������� �� �������

        ������� ����
������ ����� ���������� �� ������� ������� ��� � ������, ������� ��:
- ���� ������� �� ������� �����
- ���� ����� ������
- ��������� ���������

����� �����:
- ������ ��� ������� �����
- ������������ ������� ��� �����
- ������������ ������� ��� ���
(��� � ���������)

        �������� ����������
���� �������� �� ������ ��������� ������ ����������, ����� ��� ������� � ������������ ������� ���������� �� �����
������������ RNG � ������ ������ ���:
- ���� �����
- ���������� ������� � �����
- ���������� �������, ��������� �������
- ���������� ���������, ��������� � �����
- ����� ����, ������� ����� ������� ���������.

���� ������������� ����� 10 �������, ����� ����� ������, ��� ���� ����� 45% ��������� ����� �� ������ � ������� ������ ������.
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
            std::cout << "���� ������� ����, ����������? 1/0" << std::endl;
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
