#include <iostream>
#include "colors.h"
#include "queue.hpp"
#include <queue>
#include "utils.h"
#include <list>
#include <cstdlib>

static void test_constructor()
{
	std::cout << MAG << "Constructor, Pop and Front :" << std::endl;

	int test = 1;
	std::queue<int> real;
	ft::queue<int> mine;
	check_ok(test, equal(real, mine));

	const std::queue<int>& creal = real;
	const ft::queue<int>& cmine = mine;
	check_ok(test, equal(creal, cmine));

	std::deque<int> c;
	ft::list<int> c2;
	for (int i = 0; i < 100; i++)
	{
		int r = rand() % 1564;
		c.push_back(r);
		c2.push_back(r);
	}

	std::queue<int> real2(c);
	ft::queue<int> mine2(c2);

	const std::queue<int>& creal2 = real2;
	const ft::queue<int>& cmine2 = mine2;

	check_ok(test, equal(real2, mine2));
	check_ok(test, equal(creal2, cmine2));

	std::cout << "\n" << std::endl;
}

static void test_push_and_pop()
{
	std::cout << MAG << "Push, Pop and Front :" << std::endl;
	int test = 1;
	std::queue<int> real;
	ft::queue<int> mine;

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
	std::queue<int> real;
	ft::queue<int> mine;

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
	std::queue<int> real;
	ft::queue<int> mine;
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
static T create_queue(size_t size, const U& val)
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

	std::queue<int> reals[] =
	{
		create_queue<std::queue<int> >((size_t)3, (int)100),
		create_queue<std::queue<int> >((size_t)5, (int)100),
		create_queue<std::queue<int> >((size_t)3, (int)500),
		create_queue<std::queue<int> >((size_t)3, (int)100),
		create_queue<std::queue<int> >((size_t)5, (int)500)
	};

	ft::queue<int> mines[] =
	{
		create_queue<ft::queue<int> >((size_t)3, (int)100),
		create_queue<ft::queue<int> >((size_t)5, (int)100),
		create_queue<ft::queue<int> >((size_t)3, (int)500),
		create_queue<ft::queue<int> >((size_t)3, (int)100),
		create_queue<ft::queue<int> >((size_t)5, (int)500),
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

static void test_back()
{
	std::cout << MAG << "Back :" << std::endl;

	int test = 1;

	std::queue<int> real;
	ft::queue<int> mine;

	for (int i = 0; i < 15; i++)
	{
		real.push(i);
		mine.push(i);
		check_ok(test, real.back() == mine.back());
	}

	for (int i = 0; i < 14; i++)
	{
		real.pop();
		mine.pop();
		check_ok(test, real.back() == mine.back());
	}

	std::cout << '\n' << std::endl;
}

void test_queue()
{
	std::cout << RES << "-----------------------------------------------------------------\n" << std::endl;
	std::cout << GRN << "	                              \n"
						"   __ _ _   _  ___ _   _  ___ \n"
						"  / _` | | | |/ _ \\ | | |/ _ \\\n"
						" | (_| | |_| |  __/ |_| |  __/\n"
						"  \\__, |\\__,_|\\___|\\__,_|\\___|\n"
						"     |_|                      \n" << std::endl;

	test_constructor();
	test_push_and_pop();
	test_back();
	test_size();
	test_empty();
	test_relational_operators();
}
