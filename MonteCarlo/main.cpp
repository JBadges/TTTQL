#include <iostream>
#include "Trainer.h"

int main() {
	Trainer p1, p2;
	Trainer::runIterations(1000000000, p1, p2);
	Trainer::runIterations(1000000000, p2, p1);


	std::cout << "test" << std::endl;
}