#include "colors.h"
#include <iostream>

void check_ok(int& tests, bool ok)
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
