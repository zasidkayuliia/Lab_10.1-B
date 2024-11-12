#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_10.1 B/Lab_10.1 B.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			const int N = 3;
			Student students[N] = {
				{"Student1", 1, KOMPUTERNI_NAYKU, 5, 5, 5},
				{"Student2", 2, INFORMATUKA, 3, 4, 5},
				{"Student3", 3, MATEMATUKA_TA_EKONOMIKA, 5, 5, 4} };

			double percent = LineSearch(students, N);

			Assert::AreEqual(2, (int)(percent * N / 100));
		}
	};
}
