#include <map>
#include <iostream>
#include "map.hpp"
#include "colors.h"
#include "utils.h"
#include <cmath>
#include <vector>

static void test_constructors()
{
	std::cout << MAG << "Constructors :" << std::endl;
	int test = 1;

	ft::map<int, double> m_def;
	std::map<int, double> r_def;
	check_ok(test, equal(r_def, m_def));

	std::vector<std::pair<int, double> > v;
	std::vector<ft::pair<int, double> > v2;
	for (int i = 0; i < 100; i++)
	{
		int r = rand() % 800;
		v.push_back(std::pair<int, double>(i, r));
		v2.push_back(ft::pair<int, double>(i, r));
	}

	ft::map<int, double> m_range(v2.begin(), v2.end());
	std::map<int, double> r_range(v.begin(), v.end());
	check_ok(test, equal(r_range, m_range));

	ft::map<int, double> m_cpy(m_range);
	std::map<int, double> r_cpy(r_range);
	check_ok(test, equal(r_cpy, m_cpy));

	std::cout << "\n" << std::endl;
}

static void test_clear()
{
	std::cout << MAG << "Clear :" << std::endl;
	int test = 1;

	std::vector<std::pair<int, double> > v;
	std::vector<ft::pair<int, double> > v2;
	for (int i = 0; i < 100; i++)
	{
		int r = rand() % 800;
		v.push_back(std::pair<int, double>(i, r));
		v2.push_back(ft::pair<int, double>(i, r));
	}

	ft::map<int, double> m_range(v2.begin(), v2.end());
	std::map<int, double> r_range(v.begin(), v.end());
	v2.clear();
	v.clear();
	check_ok(test, equal(r_range, m_range));

	v2.clear();
	v.clear();
	check_ok(test, equal(r_range, m_range));

	ft::map<int, double> m_cpy(m_range);
	std::map<int, double> r_cpy(r_range);
	check_ok(test, equal(r_cpy, m_cpy));
	v2.clear();
	v.clear();
	check_ok(test, equal(r_range, m_range));

	std::cout << "\n" << std::endl;
}

