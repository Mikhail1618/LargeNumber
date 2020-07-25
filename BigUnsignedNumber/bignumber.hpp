#pragma once
#if !defined(BIGNUMBER_HPP)
#define BIGNUMBER_HPP
#include<iostream>
#include<fstream>
#include"smart_char_ptr.hpp"
#include"testnumber.hpp"

typedef unsigned long long LENGTH;

namespace
{
	const LENGTH LIMIT_DIGITS = { 18'446'744'073'709'551'615ull };
	const LENGTH TWO_GB = { 2147483648 };
	const LENGTH FOUR_GB = { 4294967296 };
}


typedef class BigUnsignedNumber
{
	smart_char_ptr number;
	LENGTH digits;

public:
	static LENGTH max_digits;

	class exUNumber
	{
	public:
		const char* message;
		exUNumber(const char* msg);
	};

	BigUnsignedNumber();
	BigUnsignedNumber(int);
	BigUnsignedNumber(unsigned long long);
	explicit BigUnsignedNumber(const char*);
	explicit BigUnsignedNumber(const BigUnsignedNumber&);
	explicit BigUnsignedNumber(BigUnsignedNumber&&);
	~BigUnsignedNumber();


	LENGTH getDigits() const;


	BigUnsignedNumber& operator= (const BigUnsignedNumber&);
	BigUnsignedNumber& operator= (BigUnsignedNumber&&);
	BigUnsignedNumber& operator= (unsigned long long);
	BigUnsignedNumber& operator= (const char*);
	BigUnsignedNumber operator+ (const BigUnsignedNumber&) const;
	BigUnsignedNumber& operator+=(const BigUnsignedNumber&);
	BigUnsignedNumber operator- (const BigUnsignedNumber&) const;
	BigUnsignedNumber& operator-=(const BigUnsignedNumber&);
	BigUnsignedNumber operator* (const BigUnsignedNumber&) const;
	BigUnsignedNumber& operator*=(const BigUnsignedNumber&);
	BigUnsignedNumber operator/ (const BigUnsignedNumber&) const;
	BigUnsignedNumber& operator/=(const BigUnsignedNumber&);
	BigUnsignedNumber operator% (const BigUnsignedNumber&) const;
	BigUnsignedNumber& operator%= (const BigUnsignedNumber&) ;

	BigUnsignedNumber operator++(int);
	BigUnsignedNumber& operator++();

	bool operator!=(const BigUnsignedNumber&) const;
	bool operator==(const BigUnsignedNumber&) const;
	bool operator< (const BigUnsignedNumber&) const;
	bool operator<=(const BigUnsignedNumber&) const;
	bool operator> (const BigUnsignedNumber&) const;
	bool operator>=(const BigUnsignedNumber&) const;

	
	friend std::ostream& operator<<(std::ostream&, const BigUnsignedNumber&);

	friend void* operator new[](LENGTH);

	explicit operator char*()const;

private:
	void setDigits(LENGTH len);
	char sumStrs(char, char, short&) const noexcept;
	char subStrs(char, char, short&) const noexcept;
	void copystr(char*, const char*);
	void increase_size();
	LENGTH minLength(LENGTH len1, LENGTH len2) const noexcept;
	LENGTH calculate_digits(unsigned long long) const;

}UNumber;



void savetoFile(const char* const, const BigUnsignedNumber&);
void savetoFile(const char* const, const char* const, const BigUnsignedNumber&);
void readfromFile(const char*, const char* const, BigUnsignedNumber&);
BigUnsignedNumber fac(const BigUnsignedNumber&);
BigUnsignedNumber pow(const BigUnsignedNumber&, const BigUnsignedNumber&);
bool isPrime(const BigUnsignedNumber&);
void prime_numbers_up(const BigUnsignedNumber&);


#endif // BIGNUMBER_HPP
