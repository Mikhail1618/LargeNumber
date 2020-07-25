#pragma once
#if !defined(TESTNUMBER_HPP)
#define TESTNUMBER_HPP
#include<iostream>
#include"bignumber.hpp"


class TestNumber 
{
public:
	void test_run();
	
private:
	template<typename T1, typename T2, typename T3>
	void test(T1, char, T2, T3);

	template<typename T1, typename T2, typename T3>
	void error(T1, char, T2, T3);

	void good();
};


#endif // TESTNUMBER_HPP