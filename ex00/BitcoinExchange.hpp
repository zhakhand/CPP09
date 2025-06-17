#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

#include <string>
#include <algorithm>
#include <map>
#include <stdexcept>
#include <iostream>
#include <fstream>

class BitcoinExchange {
private:
	std::map<std::string, float> _prices;
public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();

	void fillDataBase(const std::string& csvFile);
	void searchPrices(const std::string& inputFile);
	void valiDate(const std::string&);
};


#endif