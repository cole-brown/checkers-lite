//*****************************************************************************
//
// Reference the class description in Board.h.
//
//*****************************************************************************

#include <cstdlib>
#include <new>
#include <vector>
#include <iostream> //! TODO remove this
#include "Board.h"

using namespace std;

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

   // initialize info structure with invalid values
   _info._startRow = MAX_LENGTH;
   _info._startCol = MAX_WIDTH;
   _info._endRow   = MAX_LENGTH;
   _info._endCol   = MAX_WIDTH;
   _info._mover    = INVALID_TOKEN;
   _info._lastMove = INVALID_MOVER;
}


//*****************************************************************************
// DESTRUCTOR : Board
//*****************************************************************************
Board::~Board(void)
{
   // nothing to do
}


//*****************************************************************************
// PUBLIC METHOD : turnPossible
//*****************************************************************************
bool Board::turnPossible(BoardToken player, std::vector<BoardPos>* moves)
{
   bool retVal = false;

   // sanity
   if ((player != BLACK_PIECE) && (player != WHITE_PIECE))
   {
      // it ain't possible for empty squares and invalid players to take turns.
      return false;
   }

   BoardToken enemy = (player == BLACK_PIECE) ? WHITE_PIECE : BLACK_PIECE;

   //! TODO remove couts

   // search the board for pieces
   vector<BoardPos> pieces; // all pieces
   vector<BoardPos> movablePieces; // pieces that have normal moves available
   vector<BoardPos> jumpPieces; // pieces that have jump moves available
   for (int i = 0; i < MAX_LENGTH; i++)
   {
      for (int j = 0; j < MAX_WIDTH; j++)
      {
         // save off if it's the player's piece
         if (at(i,j) == player)
         {
            pieces.push_back(BoardPos(i,j));
         }
      }
   }

   // check each piece for possible moves
   int rowMoveDir = (player == BLACK_PIECE) ? MOVE_DIR_BLACK : MOVE_DIR_WHITE;
   for (vector<BoardPos>::iterator it = pieces.begin(); it < pieces.end(); it++)
   {
      // check left diagonal (let at() do bounds checking)
      unsigned int toRow = it->_row + rowMoveDir;
      unsigned int toCol = it->_col - 1;
      BoardToken checkSquare = at(toRow, toCol);
      if (checkSquare == EMPTY_SQUARE)
      {
         cout << it->_row << "," << it->_col << " can go lefty." << endl;
         movablePieces.push_back(BoardPos(it->_row,
                                          it->_col,
                                          toRow,
                                          toCol));
         retVal = true;
      }
      else if (checkSquare == enemy)
      {
         // check jumpability
         toRow += rowMoveDir;
         toCol -= 1;
         if (at(toRow, toCol) == EMPTY_SQUARE)
         {
            cout << it->_row << "," << it->_col << " can jump left!" << endl;
            jumpPieces.push_back(BoardPos(it->_row,
                                          it->_col,
                                          toRow,
                                          toCol));
            retVal = true;
         }
      }

      // check right diagonal
      toRow = it->_row + rowMoveDir;
      toCol = it->_col + 1;
      checkSquare = at(toRow, toCol);
      if (checkSquare == EMPTY_SQUARE)
      {
         cout << it->_row << "," << it->_col << " can go righty." << endl;
         movablePieces.push_back(BoardPos(it->_row,
                                          it->_col,
                                          toRow,
                                          toCol));
         retVal = true;
      }
      else if (checkSquare == enemy)
      {
         // check jumpability
         toRow += rowMoveDir;
         toCol += 1;
         if (at(toRow, toCol) == EMPTY_SQUARE)
         {
            cout << it->_row << "," << it->_col << " can jump right!" << endl;
            jumpPieces.push_back(BoardPos(it->_row,
                                          it->_col,
                                          toRow,
                                          toCol));
            retVal = true;
         }
      }
   }

   // does the caller want the moves list?
   if (retVal && (moves != NULL))
   {
      if (jumpPieces.size() > 0)
      {
         *moves = jumpPieces;
      }
      else
      {
         *moves = movablePieces;
      }
   }

   return retVal;
}


