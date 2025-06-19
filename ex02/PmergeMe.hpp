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
	Container checkInput(int ac, char *av[]);

	template <typename PairContainer, typename Container>
	PairContainer createPairs(const Container& container);

	template <typename PairContainer, typename Container>
	Container collectSmalls(const PairContainer& container);

	template <typename PairContainer, typename Container>
	Container collectBigs(const PairContainer& container);

	template <typename Container>
	void binaryInsert(Container& container, int value, int distance);

	template <typename Container>
	int distToPair(const std::pair<int, int>& pair, const Container& bigs);

	template <typename Container, typename PairContainer>
	void insertSmalls(Container& bigs, Container& smalls, int leftover, const PairContainer& pairs);

	template <typename Container, typename PairContainer>
	Container mergeInsertionSort(Container& container);

	template <typename Container, typename Iterator>
	void dump(Container container);
};

#endif