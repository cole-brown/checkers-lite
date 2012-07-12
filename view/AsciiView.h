//******************************************************************************
//
// The AsciiView class proviews a text-based UI of the game to the user.
// 
//*****************************************************************************
#ifndef ASCIIVIEW_H
#define ASCIIVIEW_H

// #include "something.h"

namespace BlizzCheckers {

// forward declarations
class Board;

class AsciiView
{
public:
   //**************************************************************************
   // Public Constants
   //**************************************************************************
   //! TODO - anything public?


   //**************************************************************************
   // Public Methods
   //**************************************************************************

   //-----------------------------------------------------------------------
   // This is the only constructor.  Its primary purpose is to 
   // initialize class configuration variables.
   //
   // Inputs:
   //    checkersBoard - pointer to the checkers board
   //
   // Outputs: 
   //    Nothing
   //
   // Exceptions:
   //    None - Nothing
   //-----------------------------------------------------------------------
   AsciiView(Board* checkersBoard);

   //-----------------------------------------------------------------------
   // Destructor
   //-----------------------------------------------------------------------
   virtual ~AsciiView(void);

   //-----------------------------------------------------------------------
   // Draws the info line, board, and prompt to stdout.
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
   void draw(void);
   

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

   //-----------------------------------------------------------------------
   // Returns ASCII representation of the board token at the supplied location.
   //
   // Inputs:
   //    row - row on the board
   //    col - column on the board
   //
   // Outputs: 
   //    char - ASCII character representing the token
   //
   // Exceptions:
   //    None - Nothing
   //-----------------------------------------------------------------------
   char getTokenAt(unsigned int row, unsigned int col);
   

   //**************************************************************************
   // Private Members
   //**************************************************************************

   // the checkers board
   Board* _board;
   
};

} // end namespace BlizzCheckers
#endif // ASCIIVIEW_H

