#include"testnumber.hpp"

void TestNumber::test_run()
{
	test(1024ull, '+', 1024ull, 2048ull);
	test(1024ULL, '+', 1024ULL, 2048);
	test(1024ULL, '+', 1024, 2048ULL);
	test(1024, '+', 1024ULL, 2048ULL);
	test(1024, '+', 1024, 2048);
	test(0ull, '+', 0ull, 0ull);
	test(1999, '+', 0ull, 1999);
	test(0, '+', 1999, 1999);
	test("9995", '+', 0, "9995");
	test("9995", '+', 0, 9995);
	test("9995", '+', "0", "9995");
	test("9995", '+', "10005", "20000");
	test(9, '+', 1, 10);
	test(14, '+', 7, 21);
	test(18'346'435'631'974'000'863ull,
		'+',
		100'000'000'000'000'000ull,
		18'446'435'631'974'000'863ull
	);


	test(199, '-', 0, 199ull);
	test(199, '-', 200, "exception");
	test("1000", '-', 0ull, 1000);
	test(1000, '-', 199, 801ull);


	test(2, '*', 11, 22);
	test(10, '*', 2, 20);
	test(9, '*', 9, 81);
	test(0, '*', 100000, 0);
	test(999, '*', 0, 0);
	test(1, '*', 1, 1);
	test(1, '*', 1024, 1024);
	test(43, '*', 1, 43);


	test(99, '/', 100, 0);
	test(1, '/', 0, "exception");
	test(3, '/', 3, 1);
	test(3, '/', 2, 1);
	test(50, '/', 11, 4);


	std::cout << "end test\n";
}

template<typename T1, typename T2, typename T3>
void TestNumber::test(T1 num1, char oper, T2 num2, T3 res)
{
	try
	{
		switch (oper)
		{
		case '+':
			if (UNumber(num1) + UNumber(num2) != UNumber(res))
				error(num1, oper, num2, res);
			else
				good();
			break;

		case '-':
			if (UNumber(num1) - UNumber(num2) != UNumber(res))
				error(num1, oper, num2, res);
			else
				good();
			break;

		case '*':
			if (UNumber(num1) * UNumber(num2) != UNumber(res))
				error(num1, oper, num2, res);
			else
				good();
			break;

		case '/':
			if (UNumber(num1) / UNumber(num2) != UNumber(res))
				error(num1, oper, num2, res);
			else
				good();
			break;

		default:
			break;
		}
	}
	catch (UNumber::exUNumber ex)
	{
		std::cout << ex.message
			<< std::endl;
	}
}

template<typename T1, typename T2, typename T3>
void TestNumber::error(T1 num1, char oper, T2 num2, T3 res)
{
	std::cout << "test -- ERROR\n";
	std::cout << num1 << " " << oper << " " << num2 << " != " << res << "\n";
}

void TestNumber::good()
{
	std::cout << "test -- OK\n";
}
