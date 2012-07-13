//******************************************************************************
//
// The Human class models how Humans interact with the game.
// 
//*****************************************************************************
#ifndef HUMAN_H
#define HUMAN_H

#include <string>
#include <vector>
#include "Player.h"

namespace BlizzCheckers {

class Human : public Player
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
   //    playerColor - BLACK_PIECE or WHITE_PIECE
   //
   // Outputs: 
   //    Nothing
   //
   // Exceptions:
   //    None - Nothing
   //-----------------------------------------------------------------------
   Human(Board* checkersBoard, Board::BoardToken playerColor);

   //-----------------------------------------------------------------------
   // Destructor
   //-----------------------------------------------------------------------
   virtual ~Human(void);

   //-----------------------------------------------------------------------
   // This function is how the Human takes their turn. This does not guarentee
   // the turn is successful or valid. If turn was invalid, the Human should be
   // informed and given another chance to take their turn.
   //
   // Inputs:
   //    None
   //
   // Outputs: 
   //    bool - true: successful, valid turn
   //           false: invalid turn attempt or error along the way
   //
   // Exceptions:
   //    None - Nothing
   //-----------------------------------------------------------------------
   virtual bool turn(void);
   

private:
   //**************************************************************************
   // Private Methods
   //**************************************************************************

   //-----------------------------------------------------------------------
   // Gets user's input from stdin and trims leading/trailing whitespace.
   //
   // Inputs:
   //    None
   //
   // Outputs: 
   //    userInput - trimmed string that user typed in
   //
   // Exceptions:
   //    None - Nothing
   //-----------------------------------------------------------------------
   void getInput(std::string& userInput);

   //-----------------------------------------------------------------------
   // Verifies supplied string is in proper format  ([a-h][1-8])
   //
   // Inputs:
   //    userInput - input to verify
   //
   // Outputs: 
   //    bool - true if input is proper format ([a-h][1-8]), false otherwise
   //
   // Exceptions:
   //    None - Nothing
   //-----------------------------------------------------------------------
   bool checkInput(std::string& userInput);

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

   //-----------------------------------------------------------------------
   // Force the user to make a jump. Lists out the jumps and then asks
   // the user to pick from them. Executes the chosen jump move.
   //
   // Inputs:
   //    moves - vector of possible jumps
   //
   // Outputs: 
   //    bool - true: successful, valid turn
   //           false: invalid turn attempt or error along the way
   //
   // Exceptions:
   //    None - Nothing
   //-----------------------------------------------------------------------
   bool jumpTurn(std::vector<Board::BoardPos>* moves);
   
};

} // end namespace BlizzCheckers
#endif // HUMAN_H

