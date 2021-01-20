#include <list>
#include <iostream>
#include "list.hpp"
#include "colors.h"
#include <cmath>

template<class T, class U>
static bool equal(T& real, U& mine)
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

static void check_ok(int& tests, bool ok)
{
	if (ok)
		std::cout << GRN << "[" << tests << ": OK]";
	else
		std::cout << RED << "[" << tests << ": KO]";
	if (tests % 15 == 0)
		std::cout << std::endl;
	else
		std::cout << ' ' << std::flush;
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

	std::cout << '\n' << std::endl;
}

static void test_push_back()
{
	std::cout << MAG << "Push Back :" << std::endl;

	int test = 1;

	std::list<unsigned int> r_def;
	ft::list<unsigned int> m_def;

	for (float f = 0; f < 950; f += 1.1f)
	{
		r_def.push_back(std::abs(round(sin(f) * 2 * 3.14159 / 0.5f)));
		m_def.push_back(std::abs(round(sin(f) * 2 * 3.14159 / 0.5f)));
		if (static_cast<int>(f) % 25 == 0)
			check_ok(test, equal(r_def, m_def));
	}

	std::cout << '\n' << std::endl;
}

static void test_push_front()
{
	std::cout << MAG << "Push Front :" << std::endl;

	int test = 1;

	std::list<unsigned int> r_def;
	ft::list<unsigned int> m_def;

	for (float f = 0; f < 950; f += 1.1f)
	{
		r_def.push_front(std::abs(round(sin(f) * 2 * 3.14159 / 0.5f)));
		m_def.push_front(std::abs(round(sin(f) * 2 * 3.14159 / 0.5f)));
		if (static_cast<int>(f) % 25 == 0)
			check_ok(test, equal(r_def, m_def));
	}

	std::cout << std::endl;
}

static void test_empty()
{
	std::cout << MAG << "Empty :" << std::endl;

	int test = 1;

	std::list<unsigned int> r_def;
	ft::list<unsigned int> m_def;

	check_ok(test, r_def.empty() == m_def.empty());
	r_def.push_front(0);
	m_def.push_front(0);
	check_ok(test, r_def.empty() == m_def.empty());

	std::cout << '\n' << std::endl;
}

static void test_max_size()
{
	std::cout << MAG << "Max Size :" << std::endl;

	int test = 1;

	std::list<unsigned int> r_def;
	ft::list<unsigned int> m_def;

	check_ok(test, r_def.max_size() == m_def.max_size());

	std::cout << '\n' << std::endl;
}

static void test_pop_front()
{
	std::cout << MAG << "Pop Front :" << std::endl;

	int test = 1;

	std::list<int> real;

	ft::list<int> mine;

	for (int i = 0; i < 100; i++)
	{
		real.push_back(i);
		mine.push_back(i);
	}
	for (int i = 0; !real.empty(); i++)
	{
		real.pop_front();
		mine.pop_front();
		if (i % 5 == 0)
			check_ok(test, equal(real, mine));
	}
	check_ok(test, equal(real, mine));

	std::cout << '\n' << std::endl;
}

static void test_pop_back()
{
	std::cout << MAG << "Pop Back :" << std::endl;

	int test = 1;

	std::list<int> real;

	ft::list<int> mine;

	for (int i = 0; i < 100; i++)
	{
		real.push_back(i);
		mine.push_back(i);
	}
	for (int i = 0; !real.empty(); i++)
	{
		real.pop_back();
		mine.pop_back();
		if (i % 5 == 0)
			check_ok(test, equal(real, mine));
	}
	check_ok(test, equal(real, mine));

	std::cout << '\n' << std::endl;
}

