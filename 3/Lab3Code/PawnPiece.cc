#include "PawnPiece.hh"
#include <math.h>

using namespace Student;

PawnPiece::PawnPiece(ChessBoard &board, Color color, int row, int column) : ChessPiece(board, color, row, column)
{
    type = Pawn;
}

bool PawnPiece::canMoveToLocation(int row, int column)
{
    //Handle move attempts to out of bounds locations
    if (!(isMoveOnBoard(row, column))) {return false;}

    //Handle move attempts to the same location
    if (isMoveToSameSpot(row, column)) {return false;}

    //Check if there is a piece of the same color in the way
    if (isMoveToSameColor(row, column)) {return false;}
 
    //Check if move is within max row (2 at most) and column (1 at most) range
    if ((abs(column - getColumn())) > 1) { return false; }
    if ((abs(row - getRow()) > 2)) { return false; }
    //Cannot move diagonal and two space up or down
    if (((abs(row - getRow())) == 2) && (column != getColumn())) { return false; }

    if (this->getColor() == Black)
    {   
        //Black piece must move down only
        if (row < getRow()) { return false; }

        //Check for capture semantics (white piece in row + 1, col +- 1)
        if (row == getRow() + 1 && abs(column - getColumn()) == 1)
        {
            if (board.getPiece(row, column) != nullptr)
            {
                //Already know that the piece isn't the same color so
                return true;
            }
            return false;
        }
        //Check if first move of black pawn   
        if (getRow() == 1)
        {
            //If one space move
            if (row == getRow() + 1)
            {
                //Check for opposite piece at the destination
                if (board.getPiece(row, column) != nullptr)
                {
                    return false;
                }
                return true;
            }
            //Two space move
            else if (row == getRow() + 2)
            {
                //Check for a piece in the way
                if (board.getPiece(getRow() + 1, getColumn()) != nullptr)
                {
                    return false;
                }
                //Check for opposite piece at the destination
                if (board.getPiece(row, column) != nullptr)
                {
                    return false;
                }
                return true;
            }
            //Invalid move
            else { return false; }
        }
        //Not first turn for pawn, or capture semantics
        //Thus move can only be one space down
        if (row == this->getRow() + 1 && column == this->getColumn())
        {
            //Check if there is a white piece blocking (we know there is not a black piece)
            if (board.getPiece(row, column) != nullptr)
            {
                return false;
            }
            return true;
        }
        
    }
    else
    {
        //White piece must move up only
        if (row > getRow()) { return false; }

        //Check for capture semantics (black piece in row - 1, col +- 1)
        if (row == getRow() - 1 && abs(column - getColumn()) == 1)
        {
            //Make sure there is a piece at the position
            if (board.getPiece(row, column) != nullptr)
            {
                //Already know that the piece isn't the same color so
                return true;
            }
            return false;
        }

        //Check if first move of white pawn   
        if (getRow() == board.getNumRows() - 2)
        {
            //If one space move
            if (row == getRow() - 1)
            {
                //Check for opposite piece at the destination
                if (board.getPiece(row, column) != nullptr)
                {
                    return false;
                }
                return true;
            }
            //Two space move
            else if (row == getRow() - 2)
            {

                //Check for a piece in the way
                if (board.getPiece(getRow() - 1, getColumn()) != nullptr)
                {
                    return false;
                }
                //Check for opposite piece at the destination
                if (board.getPiece(row, column) != nullptr)
                {
                    return false;
                }
                return true;
            }
            //Invalid move
            else { return false; }
        }
        //Check if move semantics match row and column (1 space up for white)
        if (row == this->getRow() - 1 && column == this->getColumn())
        {
            //Check if there is a black piece blocking (we know there is not a white piece)
            if (board.getPiece(row, column) != nullptr)
            {
                return false;
            }
            return true;
        }
        
    }

    return false;
}

const char* PawnPiece::toString()
{
    if (getColor() == White)
    {
        return "\u2659";
    }
    else 
    {
        return "\u265F";
    }
}


