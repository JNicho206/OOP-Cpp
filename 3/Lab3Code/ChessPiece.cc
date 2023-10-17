#include "ChessPiece.hh"

using Student::ChessPiece;

ChessPiece::ChessPiece(ChessBoard &board, Color color, int row, int column)
    : board(board), color(color), row(row), column(column)
{

}

Color ChessPiece::getColor()
{
    return color;
}

int ChessPiece::getRow()
{
    return row;
}

int ChessPiece::getColumn()
{
    return column;
}

bool ChessPiece::isMoveOnBoard(int row, int column)
{
    return row >= 0 && row < board.getNumRows() && column >= 0 && column < board.getNumCols();
}

bool ChessPiece::isMoveToSameSpot(int row, int column)
{
    return row == this->getRow() && column == this->getColumn();
}

bool ChessPiece::isMoveToSameColor(int row, int column)
{
    return board.getPiece(row, column) != nullptr && board.getPiece(row, column)->getColor() == this->getColor();
}

void ChessPiece::setPosition(int row, int column)
{
    this->row = row;
    this->column = column;
}

