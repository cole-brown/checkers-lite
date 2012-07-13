//*****************************************************************************
//
// Reference the class description in Board.h.
//
//*****************************************************************************

#include <cstdlib>
#include <new>
#include <iostream> //! TODO remove this
#include "Board.h"

using namespace std; //! TODO remove this

namespace BlizzCheckers {

//*****************************************************************************
// PUBLIC CONSTRUCTOR : Board
//*****************************************************************************
Board::Board(void):
   _startRow(MAX_LENGTH),
   _startCol(MAX_WIDTH),
   _endRow(MAX_LENGTH),
   _endCol(MAX_WIDTH),
   _mover(INVALID_TOKEN),
   _lastMove(INVALID_MOVER)
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


//*****************************************************************************
// PUBLIC METHOD : move
//*****************************************************************************
Board* Board::move(BoardToken mover, unsigned int row, unsigned int col)
{
   // save the info
   _mover   = mover;
   _startRow = row;
   _startCol = col;

   // return this so the function can be chained
   return this;
}


//*****************************************************************************
// PUBLIC METHOD : to
//*****************************************************************************
bool Board::to(unsigned int row, unsigned int col)
{
   //! TODO remove couts

   // save off where they're trying to move to
   _endRow = row;
   _endCol = col;

   // basic checks first...
   if ((_mover != BLACK_PIECE) && (_mover != WHITE_PIECE))
   {
      _lastMove = INVALID_MOVER;
      cout << "INVALID_MOVER" << endl;
      return false;
   }
   // boundry check
   if ((_startRow >= MAX_LENGTH) ||
       (_startCol >= MAX_WIDTH)  ||
       (_startRow >= MAX_LENGTH) ||
       (_startCol >= MAX_WIDTH))
   {
      _lastMove = OUT_OF_BOUNDS;
      cout << "OUT_OF_BOUNDS" << endl;
      return false;      
   }

   // did mover select their right piece?
   BoardToken pieceToMove = at(_startRow, _startCol);
   if (pieceToMove != _mover)
   {
      if (pieceToMove == EMPTY_SQUARE)
      {
         _lastMove = EMPTY_START;
         cout << "EMPTY_START" << endl;
      }
      else
      {
         _lastMove = ENEMY_START;
         cout << "ENEMY_START" << endl;
      }

      return false;
   }

   // is the specified square the right direction
   if ((_mover == BLACK_PIECE) && !(_startRow < row))
   {
      _lastMove = WRONG_DIRECTION;
      cout << "WRONG_DIRECTION BLACK" << endl;
      return false;
   }
   if ((_mover == WHITE_PIECE) && !(_startRow > row))
   {
      _lastMove = WRONG_DIRECTION;
      cout << "WRONG_DIRECTION WHITE" << endl;
      return false;
   }

   // Row & column distances should be exactly the same, since moves
   // are always along diagonals.
   int rowDist = abs((int)row - (int)_startRow);
   int colDist = abs((int)col - (int)_startCol);
   if (rowDist != colDist) // row/col dist differ (non-diagonal move)
   {
      _lastMove = BAD_MOVE_DIAG;
      cout << "BAD_MOVE_DIAG" << endl;
      return false;
   }

   // Allowed distances are 1 (a move) or 2 (a jump).
   if (!((rowDist == 1) || (rowDist == 2)) || // row dist not 1 or 2
       !((rowDist == 1) || (rowDist == 2)))   // col dist not 1 or 2
   {
      _lastMove = BAD_MOVE_DIST;
      cout << "BAD_MOVE_DIST" << endl;
      return false;
   }

   // can they move to the specified square?
   BoardToken toLocation = at(row, col);
   BoardToken enemy = (_mover == BLACK_PIECE) ? WHITE_PIECE : BLACK_PIECE;
   if (toLocation == _mover)
   {
      // nope, they already have a piece there...
      _lastMove = OCCUPIED_SELF;
      cout << "OCCUPIED_SELF" << endl;
      return false;
   }
   if (toLocation == enemy)
   {
      // nope, the bad guy's got his piece there...
      _lastMove = OCCUPIED_ENEMY;
      cout << "OCCUPIED_ENEMY" << endl;
      return false;
   }

   // Is it a jump?
   unsigned int jumpedRow;
   unsigned int jumpedCol;
   if (rowDist == 2)
   {
      // figure out the jumped square's location
      int rowVec = (int)row - (int)_startRow; // magnitude & direction of jump
      int colVec = (int)col - (int)_startCol;
      // +1 to destination if negative jump vector
      // or -1 to destination for positive jump vector
      jumpedRow = row + ((rowVec < 0) ? -1 : 1); 
      jumpedCol = col + ((colVec < 0) ? -1 : 1);

      cout << "jump from " << _startRow << "," << _startCol
           << " to " << row << "," << col
           << " will jump " << jumpedRow << "," << jumpedCol << endl;

      // Did they actually jump an opponent's piece?
      if (at(jumpedRow, jumpedCol) != enemy)
      {
         _lastMove = JUMPED_NON_ENEMY;
         cout << "JUMPED_NON_ENEMY" << endl;
         return false;
      }
   }

   //***
   // ALRIGHT! We're ready to actually do something!
   //***

   // move the piece
   _board[row][col] = _mover;
   _board[_startRow][_startCol] = EMPTY_SQUARE;

   // remove the jumped piece if it's a jump
   if (rowDist == 2)
   {
      _board[jumpedRow][jumpedCol] = EMPTY_SQUARE;
   }

   return true;
}




} // end namespace BlizzCheckers

