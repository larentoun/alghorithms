#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab2_DynamicArray/Array.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(DefaultConstructTest){
			Array<std::string> myArray;
            Assert::AreEqual(0, myArray.size());
		}
        TEST_METHOD(InsertTest) {
            Array<std::string> myArray;
			for (int i = 0; i < 16; ++i) {
				myArray.insert(std::string("TEST") + std::to_string(myArray.size()));
			}
            Assert::AreEqual(std::string("TEST0"), myArray[0]);
			Assert::AreEqual(std::string("TEST1"), myArray[1]);
			Assert::AreEqual(std::string("TEST2"), myArray[2]);
        }
		TEST_METHOD(RemoveTest) {
			Array<std::string> myArray;
			for (int i = 0; i < 16; ++i) {
				myArray.insert(std::string("TEST") + std::to_string(myArray.size()));
			}
			myArray.remove(2);
			Assert::AreEqual(std::string("TEST3"), myArray[2]);
		}
		TEST_METHOD(InsertWithIndexTest) {
			Array<std::string> myArray;
			for (int i = 0; i < 16; ++i) {
				myArray.insert(std::string("TEST") + std::to_string(myArray.size()));
			}
			std::string textToInsert = "NEWVALUE";
			myArray.insert(3, textToInsert);
			Assert::AreEqual(textToInsert, myArray[3]);
		}
		TEST_METHOD(CopyConstructorTest) {
			Array<std::string> myArray;
			for (int i = 0; i < 16; ++i) {
				myArray.insert(std::string("TEST") + std::to_string(myArray.size()));
			}
			Array<std::string> newArray = myArray;
			Assert::AreEqual(myArray[1], newArray[1]);
			Assert::AreEqual(myArray[2], newArray[2]);
			myArray.insert(1, "NEWVALUE1");
			newArray.insert(2, "NEWVALUE2");
			Assert::AreNotEqual(myArray[1], newArray[1]);
			Assert::AreNotEqual(myArray[2], newArray[2]);
		}
		TEST_METHOD(CopyAssignmentTest) {
			Array<std::string> myArray;
			for (int i = 0; i < 16; ++i) {
				myArray.insert(std::string("TEST") + std::to_string(myArray.size()));
			}
			Array<std::string> newArray;
			newArray = myArray;
			Assert::AreEqual(myArray[1], newArray[1]);
			Assert::AreEqual(myArray[2], newArray[2]);
			myArray.insert(1, "NEWVALUE1");
			newArray.insert(2, "NEWVALUE2");
			Assert::AreNotEqual(myArray[1], newArray[1]);
			Assert::AreNotEqual(myArray[2], newArray[2]);
		}
		TEST_METHOD(IteratorTest) {
			Array<std::string> myArray;
			for (int i = 0; i < 16; ++i) {
				myArray.insert(std::string("TEST") + std::to_string(myArray.size()));
			}
			Array<std::string>::Iterator myIterator = myArray.iterator();
			Assert::AreEqual(myIterator.get(), myArray[0]);
			Assert::AreEqual(myIterator.hasNext(), true);
			myIterator.next();
			Assert::AreEqual(myIterator.get(), myArray[1]);
			myIterator.set("NEWVALUE");
			Assert::AreEqual(myIterator.get(), std::string("NEWVALUE"));
			Assert::AreEqual(myIterator.get(), myArray[1]);
		}
		TEST_METHOD(ReverseIteratorTest) {
			Array<std::string> myArray;
			for (int i = 0; i < 16; ++i) {
				myArray.insert(std::string("TEST") + std::to_string(myArray.size()));
			}
			Array<std::string>::Iterator myIterator = myArray.reverseIterator();
			Assert::AreEqual(myIterator.get(), myArray[myArray.size() - 1]);
			Assert::AreEqual(myIterator.hasNext(), true);
			myIterator.next();
			Assert::AreEqual(myIterator.get(), myArray[myArray.size() - 2]);
			myIterator.set("NEWVALUE");
			Assert::AreEqual(myIterator.get(), std::string("NEWVALUE"));
			Assert::AreEqual(myIterator.get(), myArray[myArray.size() - 2]);
		}
		TEST_METHOD(IntTest) {
			Array<int> myArray;
			for (int i = 0; i < 10; ++i) {
				myArray.insert(i + 1);
			}
			for (int i = 0; i < myArray.size(); ++i) {
				myArray[i] *= 2;
			}
			int counter = 0;
			for (auto it = myArray.iterator(); it.hasNext(); it.next()) {
				Assert::AreEqual(it.get(), myArray[counter]);
				counter++;
			}
		}
	};
}
