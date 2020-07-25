#pragma once
#if !defined(SMART_CHAR_PTR_HPP)
#define SMART_CHAR_PTR_HPP
#include<iostream>


typedef unsigned long long LENGTH;

class smart_char_ptr
{
	char* ptr;

public:
	smart_char_ptr();
	explicit smart_char_ptr(char*);
	explicit smart_char_ptr(smart_char_ptr&&);
	smart_char_ptr(const smart_char_ptr&) = delete;
	~smart_char_ptr();
	
	smart_char_ptr& operator=(char*);
	smart_char_ptr& operator=(smart_char_ptr&&);
	smart_char_ptr& operator=(const smart_char_ptr&) = delete;

	char& operator[](LENGTH) const;
	char& operator[](LENGTH);

	explicit operator char*()const;
};

#endif // SMART_CHAR_PTR_HPP