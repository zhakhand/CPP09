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
	for (size_t i = 0; i < jacobsthal.size(); ++i) {
		if (i == 1) continue;
		if (jacobsthal[i] < size)
			result.push_back(jacobsthal[i]);

		/* Put Remaining Indexes */
		// 0* 1* 3* 2 5* 4 11* 10 9 8 7 6 *21 20 ...
		if (i != 2) {
			for (int j = jacobsthal[i] - 1; j > jacobsthal[i - 1]; --j)
				result.push_back(j);
		}
	}
	return result;
}

template <typename Container>
Container PmergeMe::checkInput(int ac, char *av[]) {
	Container container;
	for (int i = 1; i < ac; ++i) {
		std::string arg(av[i]);
		if (arg.empty() || arg.find_first_not_of("0123456789") != std::string::npos)
			throw std::invalid_argument("Invalid input => " + arg + "\n");
		int number = toInt(arg);
		container.push_back(number);
	}
	return container;
}

template <typename PairContainer, typename Container>
PairContainer PmergeMe::createPairs(const Container& container) {
	PairContainer paired;
	typename Container::const_iterator it = container.begin();
	while (it != container.end()) {
		typename Container::value_type first = *it;
		++it;
		if (it != container.end()) {
			typename Container::value_type second = *it;
			++it;
			paired.push_back(std::make_pair(std::min(first, second), std::max(first, second)));
		} else 
			break;
	}
	return paired;
}

template <typename PairContainer, typename Container>
Container PmergeMe::collectSmalls(const PairContainer& container) {
	Container smalls;
	typename PairContainer::const_iterator it = container.begin();
	while (it != container.end()) {
		smalls.push_back(it->first);
		it++;
	}
	return smalls;
}

template <typename PairContainer, typename Container>
Container PmergeMe::collectBigs(const PairContainer& container) {
	Container bigs;
	typename PairContainer::const_iterator it = container.begin();
	while (it != container.end()) {
		bigs.push_back(it->second);
		it++;
	}
	return bigs;
}

template <typename Container>
void PmergeMe::binaryInsert(Container& container, int value, int distance) {
	typename Container::iterator itLow = container.begin();
	typename Container::iterator itHigh = container.begin() + distance;

	while (itLow != itHigh) {
		typename Container::iterator itMid = itLow + (itHigh - itLow) / 2;
		if (value < *itMid)	itHigh = itMid;
		else itLow = itMid + 1;
		counter++;
	}
	container.insert(itLow, value);
}

template <typename Container>
int PmergeMe::distToPair(const std::pair<int, int>& pair, const Container& bigs) {
	typename Container::const_iterator it = bigs.begin();
	while (it != bigs.end()) {
		if (pair.second == *it)
			return it - bigs.begin();
		it++;
	}
	return (bigs.end() - bigs.begin());
}

template <typename Container, typename PairContainer>
void PmergeMe::insertSmalls(Container& bigs, Container& smalls, int leftover, const PairContainer& pairs) {
	VecInt jacobsthal = generateJacobsthal(smalls.size());
	std::vector<bool> inserted(smalls.size(), false);

	for (size_t i = 0; i < jacobsthal.size(); ++i) {
		int index = jacobsthal[i];
		if (index < (int)smalls.size()) {
			int bigPair = distToPair<Container>(pairs[index], bigs);
			binaryInsert(bigs, smalls[index], bigPair);
			inserted[index] = true;
		}
	}
	if (leftover != -1) binaryInsert(bigs, leftover, bigs.size());
}

template <typename Container, typename PairContainer>
Container PmergeMe::mergeInsertionSort(Container& container) {
	if (container.size() <= 1)
		return container;
	/* Handle leftover */
	int	leftover = -1;
	if (container.size() % 2 == 1)
		leftover = container.back(); 
	/* 1. Separate into pairs */
	PairContainer pairs = createPairs<PairContainer, Container>(container);
	/* Collect Smalls and Bigs */
	Container smalls = collectSmalls<PairContainer, Container>(pairs);
	
	Container bigs = collectBigs<PairContainer, Container>(pairs);

	/* 2. Recursively sort Bigs */
	Container sortedBigs = mergeInsertionSort<Container, PairContainer>(bigs);

	/* 3. Use Binary Insertion and Jacobsthal Sequence to insert smalls*/
	insertSmalls<Container, PairContainer>(sortedBigs, smalls, leftover, pairs);
	return sortedBigs;
}

template <typename Container, typename Iterator>
void PmergeMe::dump(Container container) {
	Iterator it = container.begin();
	Iterator end = container.end();
	int i = 0;
	while (it != end) {
		if (i >= 10) {
			std::cout << "[...]\n";
			break;
		}
		std::cout << *it << " ";
		++it;
		++i;
	}
	std::cout << "\n";
	std::cout << "Container Size: " << end - container.begin();
}

