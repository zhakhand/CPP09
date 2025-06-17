#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN& other) {(void)other;}

RPN& RPN::operator=(const RPN& other) {(void)other; return *this;}

RPN::~RPN() {}

void RPN::process(const std::string& input) {
	if (input.empty()) throw std::invalid_argument("Error: empty input!\n");
	std::istringstream iss(input);
	std::string token;
	while (iss >> token) {
		if (token.find_first_not_of("0123456789+-/*") != std::string::npos || token.size() > 1)
			throw std::invalid_argument("Error: invalid input!\n");
		if (token == "+" || token == "-" || token == "*" || token == "/") {
			if (this->_nums.size() < 2)
				throw std::runtime_error("Error: invalid sequence!\n");
			double second = this->_nums.back();
			this->_nums.pop_back();
			double first = this->_nums.back();
			this->_nums.pop_back();
			if (token == "+") this->_nums.push_back(first + second);
			else if (token == "-") this->_nums.push_back(first - second);
			else if (token == "*") this->_nums.push_back(first * second);
			else if (token == "/") {
				if (second == 0) throw std::runtime_error("Error: dividing by zero!\n");
				this->_nums.push_back(first / second);
			}
		} else {
			this->_nums.push_back(std::atoi(token.c_str()));
		}
	}
	if (this->_nums.size() != 1)
		throw std::invalid_argument("Error: invalid sequence!\n");
	std::cout << this->_nums.back() << "\n";
}
