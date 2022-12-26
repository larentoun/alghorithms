#include <fstream>
#include "Dice.h"

int main()
{
	int throwsCount = 100000;
	int single_d6[30] = { 0 };
	int two_d6[30] = { 0 };
	int three_d6[30] = { 0 };
	int single_d10[30] = { 0 };
	int two_d10[30] = { 0 };
	int three_d10[30] = { 0 };

	std::ofstream outputFile;
	outputFile.open("rolls.csv");
	DiceGenerator dice; //Available input: 0-9, ' ', '-' and '+'
	int rolledValue = 0;
	for (int i = 0; i < throwsCount; ++i) {
		rolledValue = dice.dice("1d6");
		single_d6[rolledValue - 1] += 1;
		rolledValue = dice.dice("2d6");
		two_d6[rolledValue - 1] += 1;
		rolledValue = dice.dice("3d6");
		three_d6[rolledValue - 1] += 1;
		rolledValue = dice.dice("1d10");
		single_d10[rolledValue - 1] += 1;
		rolledValue = dice.dice("2d10");
		two_d10[rolledValue - 1] += 1;
		rolledValue = dice.dice("3d10");
		three_d10[rolledValue - 1] += 1;
	}

	
	outputFile << "value,1d6,2d6,3d6,1d10,2d10,3d10" << std::endl;
	for (int i = 0; i < 30; ++i) {
		outputFile << i + 1 << "," << single_d6[i] << "," << two_d6[i] << "," << three_d6[i] << "," << single_d10[i] << "," << two_d10[i] << "," << three_d10[i] << std::endl;
	}
	outputFile.close();
}
