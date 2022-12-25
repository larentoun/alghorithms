#include <iostream>
#include "Array.h"

int main()
{
	Array<std::string> myArray;
	for (int i = 0; i < 64; ++i) {
		myArray.insert(myArray.size() - 1, std::string("TEST") + std::to_string(myArray.size()));
	}
	//myArray.insert(0, std::string("TEST1"));
	//myArray.insert(0, std::string("TEST2"));
	//myArray.insert(1, std::string("TEST3"));

	/*
	Array<std::string> myArray;
	for (int i = 0; i < 4; ++i) {
		myArray.insert(std::string("TEST") + std::to_string(myArray.size()));
	}
	std::string textToInsert = "INSERT_AT_START";
	myArray.insert(0, textToInsert);
	std::cout << textToInsert << " AND " << myArray[0] << std::endl;

	textToInsert = "INSERT_AT_SECOND";
	myArray.insert(1, textToInsert);
	std::cout << textToInsert << " AND " << myArray[1] << std::endl;

	textToInsert = "INSERT_AT_LAST_INDEX";
	myArray.insert(myArray.size() - 1, textToInsert);
	std::cout << textToInsert << " AND " << myArray[myArray.size() - 2] << std::endl;

	textToInsert = "INSERT_AT_SIZE";
	myArray.insert(myArray.size(), textToInsert);
	std::cout << textToInsert << " AND " << myArray[myArray.size() - 1] << std::endl;

	textToInsert = "INSERT_PAST_SIZE";
	myArray.insert(myArray.size() + 10, textToInsert);
	std::cout << textToInsert << " AND " << myArray[myArray.size() - 1] << std::endl;*/

	for (int i = 0; i < myArray.size(); ++i) {
		std::cout << myArray[i] << std::endl;
	}
}