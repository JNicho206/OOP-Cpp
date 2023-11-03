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
        board.at(startRow).at(startColumn) = new KingPiece(*this, color, startRow, startColumn);
        break;
    default:
        break;
    }


}


//Called only by test boards
bool ChessBoard::kingIsSecure(Color pieceColor)
{   
    //Find the king of the correct color
    ChessPiece* k = nullptr;
    for (int row = 0; row < getNumRows(); row++)
    {
        for (int col = 0; col < getNumCols(); col++)
        {
            ChessPiece* p = board.at(row).at(col);
            if (p != nullptr)
            {  
                //If piece is a king
                if (p->getType() == King && p->getColor() == pieceColor) 
                { 
                    k = p;
                    break;
                }
            }
        }
        if (k != nullptr)
        {
            break;
        }
    }

    //Check if king is under threat without isPieceUnderThreat()
    //because that will loop back into here (isPieceUnderThreat->isvalidmove->kingsWouldBeSecure->kingIsSecure->isPieceUnderThreat)
    for (int row = 0; row < getNumRows(); row++)
    {
        for (int col = 0; col < getNumCols(); col++)
        {
            //Check if piece can move to the king's spot
            if (getPiece(row,col) != nullptr && 
                getPiece(row,col)->canMoveToLocation(k->getRow(), k->getColumn())) 
            { return false; }
        }
    }
    return true;

}

bool ChessBoard::kingWouldBeSecure(int fromRow, int fromColumn, int toRow, int toColumn)
{
    // Part 3
    // For this function we know the piece can move to the location
    // Create a copy of the board, move the piece, and check if the king (of the color of the piece to move) is in check

    //Create a copy
    ChessBoard testBoard(numRows, numCols);
    testBoard.turn = this->turn;
    //for each row (vector<ChessPiece*>)
    //Populate the test board based on the main board
    for (int row = 0; row < getNumRows(); row++)
    {
        //for each space in the row (ChessPiece*)
        for (int col = 0; col < getNumCols(); col++)
        {
            //Create piece on new board
            ChessPiece* p = board.at(row).at(col);
            if (p != nullptr) 
            {
                testBoard.createChessPiece(p->getColor(), p->getType(), row, col);
            }
        }
    }

    //Can't use below line it will keep creating test boards (movePiece->isvalidmove->kingsWouldBeSecure->movePiece->....) 
    //testBoard.movePiece(fromRow, fromColumn, toRow, toColumn);
    //We know the piece can move to the location

    //Handle piece existing at the move location on the test board
    ChessPiece* p = testBoard.getPiece(toRow, toColumn);
    if (p != nullptr)
    {
        delete p;
        testBoard.board.at(toRow).at(toColumn) = nullptr;
    }
    //Move the piece on the test board
    ChessPiece* piece = testBoard.getPiece(fromRow, fromColumn);
    piece->setPosition(toRow, toColumn);
    testBoard.board.at(toRow).at(toColumn) = piece;
    testBoard.board.at(fromRow).at(fromColumn) = nullptr;
    
    //Check if the test board has the king (of the same color as the piece to move) not in check (meaning main board move would be fine)
    return testBoard.kingIsSecure(piece->getColor());
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
            // isValidMove could return false if the king would be in check even though the piece could move
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

    //Check if there is a piece to capture
    if (board.at(toRow).at(toColumn) != nullptr)
    {
        //Remove piece from board
        delete board.at(toRow).at(toColumn);
        board.at(toRow).at(toColumn) = nullptr;
    }

    //Move piece to new location
    ChessPiece *piece = board.at(fromRow).at(fromColumn);
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
