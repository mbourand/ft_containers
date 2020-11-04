#include "vector.hpp"
#include <vector>
#include <iostream>
#include <vector>
#include "colors.h"

class TestClass
{
	public:
		int* val;

		TestClass(int val = 59) : val(new int(val)) {}
		~TestClass() { delete val; }
		TestClass(const TestClass& other) { val = new int(*other.val); }
		TestClass& operator=(const TestClass& other)
		{
			delete val;
			val = new int(*other.val);
			return *this;
		}
};

template<class T, class U>
static bool equal(const T& real, const U& mine)
{
	if (real.size() != mine.size())
	{
		std::cout << "size not equal : " << real.size() << " " << mine.size() << std::endl;
		return false;
	}
	for (size_t j = 0; j < real.size(); j++)
		if (real[j] != mine[j])
		{
			std::cout << "J not equal : " << j << " " << real[j] << " " << mine[j] << std::endl;
			return false;
		}
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

	std::vector<int> real((size_t)58, (int)50);
	ft::vector<int> mine((size_t)58, (int)50);

	std::vector<int> r_empty;
	ft::vector<int> m_empty;

	const std::vector<int> creal((size_t)58, (int)50);
	const ft::vector<int> cmine((size_t)58, (int)50);

	const std::vector<int> r_cempty;
	const ft::vector<int> m_cempty;

	int test = 1;
	bool ok = true;

	std::vector<int>* reals[] = { &real, &r_empty };
	ft::vector<int>* mines[] = { &mine, &m_empty };
	const std::vector<int>* creals[] = { &creal, &r_cempty };
	const ft::vector<int>* cmines[] = { &cmine, &m_cempty };

	for (size_t i = 0; i < sizeof(reals) / sizeof(*reals); i++)
	{
		int off = (reals[i]->size() > 18 ? 18 : reals[i]->size());
		// iterator and reverse_iterator
		test_iterator(reals[i]->begin(), reals[i]->end(), mines[i]->begin(), mines[i]->end(), ok, test);
		test_iterator(reals[i]->begin(), reals[i]->begin() + off, mines[i]->begin(), mines[i]->begin() + off, ok, test);
		test_iterator(reals[i]->rbegin(), reals[i]->rend(), mines[i]->rbegin(), mines[i]->rend(), ok, test);
		test_iterator(reals[i]->rbegin(), reals[i]->rend() - off, mines[i]->rbegin(), mines[i]->rend() - off, ok, test);

		// const_iterator and const_reverse_iterator
		test_iterator(creals[i]->begin(), creals[i]->end(), cmines[i]->begin(), cmines[i]->end(), ok, test);
		test_iterator(creals[i]->begin(), creals[i]->begin() + off, cmines[i]->begin(), cmines[i]->begin() + off, ok, test);
		test_iterator(creals[i]->rbegin(), creals[i]->rend(), cmines[i]->rbegin(), cmines[i]->rend(), ok, test);
		test_iterator(creals[i]->rbegin(), creals[i]->rend() - off, cmines[i]->rbegin(), cmines[i]->rend() - off, ok, test);
	}

	std::cout << '\n' << std::endl;
}

static void test_constructors()
{
	std::cout << MAG << "Constructors :" << std::endl;
	std::vector<int> r_def;
	ft::vector<int> m_def;

	std::vector<int> r_fill = std::vector<int>((size_t)150, (int)89);
	ft::vector<int> m_fill = ft::vector<int>((size_t)150, (int)89);

	std::vector<int> r_cpy(r_fill);
	ft::vector<int> m_cpy(m_fill);

	std::vector<int> r_range(r_cpy.begin(), r_cpy.begin() + 10);
	ft::vector<int> m_range(m_cpy.begin(), m_cpy.begin() + 10);

	std::vector<int> r_range2(r_cpy.begin(), r_cpy.begin() + 10);
	ft::vector<int> m_range2(r_cpy.begin(), r_cpy.begin() + 10);

	std::vector<int> r_assign = r_fill;
	ft::vector<int> m_assign = m_fill;

	int test = 1;
	bool ok = true;

	std::vector<int>* reals[] = { &r_def, &r_cpy, &r_fill, &r_range, &r_range2, &r_assign };
	ft::vector<int>* mines[] = { &m_def, &m_cpy, &m_fill, &m_range, &m_range2, &m_assign };

	for (size_t i = 0; i < sizeof(reals) / sizeof(*reals); i++)
	{
		for (size_t j = 0; j < reals[i]->size(); j++)
		{
			(*reals[i])[j] += j; // So values in vectors are not equal : real[0] != real[50]
			(*mines[i])[j] += j;
		}
		ok = equal(*reals[i], *mines[i]);
		check_ok(test, ok);
		ok = true;
	}
	std::cout << "\n" << std::endl;
}

