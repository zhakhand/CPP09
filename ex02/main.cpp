#include "PmergeMe.hpp"

int main(int ac, char *av[])
{
	VecInt vec = PMergeMe::sortVec(ac, av);
	DeqInt deq = PMergeMe::sortDeq(ac, av);
}