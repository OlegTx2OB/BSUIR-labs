#pragma once
#include "Board.h"
#include "Piece.h"

class Rook : public Piece
{
public:
	Rook(Color c);
	bool isValidMove(const Board *board, const std::pair<int, int> &fromCoords, const std::pair<int, int> &toCoords) const override;
	~Rook() override = default;
};
