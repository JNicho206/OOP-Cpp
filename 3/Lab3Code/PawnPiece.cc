#include "PawnPiece.hh"


using namespace Student;

PawnPiece::PawnPiece(ChessBoard &board, Color color, int row, int column) : ChessPiece(board, color, row, column)
{

}

bool PawnPiece::canMoveToLocation(int row, int column)
{
    //Handle move attempts to out of bounds locations
    if (!(isMoveOnBoard(row, column))) return false;

    //Handle move attempts to the same location
    if (isMoveToSameSpot(row, column)) return false;

    //Check if there is a piece of the same color in the way
    if (isMoveToSameSpot(row, column)) return false;

    
    if (this->getColor() == Black)
    {  
        if (row == this->getRow() + 1 && column == this->getColumn())
        {
            return true;
        }
    }
    else
    {
        if (row == this->getRow() - 1 && column == this->getColumn())
        {
            return true;
        }
    }

    return false;
}

const char* PawnPiece::toString()
{
    return "P";
}


