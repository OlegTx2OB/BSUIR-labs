#pragma once
#include "Board.h"
#include "Piece.h"

class King : public Piece
{
public:
	King(Color c);
	bool isValidMove(const Board *board, const std::pair<int, int> &fromCoords, const std::pair<int, int> &toCoords) const override;
	~King() override = default;
};