template<class RealIterator, class MineIterator>
static void test_iterator(RealIterator r_it, RealIterator r_end, MineIterator m_it, MineIterator m_end, bool& ok, int& test)
{
	while (r_it != r_end && m_it != m_end)
	{
		if (r_it->first != m_it->first || m_it->second != r_it->second)
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

	std::vector<std::pair<int, double> > v;
	std::vector<ft::pair<int, double> > v2;
	for (int i = 0; i < 100; i++)
	{
		int r = rand() % 800;
		v.push_back(std::pair<int, double>(i, r));
		v2.push_back(ft::pair<int, double>(i, r));
	}

	ft::map<int, double> mine(v2.begin(), v2.end());
	std::map<int, double> real(v.begin(), v.end());

	std::map<int, double> r_empty;
	ft::map<int, double> m_empty;

	const std::map<int, double> creal(v.begin(), v.end());
	const ft::map<int, double> cmine(v2.begin(), v2.end());

	const std::map<int, double> r_cempty;
	const ft::map<int, double> m_cempty;

	int test = 1;
	bool ok = true;

	std::map<int, double>* reals[] = { &real, &r_empty };
	ft::map<int, double>* mines[] = { &mine, &m_empty };
	const std::map<int, double>* creals[] = { &creal, &r_cempty };
	const ft::map<int, double>* cmines[] = { &cmine, &m_cempty };

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

static void test_insert_one_value(int& test)
{
	ft::map<int, std::string> m_empty;
	std::map<int, std::string> r_empty;

	std::vector<std::pair<std::map<int, std::string>::iterator, bool> > r_rets;
	std::vector<ft::pair<ft::map<int, std::string>::iterator, bool> > m_rets;

	{
		for (int i = 0; i < 100; i++)
		{
			int r = rand() % 100;
			std::string v;
			v.assign(1, rand() % 127);
			std::pair<std::map<int, std::string>::iterator, bool> r_ret = r_empty.insert(std::pair<int, std::string>(r, v));
			ft::pair<ft::map<int, std::string>::iterator, bool> m_ret = m_empty.insert(ft::pair<int, std::string>(r, v));
			r_rets.push_back(r_ret);
			m_rets.push_back(m_ret);
			if (i % 10 == 0)
			{
				bool ok = true;
				for (size_t j = 0; j < r_rets.size(); j++)
				{
					if (r_rets[j].first->first != m_rets[j].first->first ||
						r_rets[j].first->second != m_rets[j].first->second ||
						r_rets[j].second != m_rets[j].second)
						ok = false;
				}
				r_rets.clear();
				m_rets.clear();
				check_ok(test, equal(r_empty, m_empty) && ok);
			}
		}
	}
}

static void test_insert_with_hint(int& test)
{
	ft::map<int, std::string> m_empty;
	std::map<int, std::string> r_empty;

	std::vector<std::map<int, std::string>::iterator> r_rets;
	std::vector<ft::map<int, std::string>::iterator> m_rets;

	for (int i = 0; i < 100; i++)
	{
		int r = rand() % 100;
		std::string value;
		value.assign(1, rand() % 127);
		int index = rand() % (r_empty.size() + 1);
		std::map<int, std::string>::iterator r_ret = r_empty.insert(iterator_index(r_empty.begin(), index), std::pair<int, std::string>(r, value));
		ft::map<int, std::string>::iterator m_ret = m_empty.insert(iterator_index(m_empty.begin(), index), ft::pair<int, std::string>(r, value));
		r_rets.push_back(r_ret);
		m_rets.push_back(m_ret);
		if (i % 10 == 0)
		{
			bool ok = true;
			for (size_t j = 0; j < r_rets.size(); j++)
				if (r_rets[j]->first != m_rets[j]->first || r_rets[j]->second != m_rets[j]->second)
					ok = false;
			r_rets.clear();
			m_rets.clear();
			check_ok(test, equal(r_empty, m_empty) && ok);
		}
	}
}

static void test_insert_with_iterators(int& test)
{
	ft::map<int, std::string> m_empty;
	std::map<int, std::string> r_empty;

	std::vector<std::pair<int, std::string> > r_vec;
	std::vector<ft::pair<int, std::string> > m_vec;
	for (int i = 0; i < 1000; i++)
	{
		int r = rand() % 5468;
		std::string str;
		str.assign(1, (char)(rand() % 128));
		r_vec.push_back(std::pair<int, std::string>(r, str));
		m_vec.push_back(ft::pair<int, std::string>(r, str));
	}

	for (int i = 0; i < 100; i++)
	{
		int index = rand() % (r_vec.size() + 1);
		int index2 = rand() % (r_vec.size() + 1 - index) + index;
		r_empty.insert(iterator_index(r_vec.begin(), index), iterator_index(r_vec.begin(), index2));
		m_empty.insert(iterator_index(m_vec.begin(), index), iterator_index(m_vec.begin(), index2));
		if (i % 10 == 0)
			check_ok(test, equal(r_empty, m_empty));
	}
}

static void test_insert()
{
	std::cout << MAG << "Insert :" << std::endl;

	int test = 1;

	test_insert_one_value(test);
	test_insert_with_hint(test);
	test_insert_with_iterators(test);

	std::cout << std::endl;
}

static void test_find()
{
	std::cout << MAG << "Find :" << std::endl;

	std::map<int, std::string> real;
	ft::map<int, std::string> mine;
	int test = 1;

	check_ok(test, (real.find(0)->first == mine.find(0)->first && real.find(0)->second == mine.find(0)->second) || (real.find(0) == real.end() && mine.find(0) == mine.end()));

	for (int i = 0; i < 1000; i++)
	{
		int r = rand() % 1500;
		std::string str;
		for (int j = 0; j < 16; j++)
			str.append(1, rand() % 127);
		real.insert(std::make_pair(r, str));
		mine.insert(ft::make_pair(r, str));
	}

	bool ok = true;
	for (int i = 0; i < 100; i++)
	{
		int r = rand() % 1500;
		if ((real.find(r)->first != mine.find(r)->first || real.find(r)->second != mine.find(r)->second) && !(real.find(r) == real.end() && mine.find(r) == mine.end()))
			ok = false;
		if (i % 10 == 0)
		{
			check_ok(test, ok);
			ok = true;
		}
	}

	// Const find

	const std::map<int, std::string>& creal = real;
	const ft::map<int, std::string>& cmine = mine;

	check_ok(test, (creal.find(0)->first == cmine.find(0)->first && creal.find(0)->second == cmine.find(0)->second) || (creal.find(0) == creal.end() && cmine.find(0) == cmine.end()));
	ok = true;
	for (int i = 0; i < 100; i++)
	{
		int r = rand() % 1500;
		if ((creal.find(r)->first != cmine.find(r)->first || creal.find(r)->second != cmine.find(r)->second) && !(creal.find(r) == creal.end() && cmine.find(r) == cmine.end()))
			ok = false;
		if (i % 10 == 0)
		{
			check_ok(test, ok);
			ok = true;
		}
	}

	std::cout << "\n" << std::endl;
}

void test_lower_upper_bound()
{
	std::cout << MAG << "Lower bound, Upper bound and Equal Range :" << std::endl;

	int test = 1;

	std::map<int, char> real;
	ft::map<int, char> mine;

	const std::map<int, char>& creal = real;
	const ft::map<int, char>& cmine = mine;

	for (int i = 0; i < 50; i++)
	{
		real.insert(std::make_pair(3 * i, 'a'));
		mine.insert(ft::make_pair(3 * i, 'a'));
	}

	for (int i = -38; i < 165; i+=21)
	{
		check_ok(test, real.lower_bound(i)->first == mine.lower_bound(i)->first || (real.lower_bound(i) == real.end() && mine.lower_bound(i) == mine.end()));
		check_ok(test, real.upper_bound(i)->first == mine.upper_bound(i)->first || (real.upper_bound(i) == real.end() && mine.upper_bound(i) == mine.end()));
		check_ok(test, creal.lower_bound(i)->first == cmine.lower_bound(i)->first || (creal.lower_bound(i) == creal.end() && cmine.lower_bound(i) == cmine.end()));
		check_ok(test, creal.upper_bound(i)->first == cmine.upper_bound(i)->first || (creal.upper_bound(i) == creal.end() && cmine.upper_bound(i) == cmine.end()));
		check_ok(test, (real.equal_range(i).first->first == mine.equal_range(i).first->first && creal.equal_range(i).second->first == cmine.equal_range(i).second->first) || (real.equal_range(i).first == real.end() && mine.equal_range(i).first == mine.end()));
		check_ok(test, (creal.equal_range(i).first->first == cmine.equal_range(i).first->first && creal.equal_range(i).second->first == cmine.equal_range(i).second->first) || (creal.equal_range(i).first == creal.end() && cmine.equal_range(i).first == cmine.end()));
	}

	std::cout << std::endl;
}

void test_count()
{
	std::cout << MAG << "Count :" << std::endl;

	int test = 1;

	std::map<int, char> real;
	ft::map<int, char> mine;

	for (int i = 0; i < 50; i++)
	{
		int r = rand() % 20;
		for (int i = 0; i < r; i++)
		{
			real.insert(std::make_pair(3 * i, 'a'));
			mine.insert(ft::make_pair(3 * i, 'a'));
		}
	}

	for (int i = 0; i < 20; i++)
	{
		int r = rand() % 180;
		check_ok(test, real.count(r) == mine.count(r));
	}

	std::cout << "\n" << std::endl;
}

static void test_key_value_compare()
{
	std::cout << MAG << "Key and Value Compare :" << std::endl;

	int test = 1;

	std::map<int, std::string> real;
	ft::map<int, std::string> mine;

	for (int i = 0; i < 15; i++)
	{
		int r1 = (rand() % 1000) * (rand() % 2 == 0 ? -1 : 1), r2 = (rand() % 1000) * (rand() % 2 == 0 ? -1 : 1);
		std::string s1, s2;
		for (int i = 0; i < 16; i++)
		{
			s1.append(1, rand() % 127);
			s2.append(1, rand() % 127);
		}
		check_ok(test, real.key_comp()(r1, r2) == mine.key_comp()(r1, r2));
		check_ok(test, real.value_comp()(std::make_pair(r1, s1), std::make_pair(r2, s2)) == mine.value_comp()(ft::make_pair(r1, s1), ft::make_pair(r2, s2)));
	}

	std::cout << std::endl;
}

static void test_erase()
{
	std::cout << MAG << "Erase :" << std::endl;

	int test = 1;

	std::map<int, std::string> real;
	ft::map<int, std::string> mine;

	for (int i = 0; i < 1000; i++)
	{
		int r = rand() % 2000;
		std::string s;
		for (int i = 0; i < 16; i++)
			s.append(1, rand() % 127);
		real.insert(std::make_pair(r, s));
		mine.insert(ft::make_pair(r, s));
	}

	for (int i = 0; i < 15; i++)
	{
		int index = rand() % real.size();
		real.erase(iterator_index(real.begin(), index));
		mine.erase(iterator_index(mine.begin(), index));
		check_ok(test, equal(real, mine));
	}

	for (int i = 0; i < 15; i++)
	{
		int r = rand() % 2000;
		size_t r_ret = real.erase(r);
		size_t m_ret = mine.erase(r);
		check_ok(test, equal(real, mine) && r_ret == m_ret);
	}

	std::cout << std::endl;
}

static void test_operators()
{
	std::cout << MAG << "Operator = and [] :" << std::endl;
	int test = 1;

	std::map<int, std::string> real;
	ft::map<int, std::string> mine;

	for (int i = 0; i < 1000; i++)
	{
		int r = rand() % 2000;
		std::string s;
		for (int i = 0; i < 16; i++)
			s.append(1, rand() % 127);
		real.insert(std::make_pair(r, s));
		mine.insert(ft::make_pair(r, s));
	}

	ft::map<int, std::string> m_test;
	std::map<int, std::string> r_test;
	r_test = real;
	m_test = mine;
	check_ok(test, equal(r_test, m_test));

	r_test = std::map<int, std::string>();
	m_test = ft::map<int, std::string>();
	check_ok(test, equal(r_test, m_test));

	for (int i = 0; i < 10; i++)
	{
		int r = rand() % 2000;
		std::string r_ret = real[r];
		std::string m_ret = mine[r];
		check_ok(test, r_ret == m_ret && mine[r] == real[r]);
	}

	for (int i = 0; i < 10; i++)
	{
		int r = rand() % 2000;
		std::string s;
		for (int i = 0; i < 16; i++)
			s.append(1, rand() % 127);
		real[r] = s;
		mine[r] = s;
		check_ok(test, real[r] == mine[r] && mine[r] == real[r]);
	}

	std::cout << "\n" << std::endl;
}

static void test_swap()
{
	std::cout << MAG << "Swap :" << std::endl;
	int test = 1;

	std::map<int, std::string> real;
	ft::map<int, std::string> mine;

	for (int i = 0; i < 1000; i++)
	{
		int r = rand() % 2000;
		std::string s;
		for (int i = 0; i < 16; i++)
			s.append(1, rand() % 127);
		real.insert(std::make_pair(r, s));
		mine.insert(ft::make_pair(r, s));
	}

	std::map<int, std::string> r_test;
	ft::map<int, std::string> m_test;

	real.swap(r_test);
	mine.swap(m_test);

	check_ok(test, equal(r_test, m_test) && equal(real, mine));

	real.swap(r_test);
	mine.swap(m_test);

	check_ok(test, equal(r_test, m_test) && equal(real, mine));

	std::cout << "\n" << std::endl;
}

static void test_max_size()
{
	std::cout << MAG << "Max Size :" << std::endl;

	int test = 1;

	std::map<int, std::string> real;
	ft::map<int, std::string> mine;

	check_ok(test, real.max_size() == mine.max_size());

	std::map<int, int> real2;
	ft::map<int, int> mine2;
	check_ok(test, real2.max_size() == mine2.max_size());

	std::cout << "\n" << std::endl;
}

void test_map()
{
	std::cout << RES << "-----------------------------------------------------------------\n"
			  << GRN << "	                        \n" <<
						"  _ __ ___   __ _ _ __  \n" <<
						" | '_ ` _ \\ / _` | '_ \\ \n" <<
						" | | | | | | (_| | |_) |\n" <<
						" |_| |_| |_|\\__,_| .__/ \n" <<
						 "                 |_|    \n" << std::endl;
	test_constructors();
	test_max_size();
	test_clear();
	test_iterators();
	test_insert();
	test_find();
	test_lower_upper_bound();
	test_count();
	test_key_value_compare();
	test_erase();
	test_operators();
	test_swap();
}