static void test_sort()
{
	std::cout << MAG << "Sort :" << std::endl;

	int test = 1;

	for (int version = 0; version < 2; version++)
	{
		for (int i = 0; i < 20; i++)
		{
			std::list<int> real;
			ft::list<int> mine;

			for (int j = 0; j < 1000; j++)
			{
				int r = rand() % 1000;
				real.push_back(r);
				mine.push_back(r);
			}
			if (version == 0)
			{
				real.sort(std::greater<int>());
				mine.sort(std::greater<int>());
			}
			else
			{
				real.sort();
				mine.sort();
			}
			check_ok(test, equal(real, mine));
		}
		ft::list<std::string> m_errors;
		std::list<std::string> r_errors;

		if (version == 0)
		{
			m_errors.sort(std::greater<std::string>());
			r_errors.sort(std::greater<std::string>());
		}
		else
		{
			m_errors.sort();
			r_errors.sort();
		}
		check_ok(test, equal(r_errors, m_errors));

		m_errors.push_back("		Hello    ça va ? 	th");
		r_errors.push_back("		Hello    ça va ? 	th");
		if (version == 0)
		{
			m_errors.sort(std::greater<std::string>());
			r_errors.sort(std::greater<std::string>());
		}
		else
		{
			m_errors.sort();
			r_errors.sort();
		}
		check_ok(test, equal(r_errors, m_errors));

		// Ce test est valide
		m_errors.push_back("		Hello    ça va ? 	th");
		r_errors.push_back("		Hello    ça va ? 	th");
		if (version == 0)
		{
			m_errors.sort(std::greater<std::string>());
			r_errors.sort(std::greater<std::string>());
		}
		else
		{
			m_errors.sort();
			r_errors.sort();
		}
		check_ok(test, equal(r_errors, m_errors));
	}

	std::cout << '\n' << std::endl;
}

template<class RealIterator, class MineIterator>
static void test_iterator(RealIterator r_it, RealIterator r_end, MineIterator m_it, MineIterator m_end, bool& ok, int& test)
{
	while (r_it != r_end && m_it != m_end)
	{
		if (*r_it != *m_it)
		{
			ok = false;
			break;
		}
		r_it++;
		m_it++;
	}
	if ((r_it == r_end && m_it != m_end) || (r_it != r_end && m_it == m_end))
		ok = false;
	check_ok(test, ok);
	ok = true;
}

static void test_iterators()
{
	std::cout << MAG << "Iterators :" << std::endl;

	std::list<int> real((size_t)58, (int)50);
	ft::list<int> mine((size_t)58, (int)50);

	std::list<int> r_empty;
	ft::list<int> m_empty;

	const std::list<int> creal((size_t)58, (int)50);
	const ft::list<int> cmine((size_t)58, (int)50);

	const std::list<int> r_cempty;
	const ft::list<int> m_cempty;

	int test = 1;
	bool ok = true;

	std::list<int>* reals[] = { &real, &r_empty };
	ft::list<int>* mines[] = { &mine, &m_empty };
	const std::list<int>* creals[] = { &creal, &r_cempty };
	const ft::list<int>* cmines[] = { &cmine, &m_cempty };

	for (size_t i = 0; i < sizeof(reals) / sizeof(*reals); i++)
	{
		// iterator and reverse_iterator
		test_iterator(reals[i]->begin(), reals[i]->end(), mines[i]->begin(), mines[i]->end(), ok, test);
		test_iterator(reals[i]->rbegin(), reals[i]->rend(), mines[i]->rbegin(), mines[i]->rend(), ok, test);

		// const_iterator and const_reverse_iterator
		test_iterator(creals[i]->begin(), creals[i]->end(), cmines[i]->begin(), cmines[i]->end(), ok, test);
		test_iterator(creals[i]->rbegin(), creals[i]->rend(), cmines[i]->rbegin(), cmines[i]->rend(), ok, test);
	}

	std::cout << '\n' << std::endl;
}

template<class T>
static T iterator_index(T begin, size_t index)
{
	for (size_t i = 0; i < index; i++)
		begin++;
	return begin;
}

