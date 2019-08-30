#include "StateAction.h"
#include "TicTacToe.h"

bool StateAction::Pred::operator()(const StateAction& lhs, const StateAction& rhs) const {
	return (lhs.action == rhs.action && (lhs.state) == (rhs.state));
}

size_t StateAction::Hash::operator()(const StateAction& sa) const {
	size_t s = 0;
	size_t a = sa.action;

	const TicTacToe& b = sa.state;

	/*for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; ++j) {
			int k = (i * 3 + j) % 64;
			int m = (b.board[i / 3][i % 3] == Piece::X || b.board[i / 3][i % 3] == Piece::NONE) ? 0 : 1;
			size_t v = (m << k);
			s |= v;
		}
	}
	return (s << 4) + a;*/


	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; ++j) {
			int n = i * 3 + j;
			//Setting
			//number |= 1UL << n;
			//Clearing
			//number &= ~(1UL << n);
			
			switch (b.board[i][j]) {
			case X:
				//10
				s |= 1UL << (n * 2 + 1);
				s &= ~(1UL << (n*2));
				break;
			case O:
				//01
				s &= 1UL << (n * 2 + 1);
				s |= ~(1UL << (n * 2));
				break;
			case NONE:
				//00
				s &= 1UL << (n * 2 + 1);
				s &= ~(1UL << (n * 2));
				break;
			}
		}
	}

	return (s << 4) + a;
}