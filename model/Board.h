//******************************************************************************
//
// The Board class contains a model of the checkers board and the pieces on it.
// 
//*****************************************************************************
#ifndef BOARD_H
#define BOARD_H

// #include "something.h"

namespace BlizzCheckers {

class Board
{
public:
   //**************************************************************************
   // Public Constants
   //**************************************************************************

   // Possible values for each location on the checkers board.
   // Note: This checkers has no kings.
   enum BoardToken
   {
      INVALID_TOKEN = -1,
      EMPTY_SQUARE  = 0,
      BLACK_PIECE   = 1,
      WHITE_PIECE   = 2
   };

   // misc constants
   enum {
     // American Checkers boards are 8x8 squares
     MAX_WIDTH  = 8,
     MAX_LENGTH = MAX_WIDTH,

     // players start with 12 pieces
     MAX_PIECES = 12,

     // directions of movement:
     // black moves down the board, so each move adds (at least) one to the column
     MOVE_DIR_BLACK = 1,
     // white moves up the board, so each move subtracts (at least) one
     MOVE_DIR_WHITE = -1
   };

   enum MoveType
   {
     MOVE = 0,
     JUMP,
     OUT_OF_BOUNDS,
     INVALID_MOVER, // mover must be WHITE_PIECE or BLACK_PIECE
     EMPTY_START, // selected a blank square as the starting location
     ENEMY_START, // the selected start location has the opponent's piece
     WRONG_DIRECTION, // didn't go in the direction indicated by MOVE_DIR_<color>
     BAD_MOVE_DIAG, // non-diagonal move
     BAD_MOVE_DIST, // move isn't proper length
     OCCUPIED_ENEMY, // end spot is occupied by the opponent and can't be jumped
     OCCUPIED_SELF,  // no piggy back rides allowed
     JUMPED_NON_ENEMY // only allowed to jump over your opponent's pieces
   };


   //**************************************************************************
   // Public Methods
   //**************************************************************************

   //-----------------------------------------------------------------------
   // This is the only constructor.  Its primary purpose is to 
   // initialize class configuration variables.
   //
   // Inputs:
   //    None
   //
   // Outputs: 
   //    Nothing
   //
   // Exceptions:
   //    None - Nothing
   //-----------------------------------------------------------------------
   Board(void);

   //-----------------------------------------------------------------------
   // Destructor
   //-----------------------------------------------------------------------
   virtual ~Board(void);

   //-----------------------------------------------------------------------
   // Returns the board token at the supplied row & column. Gives INVALID_TOKEN
   // if row or column is out of bounds.
   //
   // Inputs:
   //    row - row coordinate
   //    col - column coordinate
   //
   // Outputs: 
   //    BoardToken - token at row,col or INVALID_TOKEN
   //
   // Exceptions:
   //    None - Nothing
   //-----------------------------------------------------------------------
   BoardToken at(unsigned int row, unsigned int col);

   //-----------------------------------------------------------------------
   // Selects piece to be moved. Returns this pointer so it can be chained
   // with to(). e.g. board->move(x,y)->to(newX,newY)
   //
   // Inputs:
   //    mover - color of mover's pieces: BLACK_PIECE or WHITE_PIECE
   //    row - row of piece to be moved
   //    col - column of piece to be moved
   //
   // Outputs: 
   //    Board* - this
   //
   // Exceptions:
   //    None - Nothing
   //-----------------------------------------------------------------------
   Board* move(BoardToken mover, unsigned int row, unsigned int col);

   //-----------------------------------------------------------------------
   // Attempts to move piece selected by move() to location specified by
   // parameters. Check return value for success. Check moveInfo() for details.
   //
   // Inputs:
   //    row - row of piece to be moved
   //    col - column of piece to be moved
   //
   // Outputs: 
   //    bool - true for a successful move, false for failure
   //
   // Exceptions:
   //    None - Nothing
   //-----------------------------------------------------------------------
   bool to(unsigned int row, unsigned int col);
   

protected:
   //**************************************************************************
   // Protected Methods
   //**************************************************************************
   //! TODO - anything protected?

private:
   //**************************************************************************
   // Private Constants
   //**************************************************************************
   //! TODO - any consts?

   //**************************************************************************
   // Private Methods
   //**************************************************************************
   //! TODO - any private methods?

   //**************************************************************************
   // Private Members
   //**************************************************************************

   // This 2d array is the checkers board.
   // I'm allowing this here because 64 ints is not that much memory and there's
   // only one board per game.
   BoardToken _board[MAX_WIDTH][MAX_LENGTH];

   // these are for saving off the location of the piece to be moved and where
   // it's moving to
   unsigned int _startRow;
   unsigned int _startCol;
   unsigned int _endRow;
   unsigned int _endCol;

   // Saves off whose turn it is.
   BoardToken _mover;

   // Saves off how the last move went.
   MoveType _lastMove;
};

} // end namespace BlizzCheckers
#endif // BOARD_H

