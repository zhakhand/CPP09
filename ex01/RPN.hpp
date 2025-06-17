#ifndef RPN_HPP
#define RPN_HPP

#include <list>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <sstream>
#include <iostream>

class RPN {
private:
	std::list<double> _nums;
public:
	RPN();
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	~RPN();

	void process(const std::string& input);
};

#endif