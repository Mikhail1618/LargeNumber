#include"bignumber.hpp"

BigUnsignedNumber::exUNumber::exUNumber(const char* msg) : message(msg) {}


LENGTH BigUnsignedNumber::max_digits = TWO_GB;


BigUnsignedNumber::BigUnsignedNumber()
{
	setDigits(1);
	number = new char[digits + 1];

	number[0] = '0';
	number[1] = '\0';
}

BigUnsignedNumber::BigUnsignedNumber(int num) 
	: BigUnsignedNumber((size_t)num) {}

BigUnsignedNumber::BigUnsignedNumber(unsigned long long num)
{
	setDigits(calculate_digits(num));
	number = new char[digits + 1];

	_ui64toa(num, (char*)number, 10);
}

BigUnsignedNumber::BigUnsignedNumber(const char* num)
{
	setDigits(strlen(num));
	number = new char[digits + 1];

	copystr((char*)number, num);
}

BigUnsignedNumber::BigUnsignedNumber(const BigUnsignedNumber& num)
{
	setDigits(num.getDigits());
	number = new char[digits + 1];

	copystr((char*)number, (char*)num.number);
}

BigUnsignedNumber::BigUnsignedNumber(BigUnsignedNumber&& R_num)
{
	digits = R_num.digits;
	number = std::move(R_num.number);
}

BigUnsignedNumber::~BigUnsignedNumber() {}


LENGTH BigUnsignedNumber::getDigits() const
{
	return digits;
}


BigUnsignedNumber& BigUnsignedNumber::operator=(const BigUnsignedNumber& num)
{
	if (this == &num)
		return *this;

	digits = num.getDigits();
	number = new char[digits + 1];

	copystr((char*)number, (char*)num.number);

	return *this;
}

BigUnsignedNumber& BigUnsignedNumber::operator=(BigUnsignedNumber&& R_num)
{
	digits = R_num.digits;
	number = std::move(R_num.number);

	return *this;
}

BigUnsignedNumber& BigUnsignedNumber::operator=(unsigned long long num)
{
	setDigits(calculate_digits(num));
	number = new char[digits + 1];

	_ui64toa(num, (char*)number, 10);

	return *this;
}

BigUnsignedNumber& BigUnsignedNumber::operator=(const char* num)
{
	setDigits(strlen(num));
	number = new char[digits + 1];

	copystr((char*)number, num);
}

BigUnsignedNumber BigUnsignedNumber::operator+(const BigUnsignedNumber& num) const
{
	UNumber result;

	bool leftisbiger = true;
	{
		if (digits < num.digits)
		{
			result = num;
			leftisbiger = false;
		}
		else
		{
			result = *this;
		}
	}


	_strrev((char*)this->number);
	_strrev((char*)num.number);
	_strrev((char*)result);

	short carry = 0;
	LENGTH i;
	for (i = 0; i < minLength(this->digits, num.digits); ++i)
	{
		result.number[i] = sumStrs(this->number[i], num.number[i], carry);
	}

	while (carry && i < result.digits)
	{
		if (leftisbiger)
			result.number[i] = sumStrs(this->number[i], '0', carry);

		else
			result.number[i] = sumStrs('0', num.number[i], carry);

		++i;
	}

	_strrev((char*)this->number);
	_strrev((char*)num.number);
	_strrev((char*)result);

	if (carry)
	{
		result.increase_size();
		result.number[0] = sumStrs('0', '0', carry);
	}

	return UNumber(std::move(result));
}

BigUnsignedNumber& BigUnsignedNumber::operator+=(const BigUnsignedNumber& num)
{
	return *this = std::move(*this + num);
}

BigUnsignedNumber BigUnsignedNumber::operator-(const BigUnsignedNumber& num) const
{
	if (*this < num)
		throw exUNumber("( orerator- )unsigned right value is bigger than left one");

	if (*this == num)
		return UNumber();

	if (num == UNumber())
		return UNumber(std::move(*this));

	UNumber result{ *this };

	_strrev((char*)this->number);
	_strrev((char*)num.number);
	_strrev((char*)result);

	short carry = 0;
	LENGTH i;
	for (i = 0; i < num.digits; ++i)
	{
		result.number[i] = subStrs(this->number[i], num.number[i], carry);
	}

	while (carry && i < result.digits)
	{
		result.number[i] = subStrs(this->number[i], '0', carry);

		++i;
	}

	for (LENGTH j = strlen((char*)result) - 1; ; --j)
	{
		if (result.number[j] == '0')
		{
			result.number[j] = '\0';
		}
		else
		{
			result.digits = strlen((char*)result);
			break;
		}
	}

	_strrev((char*)this->number);
	_strrev((char*)num.number);
	_strrev((char*)result);

	return UNumber(std::move(result));
}

BigUnsignedNumber& BigUnsignedNumber::operator-=(const BigUnsignedNumber& num)
{
	return *this = std::move(*this - num);
}

BigUnsignedNumber BigUnsignedNumber::operator*(const BigUnsignedNumber& num) const
{
	UNumber ZERO;
	if (num == ZERO)
		return UNumber(std::move(ZERO));

	UNumber result{ (char*)number };
	
	{
		UNumber temp{ (char*)number };

		for (UNumber i = 1; i < num; ++i)
			result += temp;
	}

	return UNumber(std::move(result));
}

BigUnsignedNumber& BigUnsignedNumber::operator*=(const BigUnsignedNumber& num)
{
	return *this = std::move(*this * num);
}

