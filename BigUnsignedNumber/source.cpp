#include"bignumber.hpp"


void savetoFile(const char* const filename, const char* const str, const BigUnsignedNumber& num)
{
	std::ofstream file{ filename, std::ios::out | std::ios::trunc };

	if (file.is_open())
	{
		file << str;
		file << num;
		return;
	}

	const char ch1[] = "file ";
	const char ch2[] = " is not open.";

	LENGTH lenmsg = strlen(ch1) + strlen(filename) + strlen(ch2);
	smart_char_ptr msg{ new char[lenmsg + 1] };

	strcat((char*)msg, ch1);
	strcat((char*)msg, filename);
	strcat((char*)msg, ch2);

	throw BigUnsignedNumber::exUNumber((char*)msg);
}

void savetoFile(const char* const filename, const BigUnsignedNumber& num)
{
	savetoFile(filename, "", num);
}

void readfromFile(const char* filename, const char* const str, BigUnsignedNumber& num)
{
	std::ifstream file{ filename, std::ios::in };

	if (file.is_open())
	{
		file.seekg(strlen(str), std::ios::beg);

		smart_char_ptr tempStr{ new char[num.max_digits + 1] };

		LENGTH i = 0;
		char ch;
		while (file.get(ch))
		{
			if (ch < (int)'0' || ch >(int)'9' || (i + 1) == num.max_digits)
				throw BigUnsignedNumber::exUNumber("error read file");

			tempStr[i++] = ch;
		}
		tempStr[i] = '\0';

		num = (char*)tempStr;

		//file.close();
		return;
	}

	const char ch1[] = "file ";
	const char ch2[] = " is not open.";

	LENGTH lenmsg = strlen(ch1) + strlen(filename) + strlen(ch2);
	smart_char_ptr msg{ new char[lenmsg + 1] };

	strcat((char*)msg, ch1);
	strcat((char*)msg, filename);
	strcat((char*)msg, ch2);

	throw BigUnsignedNumber::exUNumber((char*)msg);
}

BigUnsignedNumber fac(const BigUnsignedNumber& num)
{
	if (num == UNumber("0"))
		return UNumber("1");

	UNumber result{ "1" };

	for (UNumber i = 1; i <= num; ++i)
	{
		result *= i;
		std::cout << i << "  factorial" << "\t\t";
		std::cout << "MB = " << result.getDigits() / 1024 / 1024 << "\t";
		std::cout << "KB = " << result.getDigits() / 1024 << "\t";
		std::cout << "Bt = " << result.getDigits() << "\n";
	}

	return UNumber(std::move(result));
}

BigUnsignedNumber pow(const BigUnsignedNumber& num1, const BigUnsignedNumber& num2)
{
	UNumber ZERO, ONE("1");

	if (num1 == ZERO)
		return UNumber(std::move(ZERO));

	if (num2 == ZERO)
		return UNumber(std::move(ONE));

	if (num2 == ONE || num1 == ONE)
		return UNumber(std::move(num1));

	UNumber result{ num1 };

	for (UNumber i = 1; i < num2;)
	{
		result *= num1; 
		++i;
		std::cout << num1 << "  power  " << i << "\t\t";
		std::cout << "MB = " << result.getDigits() / 1024 / 1024 << "\t";
		std::cout << "KB = " << result.getDigits() / 1024 << "\t";
		std::cout << "Bt = " << result.getDigits() << "\n";
	}

	return UNumber(std::move(result));
}

//TODO: optimize
bool isPrime(const BigUnsignedNumber& num) 
{
	UNumber ZERO, TWO{ "2" };

	if (num < TWO)
		return false;

	if (num == TWO)
		return true;

	if (num % TWO == ZERO)
		return false;

	for (UNumber i = 3; pow(i, TWO) <= num; i += TWO) {
		if ((num % i) == ZERO)
			return false;
	}

	return true;
}

//TODO: optimize
void prime_numbers_up(BigUnsignedNumber& num)
{
	UNumber value{ "2" };

	while (value <= num)
	{
		if (isPrime(value))
			std::cout << value << "\n";

		++value;
	}
}
