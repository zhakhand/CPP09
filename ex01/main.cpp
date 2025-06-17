#include "RPN.hpp"

int main(int ac, char *av[]) {
	if (ac != 2)
		std::cout << "Provide an RPN string!\n";
	else
	{
		try {
			RPN().process(av[1]);
		} catch (const std::exception& e) {
			std::cout << e.what();
		}
	}
	return 0;
}