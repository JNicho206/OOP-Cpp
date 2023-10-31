#include "ChessBoard.hh"
#include "PawnPiece.hh"
#include "RookPiece.hh"
#include "BishopPiece.hh"
#include "KingPiece.hh"
#include <vector>

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

ChessBoard::ChessBoard(const ChessBoard &other)
 : numRows(other.numRows), numCols(other.numCols), turn(other.turn)
{
    board = std::vector<std::vector<ChessPiece *>>(numRows, std::vector<ChessPiece *>(numCols, nullptr));
    //vector<ChessPiece*>
    for (int row = 0; row < board.size(); row++)
    {
        //ChessPiece*
        for (int col = 0; col < board.at(row).size(); col++)
        {
            //Need to overload createChessPiece to take a chesspiece*
            //Create piece on new board
            //ChessPiece* p = other.board.at(row).at(col);
            //if (p != nullptr) 
            //board.at(row).at(col) = createChessPiece(p.getColor(), p.getType(), row, col);
        }
    }
}

bool ChessBoard::kingsAreSecure()
{
    for (int row = 0; row < board.size(); row++)
    {
        for (int col = 0; col < board.at(row).size(); col++)
        {
            ChessPiece* p = board.at(row).at(col);
            if (p != nullptr)
            {
                if (p->getType() == King) 
                { 
                    if (isPieceUnderThreat(row, col))
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool ChessBoard::kingWouldBeSecure(int fromRow, int fromColumn, int toRow, int toColumn)
{
    // Part 3
    // For this function we know the piece can move to the location
    // Create a copy of the board, move the piece, and check if the king is in check
    ChessBoard testBoard(*this);
    testBoard.movePiece(fromRow, fromColumn, toRow, toColumn);
    
    return kingsAreSecure();
}

//PART 1
bool ChessBoard::isValidMove(int fromRow, int fromColumn, int toRow, int toColumn)
{
    //This is fixed for part 3
    if (board.at(fromRow).at(fromColumn) == nullptr) {return false;}

    return (board.at(fromRow).at(fromColumn)->canMoveToLocation(toRow, toColumn) && kingWouldBeSecure(fromRow, fromColumn, toRow, toColumn));
}

//PART 2+
bool ChessBoard::isPieceUnderThreat(int row, int column)
{
    if (board.at(row).at(column) == nullptr) return false;
    for (int r = 0; r < getNumRows(); r++)
    {
        for (int c = 0; c < getNumCols(); c++)
        {
            if (isValidMove(r,c,row,column))
            {
                return true;
            }
            // Part 3
            // isValidMove could return false if the king would be in check
            // Need to check still if the piece is under threat
            if (board.at(r).at(c) != nullptr)
            {
                if (board.at(r).at(c)->canMoveToLocation(row, column)) { return true; }
            }
        }
    }
    return false;
}

//PART 2+
bool ChessBoard::movePiece(int fromRow, int fromColumn, int toRow, int toColumn)
{
    if (!isValidMove(fromRow, fromColumn, toRow, toColumn)) return false;
    if (board.at(fromRow).at(fromColumn)->getColor() != turn) return false;

    //Move piece to new location
    
    ChessPiece *piece = board.at(fromRow).at(fromColumn);

    //Check if there is a piece to capture
    if (board.at(toRow).at(toColumn) != nullptr)
    {
        //Remove piece from board
        delete board.at(toRow).at(toColumn);
        board.at(toRow).at(toColumn) = nullptr;
    }

    piece->setPosition(toRow, toColumn);
    board.at(toRow).at(toColumn) = piece;
    board.at(fromRow).at(fromColumn) = nullptr;

    if (turn == White)
    {
        turn = Black;
    }
    else 
    {
        turn = White;
    }

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