//TODO: optimize
BigUnsignedNumber BigUnsignedNumber::operator/(const BigUnsignedNumber& num) const
{
	UNumber ZERO, ONE{ "1" };

	if (num == UNumber())
		throw exUNumber("division by zero");

	if (num == ONE)
		return UNumber(std::move(*this));

	if (*this == num)
		return UNumber(std::move(ONE));

	if (*this < num)
		return UNumber(std::move(ZERO));


	UNumber result{ std::move(ZERO) };

	{
		UNumber temp{ *this };
		do
		{
			temp -= num;
			++result;
		} while (temp >= num);
	}

	return UNumber(std::move(result));
}

BigUnsignedNumber& BigUnsignedNumber::operator/=(const BigUnsignedNumber& num)
{
	return *this = std::move(*this / num);
}

//TODO: optimize
BigUnsignedNumber BigUnsignedNumber::operator% (const BigUnsignedNumber& num) const
{
	UNumber ZERO, ONE{ "1" };
	
	if (*this < num)
		return UNumber(std::move(*this));

	if (*this == num)
		return UNumber(std::move(ZERO));

	if (num == ONE)
		return UNumber(std::move(ZERO));


	UNumber result{ *this };

	do
	{
		result -= num;
	} while (result >= num);

	return UNumber(std::move(result));
}

BigUnsignedNumber& BigUnsignedNumber::operator%= (const BigUnsignedNumber& num)
{
	return *this = std::move(*this % num);
}


BigUnsignedNumber BigUnsignedNumber::operator++(int)
{
	UNumber result{ *this };
	*this += 1;

	return UNumber(std::move(result));
}

BigUnsignedNumber& BigUnsignedNumber::operator++()
{
	return *this += 1;
}


bool BigUnsignedNumber::operator!=(const BigUnsignedNumber& num) const
{
	if (digits != num.getDigits())
		return true;

	for (LENGTH i = 0; i < digits + 1; ++i)
		if (number[i] != static_cast<char*>(num)[i])
			return true;

	return false;
}

bool BigUnsignedNumber::operator==(const BigUnsignedNumber& num) const
{
	if (digits != num.getDigits())
		return false;

	for (LENGTH i = 0; i < digits + 1; ++i)
		if (number[i] != static_cast<char*>(num)[i])
			return false;

	return true;
}

bool BigUnsignedNumber::operator<(const BigUnsignedNumber& num) const
{
	if (digits < num.getDigits())
		return true;

	else if (digits > num.getDigits())
		return false;

	for (LENGTH i = 0; i < digits; ++i)
		if (number[i] > static_cast<char*>(num)[i])
			return false;
		else if (number[i] < static_cast<char*>(num)[i])
			return true;

	return false;
}

bool BigUnsignedNumber::operator<=(const BigUnsignedNumber& num) const
{
	if (*this == num)
		return true;

	else if (*this < num)
		return true;

	return false;
}

bool BigUnsignedNumber::operator>(const BigUnsignedNumber& num) const
{
	if (digits > num.getDigits())
		return true;

	else if (digits < num.getDigits())
		return false;

	for (LENGTH i = 0; i < digits; ++i)
		if (number[i] < static_cast<char*>(num)[i])
			return false;
		else if (number[i] > static_cast<char*>(num)[i])
			return true;

	return false;
}

bool BigUnsignedNumber::operator>=(const BigUnsignedNumber& num) const
{
	if (*this == num)
		return true;

	else if (*this > num)
		return true;

	return false;
}


std::ostream& operator<<(std::ostream& out, const BigUnsignedNumber& num)
{
	out << (char*)num.number;

	return out;
}

void* operator new[](LENGTH size)
{
	void* ptr = malloc(size);
	if (!ptr)
		throw BigUnsignedNumber::exUNumber("error new[size]");

	return ptr;
}

BigUnsignedNumber::operator char*()const
{
	return (char*)number;
}


void BigUnsignedNumber::setDigits(LENGTH len)
{
	if (len > max_digits)
		throw exUNumber("lim digits");

	digits = len;
}

char BigUnsignedNumber::sumStrs(char str1, char str2, short& carry) const noexcept
{
	char result;

	if (str1 + str2 - 48 - 48 + carry > 9)
	{
		result = static_cast<char>(str1 + str2 - 48 - 10 + carry);
		carry = 1;
	}
	else
	{
		result = static_cast<char>(str1 + str2 - 48 + carry);
		carry = 0;
	}

	return result;
}

char BigUnsignedNumber::subStrs(char str1, char str2, short& carry) const noexcept
{
	char result;

	if ((str1 - 48) < (str2 - 48) + carry)
	{
		result = static_cast<char>((str1 - 48) + (10 + 48) - (str2 - 48) - carry);
		carry = 1;
	}
	else
	{
		result = static_cast<char>((str1 - 48) + 48 - (str2 - 48) - carry);
		carry = 0;
	}

	return result;
}

void BigUnsignedNumber::copystr(char* str, const char* orig)
{
	if (str == orig)
		exUNumber("references to one object");

	for (; *orig; orig++, ++str)
		*str = *orig;

	*str = *orig;
}

void BigUnsignedNumber::increase_size()
{
	smart_char_ptr copy_orig{ new char[digits + 1] };

	copystr((char*)copy_orig, (char*)number);

	setDigits(digits + 1);
	number = new char[digits + 1];
	
	number[0] = '0';
	copystr((char*)number + 1, (char*)copy_orig);
}

LENGTH BigUnsignedNumber::minLength(LENGTH len1, LENGTH len2) const noexcept
{
	return len1 < len2 ? len1 : len2;
}

LENGTH BigUnsignedNumber::calculate_digits(unsigned long long num) const
{
	if (!num) return 1;

	LENGTH length = 0;
	while (num > 0)
	{
		length++;
		num /= 10;
	}

	return length;
}
