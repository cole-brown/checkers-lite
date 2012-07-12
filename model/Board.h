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
     MAX_PIECES = 12
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
   //    row - row/x coordinate
   //
   // Outputs: 
   //    BoardToken - token at row,col or INVALID_TOKEN
   //
   // Exceptions:
   //    None - Nothing
   //-----------------------------------------------------------------------
   BoardToken at(unsigned int row, unsigned int col);
   

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
   
};

} // end namespace BlizzCheckers
#endif // BOARD_H

