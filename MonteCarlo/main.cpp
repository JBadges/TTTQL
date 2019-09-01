#include <iostream>
#include "TTT_Trainer.h"
#include "Check_Checkers.h"

int main() {
	Check_Checkers c;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			std::cout << c.board[i][j].color << " ";
		}
		std::cout << std::endl;
	}
	std::cout << c.move({ 3, 2 }, { 4, 1 }) << std::endl;
	std::cout << c.move({ 6, 1 }, { 5, 0 }) << std::endl;
	std::cout << c.move({ 3, 8 }, { 4, 9 }) << std::endl;
	std::cout << c.move({ 5, 0 }, { 3, 2 }) << std::endl;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			std::cout << c.board[i][j].color << " ";
		}
		std::cout << std::endl;
	}

	std::cout << (c.forcedToMove ? ("Forced") : ("Any")) << std::endl;

	int a;
	std::cin >> a;
	TTT_Trainer p1, p2;
	TTT_Trainer::runIterations(1000000000, p1, p2);
	TTT_Trainer::runIterations(1000000000, p2, p1);

	

	std::cout << "test" << std::endl;
}