//*****************************************************************************
// PUBLIC METHOD : state
//*****************************************************************************
Board::GameState Board::state(void)
{
   // check for a win
   bool whiteExists = false;
   bool blackExists = false;
   for (int i = 0; i < MAX_LENGTH; i++)
   {
      for (int j = 0; j < MAX_WIDTH; j++)
      {
         // look for pieces
         if (at(i,j) == BLACK_PIECE)
         {
            blackExists = true;
         }
         else if (at(i,j) == WHITE_PIECE)
         {
            whiteExists = true;
         }
      }
   }

   if (!whiteExists)
   {
      return BLACK_WIN_STATE;
   }
   if (!blackExists)
   {
      return WHITE_WIN_STATE;
   }

   // check for a stalemate
   bool whiteCanPlay = turnPossible(WHITE_PIECE);
   bool blackCanPlay = turnPossible(BLACK_PIECE);
   if (!whiteCanPlay && !blackCanPlay)
   {
      return STALEMATE;
   }
   // other possible states
   else if (whiteCanPlay && !blackCanPlay)
   {
      return ONLY_WHITE_PLAYABLE;
   }
   else if (!whiteCanPlay && blackCanPlay)
   {
      return ONLY_BLACK_PLAYABLE;
   }

   // last possibility
   return GAME_PLAYABLE;
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
   _info._mover   = mover;
   _info._startRow = row;
   _info._startCol = col;

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
   _info._endRow = row;
   _info._endCol = col;

   // basic checks first...
   if ((_info._mover != BLACK_PIECE) && (_info._mover != WHITE_PIECE))
   {
      _info._lastMove = INVALID_MOVER;
      cout << "INVALID_MOVER" << endl;
      return false;
   }
   // boundry check
   if ((_info._startRow >= MAX_LENGTH) ||
       (_info._startCol >= MAX_WIDTH)  ||
       (_info._startRow >= MAX_LENGTH) ||
       (_info._startCol >= MAX_WIDTH))
   {
      _info._lastMove = OUT_OF_BOUNDS;
      cout << "OUT_OF_BOUNDS" << endl;
      return false;      
   }

   // did mover select their right piece?
   BoardToken pieceToMove = at(_info._startRow, _info._startCol);
   if (pieceToMove != _info._mover)
   {
      if (pieceToMove == EMPTY_SQUARE)
      {
         _info._lastMove = EMPTY_START;
         cout << "EMPTY_START" << endl;
      }
      else
      {
         _info._lastMove = ENEMY_START;
         cout << "ENEMY_START" << endl;
      }

      return false;
   }

   // is the specified square the right direction
   if ((_info._mover == BLACK_PIECE) && !(_info._startRow < row))
   {
      _info._lastMove = WRONG_DIRECTION;
      cout << "WRONG_DIRECTION BLACK" << endl;
      return false;
   }
   if ((_info._mover == WHITE_PIECE) && !(_info._startRow > row))
   {
      _info._lastMove = WRONG_DIRECTION;
      cout << "WRONG_DIRECTION WHITE" << endl;
      return false;
   }

   // Row & column distances should be exactly the same, since moves
   // are always along diagonals.
   int rowDist = abs((int)row - (int)_info._startRow);
   int colDist = abs((int)col - (int)_info._startCol);
   if (rowDist != colDist) // row/col dist differ (non-diagonal move)
   {
      _info._lastMove = BAD_MOVE_DIAG;
      cout << "BAD_MOVE_DIAG" << endl;
      return false;
   }

   // Allowed distances are 1 (a move) or 2 (a jump).
   if (!((rowDist == 1) || (rowDist == 2)) || // row dist not 1 or 2
       !((rowDist == 1) || (rowDist == 2)))   // col dist not 1 or 2
   {
      _info._lastMove = BAD_MOVE_DIST;
      cout << "BAD_MOVE_DIST" << endl;
      return false;
   }

   // can they move to the specified square?
   BoardToken toLocation = at(row, col);
   BoardToken enemy = (_info._mover == BLACK_PIECE) ? WHITE_PIECE : BLACK_PIECE;
   if (toLocation == _info._mover)
   {
      // nope, they already have a piece there...
      _info._lastMove = OCCUPIED_SELF;
      cout << "OCCUPIED_SELF" << endl;
      return false;
   }
   if (toLocation == enemy)
   {
      // nope, the bad guy's got his piece there...
      _info._lastMove = OCCUPIED_ENEMY;
      cout << "OCCUPIED_ENEMY" << endl;
      return false;
   }

   // Is it a jump?
   unsigned int jumpedRow;
   unsigned int jumpedCol;
   if (rowDist == 2)
   {
      // figure out the jumped square's location
      int rowVec = (int)row - (int)_info._startRow; // magnitude & direction
      int colVec = (int)col - (int)_info._startCol; // of jump
      // +1 to destination if negative jump vector
      // or -1 to destination for positive jump vector
      jumpedRow = row + ((rowVec < 0) ? -1 : 1); 
      jumpedCol = col + ((colVec < 0) ? -1 : 1);

      cout << "jump from " << _info._startRow << "," << _info._startCol
           << " to " << row << "," << col
           << " will jump " << jumpedRow << "," << jumpedCol << endl;

      // Did they actually jump an opponent's piece?
      if (at(jumpedRow, jumpedCol) != enemy)
      {
         _info._lastMove = JUMPED_NON_ENEMY;
         cout << "JUMPED_NON_ENEMY" << endl;
         return false;
      }
   }

   //***
   // ALRIGHT! We're ready to actually do something!
   //***

   // move the piece
   _board[row][col] = _info._mover;
   _board[_info._startRow][_info._startCol] = EMPTY_SQUARE;
   _info._lastMove = MOVE;

   // remove the jumped piece if it's a jump
   if (rowDist == 2)
   {
      _board[jumpedRow][jumpedCol] = EMPTY_SQUARE;
      _info._lastMove = JUMP;
   }

   return true;
}




} // end namespace BlizzCheckers