void test_assign()
{
	std::cout << MAG << "Assign :" << std::endl;

	std::vector<int> real;
	ft::vector<int> mine;

	int test = 1;

	int args[][2] = {{0, 0}, {20, 15}, {0, 15}, {1, 15}, {1000, -800}, {20, 0}, {0, 0}};

	for (size_t i = 0; i < sizeof(args) / sizeof(*args); i++)
	{
		bool ok = true;
		real.assign((size_t)args[i][0], (int)args[i][1]);
		mine.assign((size_t)args[i][0], (int)args[i][1]);
		ok = equal(real, mine);
		check_ok(test, ok);
	}

	std::vector<int> assign_range;
	for (int i = 0; i < 1000; i++)
		assign_range.push_back(235 - 2 * i);

	for (size_t i = 0; i < sizeof(args) / sizeof(*args); i++)
	{
		bool ok = true;
		std::vector<int>::iterator it = assign_range.begin() + args[i][0];
		real.assign(it, assign_range.end());
		mine.assign(it, assign_range.end());
		ok = equal(real, mine);
		check_ok(test, ok);
		ok = true;
	}

	std::cout << '\n' << std::endl;
}

void test_insert()
{
	std::cout << MAG << "Insert :" << std::endl;

	std::vector<int> real;
	ft::vector<int> mine;

	int test = 1;

	int args[][3] = {{0, 20, 15}, {10, 0, 15}, {10, 1, 15}, {18, 1000, -800}, {598, 20, 0}, {0, 0, 0}};

	for (size_t i = 0; i < 6; i++)
	{
		bool ok = true;
		real.insert(real.begin() + args[i][0], (size_t)args[i][1], (int)args[i][2]);
		mine.insert(mine.begin() + args[i][0], (size_t)args[i][1], (int)args[i][2]);
		ok = equal(real, mine);
		check_ok(test, ok);
	}

	for (size_t i = 0; i < sizeof(args) / sizeof(*args); i++)
	{
		bool ok = true;
		std::vector<int>::iterator r_ret = real.insert(real.begin() + args[i][0], (int)args[i][2]);
		ft::vector<int>::iterator m_ret = mine.insert(mine.begin() + args[i][0], (int)args[i][2]);
		ok = equal(real, mine);
		if (r_ret - real.begin() != m_ret - mine.begin())
			ok = false;
		check_ok(test, ok);
	}

	std::vector<int> insertion;
	for (int i = 0; i < 50; i++)
		insertion.push_back(i);

	for (size_t i = 0; i < sizeof(args) / sizeof(*args); i++)
	{
		bool ok = true;
		int random_offset = rand() % insertion.size();
		real.insert(real.begin() + args[i][0], insertion.begin() + random_offset, insertion.end());
		mine.insert(mine.begin() + args[i][0], insertion.begin() + random_offset, insertion.end());
		ok = equal(real, mine);
		check_ok(test, ok);
	}

	std::cout << "\n" << std::endl;
}

