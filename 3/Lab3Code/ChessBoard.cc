#include "ChessBoard.hh"
#include "PawnPiece.hh"
#include "RookPiece.hh"
#include "BishopPiece.hh"
#include "KingPiece.hh"

using Student::ChessBoard;

ChessBoard::ChessBoard(int numRow, int numCol) : numRows(numRow), numCols(numCol)
{
    // Allocate memory for the board and initialise all pointers to nullptr.
    board = std::vector<std::vector<ChessPiece *>>(numRows, std::vector<ChessPiece *>(numCols, nullptr));
}

ChessBoard::~ChessBoard()
{
    // Free memory allocated for the board.
    for (int row = 0; row < numRows; row++)
    {
        for (int column = 0; column < numCols; column++)
        {
            if (board.at(row).at(column) != nullptr)
            {
                delete board.at(row).at(column);
            }
        }
    }

    // Clear the elements of the board vector
    for (int row = 0; row < numRows; row++) {
        board.at(row).clear();
    }

    // Clear the board vector itself
    board.clear();
}

//PART 1
void ChessBoard::createChessPiece(Color color, Type ty, int startRow, int startColumn)
{
    if (startRow < 0 || startRow >= numRows || startColumn < 0 || startColumn >= numCols) 
    { 
        #ifdef DEBUG
        perror("\nPosition not on board when creating chess piece.\n")
        #endif
        return;
    }
    
    //Remove any existing piece first before adding the new piece.
    if (board.at(startRow).at(startColumn) != nullptr)
    {
        delete board.at(startRow).at(startColumn);
        board.at(startRow).at(startColumn) = nullptr;
    }

    //Create new piece
    switch (ty)
    {
    case Pawn:
        board.at(startRow).at(startColumn) = new PawnPiece(*this, color, startRow, startColumn);
        break;
    case Rook:
        board.at(startRow).at(startColumn) = new RookPiece(*this, color, startRow, startColumn);
        break;
    case Bishop:
        board.at(startRow).at(startColumn) = new BishopPiece(*this, color, startRow, startColumn);
        break;
    case King:
        //board.at(startRow).at(startColumn) = new KingPiece(*this, color, startRow, startColumn);
        break;
    default:
        break;
    }


}

//PART 1
bool ChessBoard::isValidMove(int fromRow, int fromColumn, int toRow, int toColumn)
{
    if (board.at(fromRow).at(fromColumn) == nullptr) {return false;}

    return (board.at(fromRow).at(fromColumn)->canMoveToLocation(toRow, toColumn));
}

//PART 2+
bool ChessBoard::isPieceUnderThreat(int row, int column)
{
    return false;
}

//PART 2+
bool ChessBoard::movePiece(int fromRow, int fromColumn, int toRow, int toColumn)
{
    //Check if move is valid
    if (isValidMove(fromRow, fromColumn, toRow, toColumn)) return false;

    //Move piece to new location
    
    ChessPiece *piece = board.at(fromRow).at(fromColumn);
    //Check if there is a piece to capture
    if (board.at(toRow).at(toColumn) != nullptr)
    {
        //Remove piece from board
        delete board.at(toRow).at(toColumn);
    }

    board.at(toRow).at(toColumn) = piece;
    board.at(fromRow).at(fromColumn) = nullptr;
    return true;
}


std::ostringstream ChessBoard::displayBoard()
{
    std::ostringstream outputString;
    // top scale
    outputString << "  ";
    for (int i = 0; i < numCols; i++)
    {
        outputString << i;
    }
    outputString << std::endl
                 << "  ";
    // top border
    for (int i = 0; i < numCols; i++)
    {
        outputString << "-";
    }
    outputString << std::endl;

    for (int row = 0; row < numRows; row++)
    {
        outputString << row << "|";
        for (int column = 0; column < numCols; column++)
        {
            ChessPiece *piece = board.at(row).at(column);
            outputString << (piece == nullptr ? " " : piece->toString());
        }
        outputString << "|" << std::endl;
    }

    // bottom border
    outputString << "  ";
    for (int i = 0; i < numCols; i++)
    {
        outputString << "-";
    }
    outputString << std::endl
                 << std::endl;

    return outputString;
}
