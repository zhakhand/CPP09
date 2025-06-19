#include "PmergeMe.hpp"

int main(int ac, char *av[])
{
	if (ac < 2) {
		std::cout << "Error: PROVIDE SOME POSITIVE NUMBERS!\n";
		return 1;
	}
	try {
		PmergeMe vecMerger;
		VecInt vec = vecMerger.sortVec(ac, av);
	} catch (std::exception& e) {
		std::cout << e.what();
	}
	try {
		PmergeMe deqMerger;
		DeqInt deq = deqMerger.sortDeq(ac, av);
	} catch (std::exception& e) {
		std::cout << e.what();
	}
}