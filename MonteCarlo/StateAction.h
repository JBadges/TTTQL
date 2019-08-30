#pragma once
#include <cstddef>
#include "TicTacToe.h"

class StateAction {
public:
	TicTacToe state;
	int action;

	StateAction(TicTacToe& s, int a) : state(s), action(a) {};


	struct Hash {
		std::size_t operator()(const StateAction& sa) const;
	};

	struct Pred {
		bool operator()(const StateAction& lhs, const StateAction& rhs) const;
	};
};