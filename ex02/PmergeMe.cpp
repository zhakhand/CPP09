#include "PmergeMe.hpp"

PMergeMe::PMergeMe(){}

PMergeMe::PMergeMe(const PMergeMe& other){(void)other;}

PMergeMe& PMergeMe::operator=(const PMergeMe& other) {(void)other; return *this;}

PMergeMe::~PMergeMe() {}

const VecInt PMergeMe::sortVec(int ac, char *av[]) {
	VecInt vecInput = checkInput<VecInt>(ac, av);
	int	unpaired = -1;
	if (vecInput.size() % 2 == 1)
		unpaired = vecInput.back();
	VecPair pairedVec = createPairs<VecPair, VecInt>(vecInput);
	VecPairIt it = pairedVec.begin();
	while (it != pairedVec.end()) {
		std::cout << "(" << it->first << ", " << it->second << ")\n";
		++it;
	}
	if (unpaired != -1)
		std::cout << unpaired << "\n";
	return vecInput;
}

const DeqInt PMergeMe::sortDeq(int ac, char *av[]) {
	DeqInt deqInput = checkInput<DeqInt>(ac, av);

	int unpaired = -1;
	if (deqInput.size() % 2 == 1)
		unpaired = deqInput.back();
	
	DeqPair pairedDeq = createPairs<DeqPair, DeqInt>(deqInput);
	DeqPairIt it = pairedDeq.begin();
	while (it != pairedDeq.end()) {
		std::cout << "(" << it->first << ", " << it->second << ")\n";
		++it;
	}
	if (unpaired != -1)
		std::cout << unpaired << "\n";
	return deqInput;
}

int toInt(const std::string& number) {
	int res = 0;
	for (size_t i = 0; i < number.length(); ++i) {
		res = res * 10 + (number[i] - '0');
		if (res < 0)
			throw std::runtime_error("Int Overflow => " + number + "\n");
	}
	return res;
}