static void test_insert()
{
	std::cout << MAG << "Insert :" << std::endl;

	int test = 1;

	/*
	** Insert one value
	*/

	{
		ft::list<int> m_empty;
		std::list<int> r_empty;

		{
			std::list<int>::iterator r_ret = r_empty.insert(r_empty.begin(), 27);
			ft::list<int>::iterator m_ret = m_empty.insert(m_empty.begin(), 27);
			check_ok(test, equal(m_empty, r_empty) && *r_ret == *m_ret);
		}

		for (int i = 0; i < 1000; i++)
		{
			int r = rand() % 98784;

			int index = rand() % m_empty.size();
			std::list<int>::iterator r_pos = r_empty.begin();
			ft::list<int>::iterator m_pos = m_empty.begin();
			for (int j = 0; j < index; j++)
			{
				r_pos++;
				m_pos++;
			}
			std::list<int>::iterator r_ret = r_empty.insert(r_pos, r);
			ft::list<int>::iterator m_ret = m_empty.insert(m_pos, r);
			if (i % 100 == 0)
				check_ok(test, equal(m_empty, r_empty) && *r_ret == *m_ret);
		}

		{
			std::list<int>::iterator r_ret = r_empty.insert(r_empty.end(), 27);
			ft::list<int>::iterator m_ret = m_empty.insert(m_empty.end(), 27);
			check_ok(test, equal(m_empty, r_empty) && *r_ret == *m_ret);
		}
	}

	/*
	** Insert with count
	*/

	{
		ft::list<int> m_empty;
		std::list<int> r_empty;

		r_empty.insert(r_empty.begin(), (size_t)0, (int)27);
		m_empty.insert(m_empty.begin(), (size_t)0, (int)27);
		check_ok(test, equal(m_empty, r_empty));

		r_empty.insert(r_empty.begin(), (size_t)1, (int)27);
		m_empty.insert(m_empty.begin(), (size_t)1, (int)27);
		check_ok(test, equal(m_empty, r_empty));

		for (int i = 0; i < 500; i++)
		{
			int r = rand() % 98784;
			size_t count = rand() % 10;

			int index = rand() % r_empty.size();
			std::list<int>::iterator r_pos = iterator_index(r_empty.begin(), index);
			ft::list<int>::iterator m_pos = iterator_index(m_empty.begin(), index);
			r_empty.insert(r_pos, count, (int)r);
			m_empty.insert(m_pos, count, (int)r);
			if (i % 100 == 0)
				check_ok(test, equal(m_empty, r_empty));
		}

		r_empty.insert(r_empty.end(), (size_t)50, (int)27);
		m_empty.insert(m_empty.end(), (size_t)50, (int)27);
		check_ok(test, equal(m_empty, r_empty));
	}

	/*
	** Insert with iterators
	*/

	{
		std::list<int> r_empty;

		for (int i = 0; i < 150; i++)
			r_empty.push_back(rand() % 13456);

		ft::list<int> mine;
		std::list<int> real;

		mine.insert(mine.begin(), r_empty.begin(), ++r_empty.begin());
		real.insert(real.begin(), r_empty.begin(), ++r_empty.begin());

		for (int i = 0; i < 10; i++)
		{
			int index = rand() % real.size();
			std::list<int>::iterator r_pos = iterator_index(real.begin(), index);
			ft::list<int>::iterator m_pos = iterator_index(mine.begin(), index);
			std::list<int>::iterator first = iterator_index(r_empty.begin(), index);
			real.insert(r_pos, first, r_empty.end());
			mine.insert(m_pos, first, r_empty.end());
			check_ok(test, equal(real, mine));
		}
	}

	std::cout << '\n' << std::endl;
}

