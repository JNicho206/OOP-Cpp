#include "RookPiece.hh"


using namespace Student;

RookPiece::RookPiece(ChessBoard &board, Color color, int row, int column) : ChessPiece(board, color, row, column)
{

}

bool RookPiece::canMoveToLocation(int row, int column)
{
    //Handle move attempts to out of bounds locations
    if (!(isMoveOnBoard(row, column))) return false;

    //Handle move attempts to the same location
    if (isMoveToSameSpot(row, column)) return false;

    //Check if there is a piece of the same color in the way
    if (isMoveToSameSpot(row, column)) return false;

    
    //Color doesn't matter for this, only starting spot and destination
    //Check if move is horizontal or vertical
    if (getRow() == row || getColumn() == column)
    {
        //Check if there are pieces in the way
        if (getRow() == row)
        {
            int columnDirection = (column - getColumn()) / abs(column - getColumn());

            for (int i = 1; i < abs(column - getColumn()); i++)
            {
                if (board.getPiece(getRow(), getColumn() + i * columnDirection) != nullptr)
                {
                    return false;
                }
            }
        }
        else
        {
            int rowDirection = (row - getRow()) / abs(row - getRow());

            for (int i = 1; i < abs(row - getRow()); i++)
            {
                if (board.getPiece(getRow() + i * rowDirection, getColumn()) != nullptr)
                {
                    return false;
                }
            }
        }

        return true;
    }
    return false;
}

const char* RookPiece::toString()
{
    return "P";
}