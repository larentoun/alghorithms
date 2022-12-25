#include <iostream>
#include "Dice.h"

int main()
{
	DiceGenerator dice; //Available input: 0-9, ' ', '-' and '+'
	for (int i = 0; i < 10; ++i) {
		dice.dice("1d6");
	}
}
