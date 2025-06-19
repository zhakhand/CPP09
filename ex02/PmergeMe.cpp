#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : counter(0){}

PmergeMe::PmergeMe(const PmergeMe& other){(void)other;}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {(void)other; return *this;}

PmergeMe::~PmergeMe() {}

const VecInt PmergeMe::sortVec(int ac, char *av[]) {
	VecInt vecInput = checkInput<VecInt>(ac, av);
	std::cout << "\nBefore: ";
	dump<VecInt, VecIntIt>(vecInput);
	
	std::clock_t start = std::clock();
	VecInt sorted = mergeInsertionSort<VecInt, VecPair>(vecInput);
	std::clock_t end = std::clock();
	std::cout << "\nAfter: ";
	dump<VecInt, VecIntIt>(sorted);
	
	std::cout << "\nTime to process the range of " 
				<< vecInput.size() << " with std::vector : " 
				<< static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0 << " microsecs\n";
	std::cout << "Number of comparisons: " << counter << "\n";
	return sorted;
}

const DeqInt PmergeMe::sortDeq(int ac, char *av[]) {
	DeqInt deqInput = checkInput<DeqInt>(ac, av);
	std::cout << "\nBefore: ";
	dump<DeqInt, DeqIntIt>(deqInput);
	
	std::clock_t start = std::clock();
	DeqInt sorted = mergeInsertionSort<DeqInt, DeqPair>(deqInput);
	std::clock_t end = std::clock();
	std::cout << "\nAfter: ";
	dump<DeqInt, DeqIntIt>(sorted);

	std::cout << "\nTime to process the range of " 
				<< deqInput.size() << " with std::deque : " 
				<< static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0 << " microsecs\n";
	std::cout << "\nNumber of comparisons: " << counter << "\n";
	return sorted;
}

int PmergeMe::toInt(const std::string& number) {
	int res = 0;
	for (size_t i = 0; i < number.length(); ++i) {
		res = res * 10 + (number[i] - '0');
		if (res < 0)
			throw std::runtime_error("Int Overflow => " + number + "\n");
	}
	return res;
}

VecInt PmergeMe::generateJacobsthal(int size) {
	VecInt jacobsthal;
	jacobsthal.push_back(0);
	jacobsthal.push_back(1);
	int next = 0;
	while (next < size) {
		next = jacobsthal[jacobsthal.size() - 1] + 2 * jacobsthal[jacobsthal.size() - 2];
		jacobsthal.push_back(next);
	}
	VecInt result;
	for (size_t i = 2; i < jacobsthal.size(); ++i) {
		if (jacobsthal[i] < size)
			result.push_back(jacobsthal[i]);
	}
	return result;
}