static void test_erase()
{
	std::cout << MAG << "Erase :" << std::endl;

	int test = 1;

	/*
	** Erase simple
	*/
	{
		std::list<float> real;
		ft::list<float> mine;

		for (int i = 0; i < 100; i++)
		{
			int r = rand() % 6487;
			real.push_back(r);
			mine.push_back(r);
		}

		ft::list<float>::iterator m_ret = mine.erase(mine.begin());
		std::list<float>::iterator r_ret = real.erase(real.begin());
		check_ok(test, equal(mine, real) && *m_ret == *r_ret);

		m_ret = mine.erase(--mine.end());
		r_ret = real.erase(--real.end());
		check_ok(test, equal(mine, real) && m_ret == mine.end());

		for (int i = 0; !real.empty(); i++)
		{
			int index = rand() % mine.size();
			m_ret = mine.erase(iterator_index(mine.begin(), index));
			r_ret = real.erase(iterator_index(real.begin(), index));
			if (i % 10 == 0)
				check_ok(test, equal(mine, real));
		}
	}

	{
		std::list<float> real;
		ft::list<float> mine;

		for (int i = 0; i < 1000; i++)
		{
			int r = rand() % 6487;
			real.push_back(r);
			mine.push_back(r);
		}

		ft::list<float>::iterator m_ret = mine.erase(mine.begin(), ++mine.begin());
		std::list<float>::iterator r_ret = real.erase(real.begin(), ++real.begin());
		check_ok(test, equal(mine, real) && *m_ret == *r_ret);

		m_ret = mine.erase(--mine.end(), mine.end());
		r_ret = real.erase(--real.end(), real.end());
		check_ok(test, equal(mine, real) && m_ret == mine.end());

		m_ret = mine.erase(mine.begin(), mine.begin());
		r_ret = real.erase(real.begin(), real.begin());
		check_ok(test, equal(mine, real) && *m_ret == *r_ret);

		m_ret = mine.erase(mine.end(), mine.end());
		r_ret = real.erase(real.end(), real.end());
		check_ok(test, equal(mine, real) && m_ret == mine.end());

		m_ret = mine.erase(mine.begin(), mine.end());
		r_ret = real.erase(real.begin(), real.end());
		check_ok(test, equal(mine, real) && m_ret == mine.end());

		for (int i = 0; i < 1000; i++)
		{
			int r = rand() % 6487;
			real.push_back(r);
			mine.push_back(r);
		}

		for (int i = 0; !real.empty(); i++)
		{
			int index = rand() % (mine.size() / 10 == 0 ? mine.size() : mine.size() / 10);
			m_ret = mine.erase(iterator_index(mine.begin(), index));
			r_ret = real.erase(iterator_index(real.begin(), index));
			if (i % 30 == 0)
				check_ok(test, equal(mine, real));
		}
	}

	std::cout << "\n" << std::endl;
}

void test_swap()
{
	std::cout << MAG << "Swap :" << std::endl;

	int test = 1;

	ft::list<int> m_1, m_2;

	for (int i = 0; i < 4588; i++)
	{
		int r1 = rand() % 4728, r2 = rand() % 4728;
		m_1.push_back(r1);
		m_2.push_back(r2);
	}
	ft::list<int> m_tmp1(m_1), m_tmp2(m_2);

	m_1.swap(m_2);
	check_ok(test, equal(m_tmp1, m_2));
	check_ok(test, equal(m_tmp2, m_1));
	m_1.swap(m_2);
	check_ok(test, equal(m_tmp1, m_1));
	check_ok(test, equal(m_tmp2, m_2));

	std::cout << "\n" << std::endl;
}

static void test_resize()
{
	std::cout << MAG << "Resize :" << std::endl;

	int test = 1;

	std::list<int> real;
	ft::list<int> mine;

	real.resize(0);
	mine.resize(0);
	check_ok(test, equal(real, mine));
	real.resize(200);
	mine.resize(200);
	check_ok(test, equal(real, mine));
	real.resize(50);
	mine.resize(50);
	check_ok(test, equal(real, mine));
	real.resize(500);
	mine.resize(500);
	check_ok(test, equal(real, mine));
	real.resize(1);
	mine.resize(1);
	check_ok(test, equal(real, mine));
	real.resize(0);
	mine.resize(0);
	check_ok(test, equal(real, mine));

	std::cout << "\n" << std::endl;
}