void test_erase()
{
	std::cout << MAG << "Erase :" << std::endl;
	std::vector<int> real;
	for (int i = 0; i < 250; i++)
		real.push_back(i);

	ft::vector<int> mine;
	mine.insert(mine.begin(), real.begin(), real.end());

	int test = 1;

	size_t args[][2] = { {0, 5}, {10, 20}, {200, 236}, {5, 5}, {5, 6}, {0, 200} };

	for (size_t i = 0; i < sizeof(args) / sizeof(*args); i++)
	{
		bool ok = true;
		ft::vector<int>::iterator m_it = mine.erase(mine.begin() + args[i][0], args[i][1] > mine.size() ? mine.end() : mine.begin() + args[i][1]);
		std::vector<int>::iterator r_it = real.erase(real.begin() + args[i][0], args[i][1] > real.size() ? real.end() : real.begin() + args[i][1]);
		ok = equal(real, mine);
		if ((m_it - mine.begin()) != (r_it - real.begin()))
			ok = false;
		check_ok(test, ok);
	}

	for (int i = 0; i < 250; i++)
		real.push_back(i);
	mine.insert(mine.begin(), real.begin(), real.end());

	for (size_t i = 0; i < sizeof(args) / sizeof(*args); i++)
	{
		for (size_t j = 0; j < sizeof(*args) / sizeof(**args); j++)
		{
			bool ok = true;
			ft::vector<int>::iterator m_it = mine.erase(mine.begin() + args[i][j]);
			std::vector<int>::iterator r_it = real.erase(real.begin() + args[i][j]);
			ok = equal(real, mine);
			if ((m_it - mine.begin()) != (r_it - real.begin()))
				ok = false;
			check_ok(test, ok);
		}
	}

	std::cout << '\n' << std::endl;
}

void test_push_back()
{
	std::cout << MAG << "Push Back :" << std::endl;

	std::vector<int> real;
	ft::vector<int> mine;

	int test = 1;

	for (int i = 0; i < 15000; i++)
		real.push_back(235 - 2 * i);
	for (int i = 0; i < 15000; i++)
		mine.push_back(235 - 2 * i);
	check_ok(test, equal(real, mine));

	std::cout << '\n' << std::endl;
}

void test_pop_back()
{
	std::cout << MAG << "Pop Back :" << std::endl;

	std::vector<int> real;
	ft::vector<int> mine;

	int test = 1;

	for (int i = 0; i < 15000; i++)
		real.push_back(235 - 2 * i);
	for (int i = 0; i < 15000; i++)
		mine.push_back(235 - 2 * i);

	while (!real.empty())
	{
		for (int i = 0; i < 1000; i++)
		{
			real.pop_back();
			mine.pop_back();
		}
		check_ok(test, equal(real, mine));
	}

	std::cout << std::endl;
}

void test_clear()
{
	std::cout << MAG << "Clear :" << std::endl;

	int test = 1;
	std::vector<int> real;
	ft::vector<int> mine;
	for (int i = 0; i < 1000; i++)
		real.push_back(235 - 2 * i);
	for (int i = 0; i < 1000; i++)
		mine.push_back(235 - 2 * i);

	std::vector<int> r_empty;
	ft::vector<int> m_empty;

	real.clear();
	mine.clear();
	check_ok(test, equal(real, mine));

	real.clear();
	mine.clear();
	check_ok(test, equal(real, mine));

	r_empty.clear();
	m_empty.clear();
	check_ok(test, equal(real, mine));

	std::cout << "\n" << std::endl;
}

static void test_swap()
{
	std::cout << MAG << "Swap :" << std::endl;

	std::vector<int> real((size_t)50, (int)200);
	ft::vector<int> mine((size_t)50, (int)200);
	std::vector<int> real2((size_t)30, (int)10);
	ft::vector<int> mine2((size_t)30, (int)10);
	std::vector<int> r_cpy(real);
	ft::vector<int> m_cpy(mine);
	std::vector<int> r_empty;
	ft::vector<int> m_empty;

	int test = 1;

	real.swap(real2);
	mine.swap(mine2);
	check_ok(test, equal(real2, r_cpy) == equal(mine2, m_cpy));
	real.swap(real2);
	mine.swap(mine2);
	check_ok(test, equal(real, r_cpy) == equal(mine, m_cpy));
	r_empty.swap(real);
	m_empty.swap(mine);
	check_ok(test, equal(r_empty, r_cpy) == equal(m_empty, m_cpy));
	r_empty.swap(real);
	m_empty.swap(mine);
	check_ok(test, equal(real, r_cpy) == equal(mine, m_cpy));

	std::cout << '\n' << std::endl;
}

static void test_front_back_at()
{
	std::cout << MAG << "Front, Back and At :" << std::endl;

	std::vector<int> real;
	for (int i = 0; i < 10; i++)
		real.push_back(i);
	ft::vector<int> mine;
	for (int i = 0; i < 10; i++)
		mine.push_back(i);

	int test = 1;

	while (real.size() >= 2)
	{
		check_ok(test, real.front() == mine.front());
		check_ok(test, real.back() == mine.back());
		for (size_t i = 0; i < real.size(); i++)
			check_ok(test, real.at(i) == mine.at(i));
		real.erase(real.begin());
		mine.erase(mine.begin());
		real.pop_back();
		mine.pop_back();
	}

	try
	{
		mine.at(mine.size());
		check_ok(test, false);
	}
	catch(const std::exception& e) { check_ok(test, true); }

	std::cout << '\n' << std::endl;
}

