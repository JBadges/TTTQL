#pragma once
#include <cstddef>
#include "TTT_TicTacToe.h"

class TTT_StateAction {
public:
	TTT_TicTacToe state;
	int action;

	TTT_StateAction(TTT_TicTacToe& s, int a) : state(s), action(a) {};


	struct Hash {
		std::size_t operator()(const TTT_StateAction& sa) const;
	};

	struct Pred {
		bool operator()(const TTT_StateAction& lhs, const TTT_StateAction& rhs) const;
	};
};