static void test_assign()
{
	std::cout << MAG << "Assign :" << std::endl;

	int test = 1;

	std::list<int> real;
	ft::list<int> mine;

	real.assign((size_t)100, (int)50);
	mine.assign((size_t)100, (int)50);
	check_ok(test, equal(real, mine));
	mine.assign((size_t)15, (int)84);
	real.assign((size_t)15, (int)84);
	check_ok(test, equal(real, mine));
	mine.assign((size_t)0, (int)84);
	real.assign((size_t)0, (int)84);
	check_ok(test, equal(real, mine));

	std::list<int> tmp;
	for (int i = 0; i < 1000; i++)
		tmp.push_back(i);
	mine.assign(tmp.begin(), tmp.end());
	real.assign(tmp.begin(), tmp.end());
	check_ok(test, equal(real, mine));

	mine.assign(tmp.begin(), tmp.begin());
	real.assign(tmp.begin(), tmp.begin());
	check_ok(test, equal(real, mine));

	mine.assign(tmp.end(), tmp.end());
	real.assign(tmp.end(), tmp.end());
	check_ok(test, equal(real, mine));

	std::cout << "\n" << std::endl;
}

static void test_splice()
{
	std::cout << MAG << "Splice :" << std::endl;

	int test = 1;

	std::list<int> real;
	ft::list<int> mine;

	std::list<int> r_reverse;
	ft::list<int> m_reverse;

	for (int i = 0; i < 20; i++)
	{
		real.push_back(i);
		mine.push_back(i);
		r_reverse.push_back(20 - i);
		m_reverse.push_back(20 - i);
	}

	real.splice(real.end(), r_reverse);
	mine.splice(mine.end(), m_reverse);
	check_ok(test, equal(real, mine) && equal(r_reverse, m_reverse));

	r_reverse.splice(r_reverse.begin(), real, real.begin());
	m_reverse.splice(m_reverse.begin(), mine, mine.begin());
	check_ok(test, equal(real, mine) && equal(r_reverse, m_reverse));

	std::list<int>::iterator r_it = real.begin();
	ft::list<int>::iterator m_it = mine.begin();
	for (size_t i = 0; i < real.size() / 2; i++)
	{
		r_it++;
		m_it++;
	}
	r_reverse.splice(++r_reverse.begin(), real, real.begin(), r_it);
	m_reverse.splice(++m_reverse.begin(), mine, mine.begin(), m_it);
	check_ok(test, equal(real, mine) && equal(r_reverse, m_reverse));

	std::cout << "\n" << std::endl;
}

static void test_remove()
{
	std::cout << MAG << "Remove :" << std::endl;

	int test = 1;

	std::list<int> real;
	ft::list<int> mine;

	for (int i = 0; i < 1000; i++)
	{
		real.push_back(i / 2);
		mine.push_back(i / 2);
	}

	real.remove(5000);
	mine.remove(5000);
	check_ok(test, equal(real, mine));
	real.remove(499);
	mine.remove(499);
	check_ok(test, equal(real, mine));
	real.remove(0);
	mine.remove(0);
	check_ok(test, equal(real, mine));
	real.remove(50);
	mine.remove(50);
	check_ok(test, equal(real, mine));

	std::cout << "\n" << std::endl;
}

static bool greater(int a) { return a > 250; }
static bool eq(int a) { return a == 5000; }
static bool less(int a) { return a < 10; }
static void test_remove_if()
{
	std::cout << MAG << "Remove If :" << std::endl;

	int test = 1;

	std::list<int> real;
	ft::list<int> mine;

	for (int i = 0; i < 1000; i++)
	{
		real.push_back(i / 2);
		mine.push_back(i / 2);
	}

	real.remove_if(eq);
	mine.remove_if(eq);
	check_ok(test, equal(real, mine));
	real.remove_if(greater);
	mine.remove_if(greater);
	check_ok(test, equal(real, mine));
	real.remove_if(less);
	mine.remove_if(less);
	check_ok(test, equal(real, mine));

	std::cout << "\n" << std::endl;
}

