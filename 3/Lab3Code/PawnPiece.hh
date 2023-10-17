#ifndef __PAWNPIECE_H__
#define __PAWNPIECE_H__

#include "ChessPiece.hh"


/**
 * Student implementation of a Pawn chess piece.
 * The class is defined within the Student namespace.
 */
namespace Student
{
    class PawnPiece : public ChessPiece
    {   public:
            PawnPiece(ChessBoard &board, Color color, int row, int column);

            bool canMoveToLocation(int row, int column) override;

            const char* toString() override;
    };
}

#endif
