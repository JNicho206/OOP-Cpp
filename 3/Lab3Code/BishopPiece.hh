#ifndef __BISHOPPIECE_H__
#define __BISHOPPIECE_H__

#include "ChessPiece.hh"

/**
 * Student implementation of a Bishop chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    class BishopPiece : public ChessPiece
    {
        public:
            BishopPiece(ChessBoard &board, Color color, int row, int column);

            bool canMoveToLocation(int row, int column) override;

            const char* toString() override;
    };
}

#endif
