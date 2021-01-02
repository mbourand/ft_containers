#include <list>
#include <iostream>
#include "list.hpp"
#include "colors.h"

template<class T, class U>
static bool equal(T& real, U& mine)
{
	typename U::iterator m_it = mine.begin();

	if (real.size() != mine.size())
		return false;
	for (typename T::iterator r_it = real.begin(); r_it != real.end(); r_it++, m_it++)
		if (*m_it != *r_it)
			return false;
	return true;
}

static void check_ok(int& tests, bool ok)
{
	if (ok)
		std::cout << GRN << "[Test " << tests << ": OK]";
	else
		std::cout << RED << "[Test " << tests << ": KO]";
	if (tests % 5 == 0)
		std::cout << std::endl;
	else
		std::cout << '\t' << std::flush;
	tests++;
}

static void test_constructors()
{
	std::cout << MAG << "Constructors :" << std::endl;

	int test = 1;

	std::list<int> r_def;
	std::list<int> r_fill((size_t)20, (int)58);
	std::list<int> r_range(r_fill.begin(), r_fill.end());
	std::list<int> r_cpy(r_range);

	ft::list<int> m_def;
	ft::list<int> m_fill((size_t)20, (int)58);
	ft::list<int> m_range(m_fill.begin(), m_fill.end());
	ft::list<int> m_cpy(m_range);

	check_ok(test, equal(r_def, m_def));
	check_ok(test, equal(r_fill, m_fill));
	check_ok(test, equal(r_range, m_range));
	check_ok(test, equal(r_cpy, m_cpy));
}

void test_list()
{
	std::cout << RES << "-----------------------------------------------------------------\n" << std::endl;

	std::cout << GRN << "  _ _     _   \n | (_)___| |_ \n | | / __| __|\n | | \\__ \\ |_ \n |_|_|___/\\__|\n              \n" << std::endl;

	test_constructors();
}