static void test_unique()
{
	std::cout << MAG << "Unique :" << std::endl;

	int test = 1;

	std::list<int> real;
	ft::list<int> mine;

	for (int i = 0; i < 1000; i++)
	{
		int r = rand() % 56848;
		real.push_back(r);
		mine.push_back(r);
	}
	real.unique();
	mine.unique();
	check_ok(test, equal(real, mine));

	for (int i = 0; i < 1000; i++)
	{
		int r = rand() % 56848;
		real.push_back(r);
		mine.push_back(r);
	}
	real.unique();
	mine.unique();
	check_ok(test, equal(real, mine));


	for (int i = 0; i < 1000; i++)
	{
		int r = rand() % 56848;
		real.push_back(r);
		mine.push_back(r);
	}
	real.unique(std::greater<int>());
	mine.unique(std::greater<int>());
	check_ok(test, equal(real, mine));

	for (int i = 0; i < 1000; i++)
	{
		int r = rand() % 56848;
		real.push_back(r);
		mine.push_back(r);
	}
	real.unique(std::less_equal<int>());
	mine.unique(std::less_equal<int>());
	check_ok(test, equal(real, mine));

	std::cout << "\n" << std::endl;
}

void test_reverse()
{

	std::cout << MAG << "Reverse :" << std::endl;

	int test = 1;

	std::list<int> real;
	ft::list<int> mine;

	for (int i = 0; i < 1000; i++)
	{
		int r = rand() % 45867;
		real.push_back(r);
		mine.push_back(r);
	}
	mine.reverse();
	real.reverse();
	check_ok(test, equal(mine, real));

	mine.clear();
	real.clear();
	mine.reverse();
	real.reverse();
	check_ok(test, equal(mine, real));

	mine.push_back(1);
	real.push_back(1);
	mine.reverse();
	real.reverse();
	check_ok(test, equal(mine, real));

	mine.push_back(2);
	real.push_back(2);
	mine.reverse();
	real.reverse();
	check_ok(test, equal(mine, real));

	mine.reverse();
	real.reverse();
	check_ok(test, equal(mine, real));

	std::cout << "\n" << std::endl;
}

static void test_relational_operators()
{
	std::cout << MAG << "Relational Operators :" << std::endl;

	int test = 1;

	std::list<int> reals[] =
	{
		std::list<int>((size_t)3, (int)100),
		std::list<int>((size_t)5, (int)100),
		std::list<int>((size_t)3, (int)500),
		std::list<int>((size_t)3, (int)100),
		std::list<int>((size_t)5, (int)500)
	};

	ft::list<int> mines[] =
	{
		ft::list<int>((size_t)3, (int)100),
		ft::list<int>((size_t)5, (int)100),
		ft::list<int>((size_t)3, (int)500),
		ft::list<int>((size_t)3, (int)100),
		ft::list<int>((size_t)5, (int)500),
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

void test_list()
{
	std::cout << RES << "-----------------------------------------------------------------\n" << std::endl;

	std::cout << GRN << "  _ _     _   \n | (_)___| |_ \n | | / __| __|\n | | \\__ \\ |_ \n |_|_|___/\\__|\n              \n" << std::endl;

	test_constructors();
	test_iterators();
	test_push_back();
	test_push_front();
	test_empty();
	test_max_size();
	test_pop_front();
	test_pop_back();
	test_sort();
	test_insert();
	test_erase();
	test_swap();
	test_resize();
	test_assign();
	test_splice();
	test_remove();
	test_remove_if();
	test_unique();
	test_reverse();
	test_relational_operators();
}
