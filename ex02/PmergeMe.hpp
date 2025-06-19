#ifndef PMERGE_ME_HPP
#define PMERGE_ME_HPP

#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <iostream>

typedef std::vector<int> VecInt;
typedef VecInt::iterator VecIntIt;
typedef std::vector<std::pair<int, int> > VecPair;
typedef VecPair::iterator VecPairIt; 
typedef std::deque<int> DeqInt;
typedef DeqInt::iterator DeqIntIt;
typedef std::deque<std::pair<int, int> > DeqPair;
typedef DeqPair::iterator DeqPairIt;

class PMergeMe {
private:
	PMergeMe();
	PMergeMe(const PMergeMe& other);
	PMergeMe& operator=(const PMergeMe& other);
	~PMergeMe();
public:
	static const VecInt sortVec(int ac, char *av[]);
	static const DeqInt sortDeq(int ac, char *av[]);
};

int toInt(const std::string& number);

template <typename T>
T checkInput(int ac, char *av[]) {
	T container;
	for (int i = 1; i < ac; ++i) {
		std::string arg(av[i]);
		if (arg.empty() || arg.find_first_not_of("0123456789") != std::string::npos)
			throw std::invalid_argument("Invalid input => " + arg + "\n");
		int number = toInt(arg);
		container.push_back(number);
	}
	return container;
}

template <typename T, typename C>
T createPairs(const C& container) {
	T paired;
	typename C::const_iterator it = container.begin();
    while (it != container.end()) {
        typename C::value_type first = *it;
        ++it;
        if (it != container.end()) {
            typename C::value_type second = *it;
            ++it;
            paired.push_back(std::make_pair(std::min(first, second), std::max(first, second)));
        } else break;
    }
	return paired;
}

#endif