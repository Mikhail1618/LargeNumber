#include"smart_char_ptr.hpp"

smart_char_ptr::smart_char_ptr()
{
	ptr = nullptr;
}

smart_char_ptr::smart_char_ptr(char* m_ptr) : ptr(m_ptr) {}

smart_char_ptr::smart_char_ptr(smart_char_ptr&& R_scp)
{
	delete[] ptr;
	ptr = R_scp.ptr;
	R_scp.ptr = nullptr;
}

smart_char_ptr::~smart_char_ptr()
{
	delete[] ptr;
}

smart_char_ptr& smart_char_ptr::operator=(smart_char_ptr&& R_scp)
{
	delete[] ptr;
	ptr = R_scp.ptr;
	R_scp.ptr = nullptr;
	return *this;
}

smart_char_ptr& smart_char_ptr::operator=(char* m_ptr)
{
	delete[] ptr;
	ptr = m_ptr;
	return *this;
}


char& smart_char_ptr::operator[](LENGTH i) const
{
	return ptr[i];
}

char& smart_char_ptr::operator[](LENGTH i)
{
	return ptr[i];
}

smart_char_ptr::operator char*() const
{
	return ptr;
}
