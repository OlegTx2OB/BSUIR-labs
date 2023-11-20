#pragma once
#include "Board.h"
#include "Piece.h"

class Pawn : public Piece
{
public:
	Pawn(Color c);
	bool isValidMove(const Board *board, const std::pair<int, int> &fromCoords, const std::pair<int, int> &toCoords) const override;
	~Pawn() override = default;
};
