#include <iostream>
#include "colors.h"
#include "stack.hpp"
#include <stack>
#include "utils.h"
#include <list>
#include <cstdlib>

static void test_constructor()
{
	std::cout << MAG << "Constructor, Pop and Top :" << std::endl;

	int test = 1;
	std::stack<int> real;
	ft::stack<int> mine;
	check_ok(test, equal(real, mine));

	const std::stack<int>& creal = real;
	const ft::stack<int>& cmine = mine;
	check_ok(test, equal(creal, cmine));

	std::deque<int> c;
	ft::list<int> c2;
	for (int i = 0; i < 100; i++)
	{
		int r = rand() % 1564;
		c.push_back(r);
		c2.push_back(r);
	}

	std::stack<int> real2(c);
	ft::stack<int> mine2(c2);

	const std::stack<int>& creal2 = real2;
	const ft::stack<int>& cmine2 = mine2;

	check_ok(test, equal(real2, mine2));
	check_ok(test, equal(creal2, cmine2));

	std::cout << "\n" << std::endl;
}

static void test_push_and_pop()
{
	std::cout << MAG << "Push, Pop and Top :" << std::endl;
	int test = 1;
	std::stack<int> real;
	ft::stack<int> mine;

	for (int i = 0; i < 554; i++)
	{
		int r = rand() % 5847;
		mine.push(r);
		real.push(r);
	}

	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			mine.pop();
			real.pop();
		}
		check_ok(test, equal(real, mine));
	}

	std::cout << "\n" << std::endl;
}

static void test_size()
{
	std::cout << MAG << "Size :" << std::endl;

	int test = 1;
	std::stack<int> real;
	ft::stack<int> mine;

	for (int i = 0; i < 15; i++)
	{
		int r = rand() % 2585;
		real.push(r);
		mine.push(r);
		check_ok(test, equal(real, mine));
	}

	for (int i = 0; i < 15; i++)
	{
		real.pop();
		mine.pop();
		check_ok(test, equal(real, mine));
	}

	std::cout << std::endl;
}

static void test_empty()
{
	std::cout << MAG << "Empty :" << std::endl;

	int test = 1;
	std::stack<int> real;
	ft::stack<int> mine;
	check_ok(test, real.empty() == mine.empty());

	int r = rand() % 2585;
	real.push(r);
	mine.push(r);
	check_ok(test, real.empty() == mine.empty());

	real.pop();
	mine.pop();
	check_ok(test, real.empty() == mine.empty());

	std::cout << '\n' << std::endl;
}

template<class T, class U>
static T create_stack(size_t size, const U& val)
{
	T ret;
	for (size_t i = 0; i < size; i++)
		ret.push(val);
	return ret;
}

static void test_relational_operators()
{
	std::cout << MAG << "Relational Operators :" << std::endl;

	int test = 1;

	std::stack<int> reals[] =
	{
		create_stack<std::stack<int> >((size_t)3, (int)100),
		create_stack<std::stack<int> >((size_t)5, (int)100),
		create_stack<std::stack<int> >((size_t)3, (int)500),
		create_stack<std::stack<int> >((size_t)3, (int)100),
		create_stack<std::stack<int> >((size_t)5, (int)500)
	};

	ft::stack<int> mines[] =
	{
		create_stack<ft::stack<int> >((size_t)3, (int)100),
		create_stack<ft::stack<int> >((size_t)5, (int)100),
		create_stack<ft::stack<int> >((size_t)3, (int)500),
		create_stack<ft::stack<int> >((size_t)3, (int)100),
		create_stack<ft::stack<int> >((size_t)5, (int)500),
	};

	for (size_t i = 0; i < sizeof(reals) / sizeof(*reals); i++)
	{
		for (size_t j = 0; j < sizeof(reals) / sizeof(*reals); j++)
		{
			check_ok(test, (reals[i] == reals[j]) == (mines[i] == mines[j]));
			check_ok(test, (reals[i] != reals[j]) == (mines[i] != mines[j]));
			check_ok(test, (reals[i] >= reals[j]) == (mines[i] >= mines[j]));
			check_ok(test, (reals[i] <= reals[j]) == (mines[i] <= mines[j]));
			check_ok(test, (reals[i] > reals[j]) == (mines[i] > mines[j]));
			check_ok(test, (reals[i] < reals[j]) == (mines[i] < mines[j]));
		}
	}

	std::cout << std::endl;
}

void test_stack()
{
	std::cout << RES << "-----------------------------------------------------------------\n" << std::endl;
	std::cout << GRN <<	"      _             _    \n"
					"  ___| |_ __ _  ___| | __\n"
					" / __| __/ _` |/ __| |/ /\n"
					" \\__ \\ || (_| | (__|   < \n"
					" |___/\\__\\__,_|\\___|_|\\_\\\n"
					"                         \n" << std::endl;
	test_constructor();
	test_push_and_pop();
	test_size();
	test_empty();
	test_relational_operators();
}
