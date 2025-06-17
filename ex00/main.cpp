#include "BitcoinExchange.hpp"

int main (int ac , char **av) {
	if (ac != 2) {
		std::cout << "Provide an argument <input_file>!\n";
		return 0;
	}
	try {
		BitcoinExchange btc;
		btc.fillDataBase("data.csv");
		btc.searchPrices(av[1]);
	}
	catch (const std::exception &e) {
		std::cerr << e.what();
	}
}