#ifndef UTILS_HPP
#define UTILS_HPP

#include <map>
#include "map.hpp"

template<class T, class U>
bool equal(T& real, U& mine)
{
	typename U::iterator m_it = mine.begin();

	if (real.size() != mine.size())
	{
		std::cout << "\nSize not equal" << std::endl;
		return false;
	}
	for (typename T::iterator r_it = real.begin(); r_it != real.end(); r_it++, m_it++)
		if (*m_it != *r_it)
			return false;
	return true;
}

template<class T, class U>
bool equal(std::map<T, U>& real, ft::map<T, U>& mine)
{
	typename ft::map<T, U>::iterator m_it = mine.begin();

	if (real.size() != mine.size())
	{
		std::cout << "\nSize not equal" << std::endl;
		return false;
	}
	for (typename std::map<T, U>::iterator r_it = real.begin(); r_it != real.end(); r_it++, m_it++)
		if (m_it->first != r_it->first || m_it->second != r_it->second)
			return false;
	return true;
}

template<class T>
static T iterator_index(T begin, size_t index)
{
	for (size_t i = 0; i < index; i++)
		begin++;
	return begin;
}

void check_ok(int& tests, bool ok);

#endif
