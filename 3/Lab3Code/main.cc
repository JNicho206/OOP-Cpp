#include <assert.h>
#include "Chess.h"
#include "ChessBoard.hh"
#include "ChessPiece.hh"
#include <iostream>

void test_part1_4x4_1()
{
    // Config file content:
    // 0
    // 4 4
    // w r 3 2
    // b b 1 3
    // b r 1 1
    // w r 2 3
    // ~
    // isValidScan

    // Corresponding code
    Student::ChessBoard sBoard(4, 4);
    sBoard.createChessPiece(White, Rook, 3, 2);
    sBoard.createChessPiece(Black, Bishop, 1, 3);
    sBoard.createChessPiece(Black, Rook, 1, 1);
    sBoard.createChessPiece(White, Rook, 2, 3);

    // Calls isValidMove() from every position to every
    // other position on the chess board for all pieces.

    return;
}

void test_part1_4x4_5()
{
    // 0
    // 4 4
    // b b 0 1
    // b b 1 1
    // b b 2 1
    // w p 2 0
    // ~
    // isValidScan


    // Corresponding code
    Student::ChessBoard sBoard(4, 4);
    sBoard.createChessPiece(Black, Bishop, 0, 1);
    sBoard.createChessPiece(Black, Bishop, 1, 1);
    sBoard.createChessPiece(Black, Bishop, 2, 1);
    sBoard.createChessPiece(White, Pawn, 2, 0);

    // Calls isValidMove() from every position to every
    // other position on the chess board for all pieces.
    sBoard.displayBoard();
    printf("\n");
    for (int r = 0; r < 4; r++)
    {
        for (int c = 0; c < 4; c++)
        {
            if ((sBoard.getPiece(r,c)) != nullptr)
            {
                for (int r2 = 0; r2 < 4; r2++)
                {
                    for (int c2 = 0; c2 < 4; c2++)
                    {
                        if (sBoard.isValidMove(r,c,r2,c2))
                        {
                            printf("%s at (%d,%d) can move to (%d,%d)\n", sBoard.getPiece(r,c)->toString(), r, c, r2, c2);
                        }
                    }
                }
            }
        }
    }

    return;
}

void test_part1_6x6_2()
{
    
    // 0
    // 6 6
    // b r 2 2
    // w b 1 1
    // w b 0 0
    // w r 1 4
    // w p 3 3
    // b p 2 1
    // ~
    // isValidScan

    // Corresponding code
    Student::ChessBoard sBoard(6, 6);
    sBoard.createChessPiece(Black, Rook, 2, 2);
    sBoard.createChessPiece(White, Bishop, 1, 1);
    sBoard.createChessPiece(White, Bishop, 0, 0);
    sBoard.createChessPiece(White, Rook, 1, 4);
    sBoard.createChessPiece(White, Pawn, 3, 3);
    sBoard.createChessPiece(Black, Pawn, 2, 1);

    // Calls isValidMove() from every position to every
    // other position on the chess board for all pieces.
    //std::cout << sBoard.displayBoard() << std::endl;
    printf("\n");
    for (int r = 0; r < 6; r++)
    {
        for (int c = 0; c < 6; c++)
        {
            if ((sBoard.getPiece(r,c)) != nullptr)
            {
                for (int r2 = 0; r2 < 6; r2++)
                {
                    for (int c2 = 0; c2 < 6; c2++)
                    {
                        if (sBoard.isValidMove(r,c,r2,c2))
                        {
                            printf("%s at (%d,%d) can move to (%d,%d)\n", sBoard.getPiece(r,c)->toString(), r, c, r2, c2);
                        }
                    }
                }
            }
        }
    }

    return;
}

void test_part2_4x4_1_threatscan()
{
    //0
    // 4 4
    // w r 3 2
    // b b 1 3
    // b r 1 1
    // w r 2 3
    // ~
    // isValidScan
    // underThreatScan


    // Corresponding code
    Student::ChessBoard sBoard(4, 4);
    sBoard.createChessPiece(White, Rook, 3, 2);
    sBoard.createChessPiece(Black, Bishop, 1, 3);
    sBoard.createChessPiece(Black, Rook, 1, 1);
    sBoard.createChessPiece(White, Rook, 2, 3);

    // Calls isValidMove() from every position to every
    // other position on the chess board for all pieces.
    sBoard.displayBoard();
    printf("\n");
    for (int r = 0; r < 4; r++)
    {
        for (int c = 0; c < 4; c++)
        {
            
        }
    }

    return;
}

void test_part3_4x4_1()
{
    // 0
    // 4 4
    // w r 3 2
    // b b 1 3
    // b r 1 1
    // w r 2 3
    // b k 0 0
    // w k 3 0


    // Corresponding code
    Student::ChessBoard sBoard(4, 4);
    sBoard.createChessPiece(White, Rook, 3, 2);
    sBoard.createChessPiece(Black, Bishop, 1, 3);
    sBoard.createChessPiece(Black, Rook, 1, 1);
    sBoard.createChessPiece(White, Rook, 2, 3);
    sBoard.createChessPiece(Black, King, 0, 0);
    sBoard.createChessPiece(White, King, 3, 0);

    // Calls isValidMove() from every position to every
    // other position on the chess board for all pieces.
    sBoard.displayBoard();
    printf("\n");
    for (int r = 0; r < 4; r++)
    {
        for (int c = 0; c < 4; c++)
        {
            if ((sBoard.getPiece(r,c)) != nullptr)
            {
                for (int r2 = 0; r2 < 4; r2++)
                {
                    for (int c2 = 0; c2 < 4; c2++)
                    {
                        if (sBoard.isValidMove(r,c,r2,c2))
                        {
                            printf("%s at (%d,%d) can move to (%d,%d)\n", sBoard.getPiece(r,c)->toString(), r, c, r2, c2);
                        }
                    }
                }
            }
        }
    }

    return;
}


int main()
{
    test_part3_4x4_1();
    return EXIT_SUCCESS;
}
