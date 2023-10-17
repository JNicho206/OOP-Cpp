#ifndef _ROOKPIECE_H__
#define _ROOKPIECE_H__

#include "ChessPiece.hh"

/**
 * Student implementation of a Rook chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    class RookPiece : public ChessPiece
    {   public:
            RookPiece(ChessBoard &board, Color color, int row, int column);

            bool canMoveToLocation(int row, int column) override;

            const char* toString() override;
    };
}

#endif
