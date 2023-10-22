#include "BishopPiece.hh"
#include <math.h>

using namespace Student;

BishopPiece::BishopPiece(ChessBoard &board, Color color, int row, int column) : ChessPiece(board, color, row, column)
{
    type = Bishop;
}

bool BishopPiece::canMoveToLocation(int row, int column)
{
    //Handle move attempts to out of bounds locations
    if (!(isMoveOnBoard(row, column))) {return false;}

    //Handle move attempts to the same location
    if (isMoveToSameSpot(row, column)) {return false;}

    //Check if there is a piece of the same color at that sport
    if (isMoveToSameColor(row, column)) {return false;}

    
    //Color doesn't matter for this, only starting spot and destination
    //Check if move is diagonal
    if (abs(this->getRow() - row) == abs(this->getColumn() - column))
    {
        //Check if there are pieces in the way
        int rowDirection = (row - this->getRow()) / abs(row - this->getRow());
        int columnDirection = (column - this->getColumn()) / abs(column - this->getColumn());

        for (int i = 1; i < abs(row - this->getRow()); i++)
        {
            //Check if there is a piece 
            if (board.getPiece(this->getRow() + i * rowDirection, this->getColumn() + i * columnDirection) != nullptr)
            {
                return false;
            }
        }

        return true;
    }
    return false;
}

const char* BishopPiece::toString()
{
    if (getColor() == White)
    {
        return "\u2657";
    }
    else 
    {
        return "\u265D";
    }
}