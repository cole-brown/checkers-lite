//******************************************************************************
//
// The AsciiView class proviews a text-based UI of the game to the user.
// 
//*****************************************************************************
#ifndef ASCIIVIEW_H
#define ASCIIVIEW_H

#include <string>
#include "model/Board.h"

namespace CheckersLite {

class AsciiView
{
public:
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

   //-----------------------------------------------------------------------
   // Prints out a this-is-a-new-game line. Note that draw() prints no
   // info line initially, so call this.
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
   void newGame(Board::BoardToken firstPlayer);


private:
   //**************************************************************************
   // Private Methods
   //**************************************************************************

   //-----------------------------------------------------------------------
   // Returns ASCII representation of the supplied board token.
   //
   // Inputs:
   //    tok - BoardToken for which an ASCII char is needed
   //
   // Outputs: 
   //    char - ASCII character representing the token
   //
   // Exceptions:
   //    None - Nothing
   //-----------------------------------------------------------------------
   char tokenToChar(Board::BoardToken tok);

   //-----------------------------------------------------------------------
   // Returns a std::string pointer representing the player's piece's color.
   //
   // Inputs:
   //    player - BoardToken of the player's
   //
   // Outputs: 
   //    string* - "White", "Black", or "Invalid"
   //
   // Exceptions:
   //    None - Nothing
   //-----------------------------------------------------------------------
   const std::string* const playerToStr(Board::BoardToken);
   
   //-----------------------------------------------------------------------
   // Prints line about who did what last move.
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
   void printInfo(void);

   //-----------------------------------------------------------------------
   // Translates row/col into a-h/1-8 board coordinates.
   //
   // Inputs:
   //    row - row
   //    col - column
   //
   // Outputs: 
   //    string - alphanumerical board coordinates (a1, h8, etc)
   //
   // Exceptions:
   //    None - Nothing
   //-----------------------------------------------------------------------
   std::string toAlphaNum(unsigned int row, unsigned int col);


   //**************************************************************************
   // Private Members
   //**************************************************************************

   // the checkers board (not owned by this class)
   Board* _board;
   
};

} // end namespace CheckersLite
#endif // ASCIIVIEW_H

