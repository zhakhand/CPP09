#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : _prices(other._prices) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this == &other) return *this;
	this->_prices = other._prices;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::fillDataBase(const std::string& csvFile) {
	if (csvFile.empty())
		throw std::invalid_argument("Error: CSV Filename not given!\n");
	std::ifstream fin;
	fin.open(csvFile.c_str());
	if (!fin.is_open())
		throw std::runtime_error("Error: Could not open file " + csvFile + "\n");
	std::string line;
	bool first = true;
	while (std::getline(fin, line)) {
		if (first) {
			first = false;
			continue;
		}
		if (line.empty()) continue;
		this->_prices[line.substr(0, 10)] = std::strtof(line.substr(11, line.length() - 11).c_str(), NULL);
	}
	fin.close();
}

void BitcoinExchange::searchPrices(const std::string& inputFile) {
	if (inputFile.empty())
		throw std::invalid_argument("Error: Input Filename not given!\n");
	std::ifstream fin(inputFile.c_str());
	if (!fin.is_open())
		throw std::runtime_error("Error: Could not open file " + inputFile + "\n");
	std::string line;
	bool first = true;
	while (std::getline(fin, line)) {
		if (first) {
			first = false;
			continue;
		}
		if (line.empty()) continue;
		try {
			valiDate(line);
		} catch (const std::exception& e) {
			std::cout << e.what();
		}
	}
	fin.close();
}

std::string checkDate(const std::string& date) {
	if (date.at(4) != '-' || date.at(7) != '-')
		throw std::invalid_argument("Error: Invalid Date Format! Use YYYY-MM-DD \n");
	int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int year = std::atoi(date.substr(0, 4).c_str());
	if (year < 2009) throw std::invalid_argument("Error: Invalid Date!\n");
	int month = std::atoi(date.substr(5, 2).c_str());
	if (month < 1 || month > 12) throw std::invalid_argument("Error: Invalid Date!\n");
	int day = std::atoi(date.substr(8, 2).c_str());
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) days[1] = 29;
	if (day < 1 || day > days[month - 1]) throw std::invalid_argument("Error: Invalid Date!\n");
	if (day == 1 && month == 1 && year == 2009) throw std::invalid_argument("Error: Invalid Date!\n");
	return date;
}

float checkVal(const std::string& val) {
	if (val.find_first_not_of("0123456789.") != std::string::npos)
		throw std::invalid_argument("Error: Provided value is not a valid number!\n");
	bool dot = false;
	for (size_t i = 0; i < val.size(); ++i) {
		if (!dot && val.at(i) == '.') 
			dot = true;
		else if (dot && val.at(i) == '.')
			throw std::invalid_argument("Error: Provided value is not a valid number!\n");
	}
	float num = std::strtof(val.c_str(), NULL);
	if (num > 1000) throw std::invalid_argument("Error: too large a number!\n");
	return num;
}

void BitcoinExchange::valiDate(const std::string& line) {
	if (line.length() < 14 || line[11] != '|' || line[10] != ' ' || line[12] != ' ')
		throw std::invalid_argument("Error: bad input => " + line + "\n");
	std::string date = checkDate(line.substr(0, 10));
	float val = checkVal(line.substr(13, line.length() - 13));
	std::map<std::string, float>::iterator it = this->_prices.lower_bound(date);
	if (it->first != date) it--;
	std::cout << date << " => " << val << " => " << val * it->second << "\n";
}
