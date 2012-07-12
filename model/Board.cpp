//*****************************************************************************
//
// Reference the class description in Board.h.
//
//*****************************************************************************

#include <cstdlib>
#include <new>
#include "Board.h"

namespace BlizzCheckers {

//*****************************************************************************
// PUBLIC CONSTRUCTOR : Board
//*****************************************************************************
Board::Board(void)
{
   // set the board to empty
   for (int i = 0; i < MAX_LENGTH; i++)
   {
      for (int j = 0; j < MAX_WIDTH; j++)
      {
         _board[i][j] = EMPTY_SQUARE;
      }
   }

   // We could do something fancy, like flattening the array and setting every
   // other of the first N spots to BLACK_PIECE, but... KISS.

   // set black pieces
   // first row
   _board[0][1] = BLACK_PIECE;
   _board[0][3] = BLACK_PIECE;
   _board[0][5] = BLACK_PIECE;
   _board[0][7] = BLACK_PIECE;

   // second row
   _board[1][0] = BLACK_PIECE;
   _board[1][2] = BLACK_PIECE;
   _board[1][4] = BLACK_PIECE;
   _board[1][6] = BLACK_PIECE;

   // third row
   _board[2][1] = BLACK_PIECE;
   _board[2][3] = BLACK_PIECE;
   _board[2][5] = BLACK_PIECE;
   _board[2][7] = BLACK_PIECE;

   // set white pieces
   // last row
   _board[7][0] = WHITE_PIECE;
   _board[7][2] = WHITE_PIECE;
   _board[7][4] = WHITE_PIECE;
   _board[7][6] = WHITE_PIECE;

   // second-to-last row
   _board[6][1] = WHITE_PIECE;
   _board[6][3] = WHITE_PIECE;
   _board[6][5] = WHITE_PIECE;
   _board[6][7] = WHITE_PIECE;
   
   // third-to-last row
   _board[5][0] = WHITE_PIECE;
   _board[5][2] = WHITE_PIECE;
   _board[5][4] = WHITE_PIECE;
   _board[5][6] = WHITE_PIECE;
}


//*****************************************************************************
// DESTRUCTOR : Board
//*****************************************************************************
Board::~Board(void)
{
   // nothing to do
}


//*****************************************************************************
// PUBLIC METHOD : at
//*****************************************************************************
Board::BoardToken Board::at(unsigned int row, unsigned int col)
{
   // sanity check!
   if ((row >= MAX_LENGTH) || (col >= MAX_WIDTH))
   {
      return INVALID_TOKEN;
   }

   // since we're sane, return the value
   return _board[row][col];
}


} // end namespace BlizzCheckers

