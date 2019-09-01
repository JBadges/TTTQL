#include "Check_Checkers.h"

Check_Checkers::Piece Check_Checkers::getPiece(Loc loc)
{
	return board[loc.row][loc.col];
}

/*
	true - Valid move
	false - didn't move due to invalid option
*/
bool Check_Checkers::move(Loc aLoc, Loc bLoc)
{
	if (!isValidMove(aLoc, bLoc)) {
		return false;
	}

	if (Loc::isJump(aLoc, bLoc)) {
		std::cout << "jump move";
		board[bLoc.row][bLoc.col] = getPiece(aLoc);
		board[bLoc.row][bLoc.col].row = bLoc.row;
		board[bLoc.row][bLoc.col].col = bLoc.col;

		board[aLoc.row][aLoc.col] = Piece();
		board[aLoc.row][aLoc.col].crowned = false;
		board[aLoc.row][aLoc.col].color = NONE;
		board[aLoc.row][aLoc.col].row = aLoc.row;
		board[aLoc.row][aLoc.col].col = aLoc.col;

		Loc avgLoc = avg(aLoc, bLoc);
		std::cout << avgLoc.row << ", " << avgLoc.col << std::endl;
		board[avgLoc.row][avgLoc.col] = Piece();
		board[avgLoc.row][avgLoc.col].crowned = false;
		board[avgLoc.row][avgLoc.col].color = NONE;
		board[avgLoc.row][avgLoc.col].row = avgLoc.row;
		board[avgLoc.row][avgLoc.col].col = avgLoc.col;

		Loc jumps[4] = {
			{ aLoc.row + 2, aLoc.col + 2},
			{ aLoc.row + 2, aLoc.col - 2},
			{ aLoc.row - 2, aLoc.col + 2},
			{ aLoc.row - 2, aLoc.col - 2}
		};

		for (Loc jump : jumps) {
			if (isValidMove(bLoc, jump)) {
				forcedToMove = &getPiece(bLoc);
				return true;
			}
		}

		turn = (turn == RED ? (BLACK) : (RED));
		forcedToMove = nullptr;

		return true;
	}

	board[bLoc.row][bLoc.col] = getPiece(aLoc);
	board[bLoc.row][bLoc.col].row = bLoc.row;
	board[bLoc.row][bLoc.col].col = bLoc.col;

	board[aLoc.row][aLoc.col] = Piece();
	board[aLoc.row][aLoc.col].crowned = false;
	board[aLoc.row][aLoc.col].color = NONE;
	board[aLoc.row][aLoc.col].row = aLoc.row;
	board[aLoc.row][aLoc.col].col = aLoc.col;

	turn = (turn == RED ? (BLACK) : (RED));

	forcedToMove = nullptr;

	return true;
}

bool Check_Checkers::isValidMove(Loc aLoc, Loc bLoc) {
	if (getPiece(aLoc).color == Check_Checkers::Type::NONE) {
		std::cout << "no piece there";
		return false;
	}
	if (getPiece(aLoc).color != turn) {
		std::cout << "not correct turn";
		return false;
	}
	if (forcedToMove) {
		if (*forcedToMove != aLoc) {
			std::cout << "wrong starting piece";
			return false;
		}
	}
	//Jump move
	Loc jumps[4] = {
		{ aLoc.row + 2, aLoc.col + 2},
		{ aLoc.row + 2, aLoc.col - 2},
		{ aLoc.row - 2, aLoc.col + 2},
		{ aLoc.row - 2, aLoc.col - 2}
	};
	
	bool hasMatch = false;
	for (Loc jump : jumps) {
		std::cout << jump.row << ", " << jump.col << std::endl;
		if (jump.col < 0 || jump.col >= 10 || jump.row < 0 || jump.row >= 10) {
			continue;
		}
		if (jump == bLoc) {
			if (getPiece(avg(aLoc, bLoc)).color != getPiece(aLoc).color && getPiece(avg(aLoc, bLoc)).color != NONE) {
				return true;
			}
		}
	}
	if (forcedToMove || hasMatch) {
		std::cout << "forced move return";
		return hasMatch;
	}

	//Normal move
	Loc moves[4] = {
		{ aLoc.row + 1, aLoc.col + 1},
		{ aLoc.row + 1, aLoc.col - 1},
		{ aLoc.row - 1, aLoc.col + 1},
		{ aLoc.row - 1, aLoc.col - 1}
	};
	hasMatch = false;
	for (Loc move : moves) {
		if (move.col < 0 || move.col >= 10 || move.row < 0 || move.row >= 10) {
			continue;
		}
		if (move == bLoc) {
			if (getPiece(bLoc).color == Check_Checkers::Type::NONE) {
				return true;
			}
		}
	}
	return false;
}

Check_Checkers::Loc Check_Checkers::avg(Loc a, Loc b)
{
	return { (a.row + b.row) / 2, (a.col + b.col) / 2 };
}

Check_Checkers::Check_Checkers() : turn(RED), forcedToMove(nullptr) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 10; j++) {
			if (i == 0 || i == 2) {
				if ((j + 1) % 2 == 0) {
					board[i][j] = Piece();
					board[i][j].row = i;
					board[i][j].col = j;
					board[i][j].color = RED;
					board[i][j].crowned = false;
				}
				else {
					board[i][j] = Piece();
					board[i][j].row = i;
					board[i][j].col = j;
					board[i][j].color = NONE;
					board[i][j].crowned = false;
				}
			} else {
				if (j % 2 == 0) {
					board[i][j] = Piece();
					board[i][j].row = i;
					board[i][j].col = j;
					board[i][j].color = RED;
					board[i][j].crowned = false;
				}
				else {
					board[i][j] = Piece();
					board[i][j].row = i;
					board[i][j].col = j;
					board[i][j].color = NONE;
					board[i][j].crowned = false;
				}
			}
		}
	}
	for (int i = 4; i < 6; i++) {
		for (int j = 0; j < 10; j++) {
			board[i][j] = Piece();
			board[i][j].row = i;
			board[i][j].col = j;
			board[i][j].color = NONE;
			board[i][j].crowned = false;
		}
	}
	for (int i = 6; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (i == 6 || i == 8) {
				if ((j + 1) % 2 == 0) {
					board[i][j] = Piece();
					board[i][j].row = i;
					board[i][j].col = j;
					board[i][j].color = BLACK;
					board[i][j].crowned = false;
				}
				else {
					board[i][j] = Piece();
					board[i][j].row = i;
					board[i][j].col = j;
					board[i][j].color = NONE;
					board[i][j].crowned = false;
				}
			} else {
				if (j % 2 == 0) {
					board[i][j] = Piece();
					board[i][j].row = i;
					board[i][j].col = j;
					board[i][j].color = BLACK;
					board[i][j].crowned = false;
				}
				else {
					board[i][j] = Piece();
					board[i][j].row = i;
					board[i][j].col = j;
					board[i][j].color = NONE;
					board[i][j].crowned = false;
				}
			}
		}
	}
}

bool Check_Checkers::Loc::operator==(const Loc& b) const
{
	return b.row == row && b.col == col;
}

bool Check_Checkers::Loc::operator!=(const Loc& b) const
{
	return !(*this==b);
}

bool Check_Checkers::Loc::isJump(const Loc& a, const Loc& b)
{
	return std::abs(a.col - b.col) == 2 && std::abs(a.row - b.row) == 2;
}
