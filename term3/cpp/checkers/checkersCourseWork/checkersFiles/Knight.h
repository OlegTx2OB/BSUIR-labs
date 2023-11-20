#pragma once
#include "Board.h"
#include "Piece.h"

class Knight : public Piece
{
public:
	Knight(Color c);
	bool isValidMove(const Board *board, const std::pair<int, int> &fromCoords, const std::pair<int, int> &toCoords) const override;
	~Knight() override = default;
};
