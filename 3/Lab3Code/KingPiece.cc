#include "KingPiece.hh"
#include <math.h>

using namespace Student;


KingPiece::KingPiece(ChessBoard &board, Color color, int row, int column) : ChessPiece(board, color, row, column)
{
    type = King;
}

bool KingPiece::canMoveToLocation(int row, int column)
{
    //Handle move attempts to out of bounds locations
    if (!(isMoveOnBoard(row, column))) return false;

    //Handle move attempts to the same location
    if (isMoveToSameSpot(row, column)) return false;

    //Check if there is a piece of the same color in the way
    if (isMoveToSameColor(row, column)) return false;

    //Move semantics are just one space in any direction
    if (abs(row - getRow()) > 1 || abs(column - getColumn()) > 1) return false;

    return true;
}

const char* KingPiece::toString()
{
    if (getColor() == White)
    {
        return "\u2654";
    }
    else 
    {
        return "\u265A";
    }
}