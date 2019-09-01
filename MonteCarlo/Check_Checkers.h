#pragma once

#include <iostream>
#include <cstdlib>
#include <climits>

class Check_Checkers
{
public:
	enum Type {
		NONE,
		RED,
		BLACK
	};

	struct Loc {
		int row, col;

		bool operator==(const Loc& b) const;
		bool operator!=(const Loc& b) const;

		static bool isJump(const Loc& a, const Loc& b);
	};

	struct Piece : public Loc {
		bool crowned;
		Check_Checkers::Type color;
	};

	Piece board[10][10];
	Piece* forcedToMove;
	Type turn;

	Piece getPiece(Loc loc);
	bool move(Loc aLoc, Loc bLoc);
	bool isValidMove(Loc aLoc, Loc bLoc);
	static Loc avg(Loc a, Loc b);

	Check_Checkers();
};

