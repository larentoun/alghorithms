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
������� ������������� ���� ��� ���, ���� ��� ����� � ��������� ���
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

#define MAX_ROUNDS 10

int main()
{
    City city = generateNewCity();
    TurnInfo turnInfo;
    TurnInfo allTurns[MAX_ROUNDS];
    turnInfo.year = 0;
    PlayerTurnInput playerTurnInput;
    while (turnInfo.year < MAX_ROUNDS) {
        turnInfo.year += 1;
        turnInfo = generateNewTurn(city, turnInfo, playerTurnInput);
        allTurns[turnInfo.year] = turnInfo;
        turnInfo.year += 1;
        playerTurnInput = playerInput(turnInfo, city);
    }
    return EXIT_SUCCESS;
}

#undef MAX_ROUNDS