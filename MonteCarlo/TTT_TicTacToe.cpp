#include "TTT_TicTacToe.h"
#include <iostream>

bool TTT_TicTacToe::isValidMove(int row, int col)
{
	if (getWinner() != Piece::NONE) {
		return false;
	}

	if (board[row][col] != Piece::NONE) {
		return false;
	}

	return true;
}

void TTT_TicTacToe::place(int row, int col)
{
	if (!isValidMove(row, col)) {
		return;
	}
	board[row][col] = playersTurn;
	playersTurn = playersTurn == Piece::X ? (Piece::O) : (Piece::X);
}

TTT_TicTacToe::Piece TTT_TicTacToe::getWinner()
{
	for (int i = 0; i < 3; i++) {
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != Piece::NONE) {
			return board[i][0];
		}
	}
	for (int i = 0; i < 3; i++) {
		if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != Piece::NONE) {
			return board[0][i];
		}
	}
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != Piece::NONE) {
		return board[1][1];
	}
	if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != Piece::NONE) {
		return board[1][1];
	}
	return Piece::NONE;
}

std::vector<int> TTT_TicTacToe::getAllValidMoves()
{
	std::vector<int> moves;
	for (int i = 0; i < 9; i++) {
		if (isValidMove(i / 3, i % 3)) {
			moves.push_back(i);
		}
	}
	return moves;
}

void TTT_TicTacToe::randomMove()
{
	std::vector<int> moves = getAllValidMoves();
	int randMove = rand() % moves.size();
	place(randMove / 3, randMove % 3);
}

bool TTT_TicTacToe::operator==(const TTT_TicTacToe& rhs) const
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] != rhs.board[i][j]) {
				return false;
			}
		}
	}
	return true;	
}
