#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab3_Sort/QuickSort.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(QuickSortTest)
	{
	public:
		TEST_METHOD(oneItemTest) {
			const int arraySize = 1;
			int a[arraySize] = { 1 };
			quickSort(a, a + arraySize - 1, [](int a, int b) {return a < b; });
			Assert::IsNotNull(a);
		}
		TEST_METHOD(smallTest) {
			const int arraySize = 8;
			int a[arraySize] = { 5,3,8,4,2,7,10,1 };
			quickSort(a, a + arraySize - 1, [](int a, int b) {return a < b; });
			for (int i = 0; i < arraySize - 1; ++i) {
				Assert::IsTrue(a[i] < a[i + 1]);
			}
		}
		TEST_METHOD(smallestTest) {
			const int arraySize = 2;
			int a[arraySize] = { 5,3 };
			quickSort(a, a + arraySize - 1, [](int a, int b) {return a < b; });
			for (int i = 0; i < arraySize - 1; ++i) {
				Assert::IsTrue(a[i] < a[i + 1]);
			}
		}
		TEST_METHOD(intTest) {
			const int arraySize = kArraySize;
			int a[arraySize];
			populateIntArray(a, arraySize);
			quickSort(a, a + arraySize - 1, [](int a, int b) {return a < b; });
			for (int i = 0; i < arraySize - 1; ++i) {
				Assert::IsTrue(a[i] < a[i + 1]);
			}
		}
		TEST_METHOD(typesTest) {
			const int arraySize = kArraySize;
			int a[arraySize];
			int aTest[arraySize];
			std::string b[arraySize];
			std::string bTest[arraySize];
			populateIntArray(a, arraySize);
			for (int i = 0; i < arraySize; ++i) {
				b[i] = std::to_string(a[i]);
			}
			for (int i = 0; i < arraySize; ++i) {
				aTest[i] = a[i];
				bTest[i] = b[i];
			}
			quickSort(a, a + arraySize - 1, [](int a, int b) {return a < b; });
			quickSort(b, b + arraySize - 1, [](std::string a, std::string b) {return a < b; });
			std::sort(aTest, aTest + arraySize, [](int a, int b) {return a < b; });
			std::sort(bTest, bTest + arraySize, [](std::string a, std::string b) {return a < b; });
			for (int i = 0; i < arraySize; ++i) {
				Assert::AreEqual(a[i], aTest[i]);
				Assert::AreEqual(b[i], bTest[i]);
			}
		}
	};
	TEST_CLASS(InsertSortTest)
	{
	public:
		TEST_METHOD(oneItemTest) {
			const int arraySize = 1;
			int a[arraySize] = { 1 };
			insertSort(a, a + arraySize - 1, [](int a, int b) {return a < b; });
			Assert::IsNotNull(a);
		}
		TEST_METHOD(smallTest) {
			const int arraySize = 8;
			int a[arraySize] = { 5,3,8,4,2,7,10,1 };
			insertSort(a, a + arraySize - 1, [](int a, int b) {return a < b; });
			for (int i = 0; i < arraySize - 1; ++i) {
				Assert::IsTrue(a[i] < a[i + 1]);
			}
		}
		TEST_METHOD(smallestTest) {
			const int arraySize = 2;
			int a[arraySize] = { 5,3 };
			insertSort(a, a + arraySize - 1, [](int a, int b) {return a < b; });
			for (int i = 0; i < arraySize - 1; ++i) {
				Assert::IsTrue(a[i] < a[i + 1]);
			}
		}
		TEST_METHOD(intTest) {
			const int arraySize = kArraySize;
			int a[arraySize];
			populateIntArray(a, arraySize);
			insertSort(a, a + arraySize - 1, [](int a, int b) {return a < b; });
			for (int i = 0; i < arraySize - 1; ++i) {
				Assert::IsTrue(a[i] < a[i + 1]);
			}
		}
		TEST_METHOD(typesTest) {
			const int arraySize = kArraySize;
			int a[arraySize];
			int aTest[arraySize];
			std::string b[arraySize];
			std::string bTest[arraySize];
			populateIntArray(a, arraySize);
			for (int i = 0; i < arraySize; ++i) {
				b[i] = std::to_string(a[i]);
			}
			for (int i = 0; i < arraySize; ++i) {
				aTest[i] = a[i];
				bTest[i] = b[i];
			}
			insertSort(a, a + arraySize - 1, [](int a, int b) {return a < b; });
			insertSort(b, b + arraySize - 1, [](std::string a, std::string b) {return a < b; });
			std::sort(aTest, aTest + arraySize, [](int a, int b) {return a < b; });
			std::sort(bTest, bTest + arraySize, [](std::string a, std::string b) {return a < b; });
			for (int i = 0; i < arraySize; ++i) {
				Assert::AreEqual(a[i], aTest[i]);
				Assert::AreEqual(b[i], bTest[i]);
			}
		}
	};
	TEST_CLASS(CombinedSortTest)
	{
	public:
		TEST_METHOD(oneItemTest) {
			const int arraySize = 1;
			int a[arraySize] = { 1 };
			combinedSort(a, a + arraySize - 1, [](int a, int b) {return a < b; });
			Assert::IsNotNull(a);
		}
		TEST_METHOD(smallTest) {
			const int arraySize = 8;
			int a[arraySize] = { 5,3,8,4,2,7,10,1 };
			combinedSort(a, a + arraySize - 1, [](int a, int b) {return a < b; });
			for (int i = 0; i < arraySize - 1; ++i) {
				Assert::IsTrue(a[i] < a[i + 1]);
			}
		}
		TEST_METHOD(smallestTest) {
			const int arraySize = 2;
			int a[arraySize] = { 5,3 };
			combinedSort(a, a + arraySize - 1, [](int a, int b) {return a < b; });
			for (int i = 0; i < arraySize - 1; ++i) {
				Assert::IsTrue(a[i] < a[i + 1]);
			}
		}
		TEST_METHOD(typesTest) {
			const int arraySize = kArraySize;
			int a[arraySize];
			int aTest[arraySize];
			std::string b[arraySize];
			std::string bTest[arraySize];
			populateIntArray(a, arraySize);
			for (int i = 0; i < arraySize; ++i) {
				b[i] = std::to_string(a[i]);
			}
			for (int i = 0; i < arraySize; ++i) {
				aTest[i] = a[i];
				bTest[i] = b[i];
			}
			combinedSort(a, a + arraySize - 1, [](int a, int b) {return a < b; });
			combinedSort(b, b + arraySize - 1, [](std::string a, std::string b) {return a < b; });
			std::sort(aTest, aTest + arraySize, [](int a, int b) {return a < b; });
			std::sort(bTest, bTest + arraySize, [](std::string a, std::string b) {return a < b; });
			for (int i = 0; i < arraySize; ++i) {
				Assert::AreEqual(a[i], aTest[i]);
				Assert::AreEqual(b[i], bTest[i]);
			}
		}
	};
}
