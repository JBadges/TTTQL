#pragma once

#include <vector>

enum Piece {
	NONE, X, O
};

class TicTacToe
{
public:
	
	TicTacToe() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				board[i][j] = Piece::NONE;
			}
		}
	}

	Piece board[3][3];

	Piece playersTurn = X;

	bool isValidMove(int row, int col);
	void place(int row, int col);

	Piece getWinner();

	std::vector<int> getAllValidMoves();

	void randomMove();

	bool operator==(const TicTacToe& rhs) const;

};

