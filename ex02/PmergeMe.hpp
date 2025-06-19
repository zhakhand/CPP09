#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include <vector>
#include <deque>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <ctime>

typedef std::vector<int> VecInt;
typedef VecInt::iterator VecIntIt;
typedef std::vector<std::pair<int, int> > VecPair;
typedef VecPair::iterator VecPairIt; 
typedef std::deque<int> DeqInt;
typedef DeqInt::iterator DeqIntIt;
typedef std::deque<std::pair<int, int> > DeqPair;
typedef DeqPair::iterator DeqPairIt;

class PmergeMe {
private:
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	int counter;
public:
	PmergeMe();
	~PmergeMe();
	const VecInt sortVec(int ac, char *av[]);
	const DeqInt sortDeq(int ac, char *av[]);

private:

	int toInt(const std::string& number);
	VecInt generateJacobsthal(int size);
	
	/* TEMPLATES BABYYY!!! */

	template <typename Container>
	Container checkInput(int ac, char *av[]) {
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
	PairContainer createPairs(const Container& container) {
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
	Container collectSmalls(const PairContainer& container) {
		Container smalls;
		typename PairContainer::const_iterator it = container.begin();
		while (it != container.end()) {
			smalls.push_back(it->first);
			it++;
		}
		return smalls;
	}

	template <typename PairContainer, typename Container>
	Container collectBigs(const PairContainer& container) {
		Container bigs;
		typename PairContainer::const_iterator it = container.begin();
		while (it != container.end()) {
			bigs.push_back(it->second);
			it++;
		}
		return bigs;
	}

	template <typename Container>
	void binaryInsert(Container& container, int value, int distance) {
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
	int distToPair(const std::pair<int, int>& pair, const Container& bigs) {
		typename Container::const_iterator it = bigs.begin();
		while (it != bigs.end()) {
			if (pair.second == *it)
				return it - bigs.begin();
			it++;
		}
		return (bigs.end() - bigs.begin());
	} 

	template <typename Container, typename PairContainer>
	void insertSmalls(Container& bigs, Container& smalls, int leftover, const PairContainer& pairs) {
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
		for (size_t i = 0; i < smalls.size(); ++i) {
			if (!inserted[i]) {
				int bigPair = distToPair<Container>(pairs[i], bigs);
				binaryInsert(bigs, smalls[i], bigPair);
			}
		}
		if (leftover != -1) binaryInsert(bigs, leftover, bigs.size());
	}

	template <typename Container, typename PairContainer>
	Container mergeInsertionSort(Container& container) {
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
	void dump(Container container) {
		Iterator it = container.begin();
		Iterator end = container.end();
		int i = 0;
		while (it != end) {
			if (i >= 5) {
				std::cout << "[...]\n";
				break;
			}
			std::cout << *it << " ";
			++it;
			++i;
		}
		std::cout << "\n";
	}
};

#endif