#pragma once
#include <random>
#include <iostream>
#include <string>

class DiceGenerator {
public:
	int dice(std::string input);
private:
	void readInput();
	int genNumber(int num);
	int getTotal();
	void readDie(int diceNum, int diceSides);
	std::string inputString_ = "";
	std::string outputString_ = "";
	std::string::iterator iterator;
	int totalValue_ = 0;
	bool nextMod_ = true;
};

int DiceGenerator::dice(std::string input) {
	if (!input.length()) {
		std::cout << "Error occured in dice input!" << std::endl;
		exit(-1);
	}
	inputString_ = input;
	iterator = inputString_.begin();
	while (iterator != inputString_.end()) {
		readInput();
	}
	return getTotal();
}

int DiceGenerator::getTotal() {
	int final = totalValue_;
	totalValue_ = 0;
	outputString_ = "";
	return final;
}

int DiceGenerator::genNumber(int num) {
	std::random_device seed;
	std::mt19937 gen{ seed() }; // seed the generator
	std::uniform_int_distribution<int> dist{ 1,  num }; // set min and max
	int guess = dist(gen); // generate number
	return guess;
}

void DiceGenerator::readInput() {
	std::string modifierString;
	int amount = 0;
	int sides = 0;
	bool isMod = true;
	
	//Getting amount of dice or mod
	while (iterator != inputString_.end()) {
		if (*iterator == 'd') {
			outputString_ += 'd';
			isMod = false;
			iterator++;
			break;
		}
		if (*iterator == ' ') {
			iterator++;
			break;
		}
		if (*iterator == '+') {
			outputString_ += " + ";
			nextMod_ = true;
			iterator++;
			break;
		}
		if (*iterator == '-') {
			outputString_ += " - ";
			nextMod_ = false;
			iterator++;
			break;
		}
		int iteratorValue = *iterator - 48;
		if (iteratorValue >= 0 && iteratorValue < 10) {
			outputString_ += *iterator;
			if (!amount) {
				amount = iteratorValue;
			}
			else {
				amount *= 10;
				amount += iteratorValue;
			}
			iterator++;
			continue;
		}
		std::cout << "Error occured in readInput! Iterator = " << *iterator << std::endl;
		exit(-1);
	}

	//Checking if not a value
	if (amount <= 0) {
		return;
	}

	//If no 'd', then just add value
	if (isMod) {
		totalValue_ += nextMod_ ? amount : -amount;
		return;
	}

	//Getting dice sides
	while (iterator != inputString_.end()) {
		if (*iterator == ' ' || *iterator == '+' || *iterator == '-') {
			break;
		}
		int iteratorValue = *iterator - 48;
		if (iteratorValue >= 0 && iteratorValue < 10) {
			outputString_ += *iterator;
			if (!sides) {
				sides = iteratorValue;
			}
			else {
				sides *= 10;
				sides += iteratorValue;
			}
			iterator++;
			continue;
		}
		break;
	}
	readDie(amount, sides);
}

void DiceGenerator::readDie(int diceNum, int diceSides) {
	outputString_ += " (";
	int randomedValue = 0;
	for (int i = 0; i < diceNum; ++i) {
		randomedValue = genNumber(diceSides);
		totalValue_ += nextMod_ ? randomedValue : -randomedValue;
		outputString_ += std::to_string(randomedValue);
		if (diceNum - 1 > i) {
			outputString_ += ", ";
		}
		else {
			outputString_ += ")";
		}
	}
}

//Array<T>::Array(int capacity) : capacity_(capacity), size_(0) {