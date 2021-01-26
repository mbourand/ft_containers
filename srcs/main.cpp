#include <vector>
#include <list>
#include <map>
#include <stack>
#include <queue>
#include <iostream>
#include "vector.hpp"
#include "colors.h"

void test_vector();
void test_list();
void test_map();

int main()
{
	srand(time(NULL));
	std::cout << CYN <<   "   __ _                     _        _                     \n" <<
						  "  / _| |                   | |      (_)                    \n" <<
						  " | |_| |_    ___ ___  _ __ | |_ __ _ _ _ __   ___ _ __ ___ \n" <<
						  " |  _| __|  / __/ _ \\| '_ \\| __/ _` | | '_ \\ / _ \\ '__/ __|\n" <<
						  " | | | |_  | (_| (_) | | | | || (_| | | | | |  __/ |  \\__ \\\n" <<
						  " |_|  \\__|  \\___\\___/|_| |_|\\__\\__,_|_|_| |_|\\___|_|  |___/\n" <<
						  "                                                           \n" <<
						  "                                                           \n" <<
						  std::endl;
	test_vector();
	test_list();
	test_map();
}