static void test_reserve()
{
	std::cout << MAG << "Reserve :" << std::endl;

	ft::vector<int> mine;

	int test = 1;

	size_t args[] = { 0, 1, 15, 7, 200, 10 };

	for (size_t i = 0; i < sizeof(args) / sizeof(*args); i++)
	{
		mine.reserve(args[i]);
		check_ok(test, mine.capacity() >= args[i]);
	}

	std::cout << '\n' << std::endl;
}

static void test_resize()
{
	std::cout << MAG << "Resize :" << std::endl;

	std::vector<int> real;
	ft::vector<int> mine;
	for (int i = 0; i < 10; i++)
	{
		real.push_back(i);
		mine.push_back(i);
	}

	int test = 1;

	size_t args[][2] = { {80, 1}, {150, 800}, {1, 0}, {0, 798}, {0, 2147483647}, {58, 477}, {58, 100000}, {90, 10}, {1500, 24}, {0, 43} };

	for (size_t i = 0; i < sizeof(args) / sizeof(*args); i++)
	{
		real.resize(args[i][0], args[i][1]);
		mine.resize(args[i][0], args[i][1]);
		check_ok(test, equal(real, mine));
	}

	std::cout << std::endl;
}

static void test_max_size()
{
	std::cout << MAG << "Max Size :" << std::endl;

	std::vector<int> real;
	ft::vector<int> mine;
	int test = 1;

	check_ok(test, real.max_size() == mine.max_size());

	std::cout << '\n' << std::endl;
}

static void test_relational_operators()
{
	std::cout << MAG << "Relational Operators :" << std::endl;

	int test = 1;

	std::vector<int> reals[] =
	{
		std::vector<int>((size_t)3, (int)100),
		std::vector<int>((size_t)5, (int)100),
		std::vector<int>((size_t)3, (int)500),
		std::vector<int>((size_t)3, (int)100),
		std::vector<int>((size_t)5, (int)500)
	};

	ft::vector<int> mines[] =
	{
		ft::vector<int>((size_t)3, (int)100),
		ft::vector<int>((size_t)5, (int)100),
		ft::vector<int>((size_t)3, (int)500),
		ft::vector<int>((size_t)3, (int)100),
		ft::vector<int>((size_t)5, (int)500),
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

static void test_memory_gesture()
{
	std::cout << MAG << "Memory Gesture :" << std::endl;
	std::cout << RES << "If the program terminates or leak, it means KO, otherwise it's OK" << std::endl;
	ft::vector<TestClass> mine(28);

	mine.assign(48, TestClass(759));
	mine.erase(mine.begin() + 10, mine.end());
	mine.insert(mine.begin(), 150, TestClass(500));
	mine.resize(400);
	mine.resize(40);

	std::cout << '\n' << std::endl;
}

void test_vector()
{
	std::cout << RES << "-----------------------------------------------------------------\n" << std::endl;
	std::cout << GRN <<	"                 _             \n" <<
							"                | |            \n" <<
							" __   _____  ___| |_ ___  _ __ \n" <<
							" \\ \\ / / _ \\/ __| __/ _ \\| '__|\n" <<
							"  \\ V /  __/ (__| || (_) | |   \n" <<
							"   \\_/ \\___|\\___|\\__\\___/|_|   \n" <<
							"                               \n" <<
							"                               " << std::endl;
	test_constructors();
	test_iterators();
	test_insert();
	test_erase();
	test_push_back();
	test_pop_back();
	test_clear();
	test_assign();
	test_swap();
	test_front_back_at();
	test_reserve();
	test_resize();
	test_max_size();
	test_relational_operators();
	test_memory_gesture();

	std::cout << MAG << "size(), operator[] and empty() are used everywhere in the tester and the ft::vector code, if everything else is OK, it means those functions are ok too.\ncapacity() is not tested too, since capacity gesture is implementation-defined.\nIf you want to be sure for correction, just check the code.\n\n" << std::endl;
}
