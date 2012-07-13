//*****************************************************************************
//
// Reference the class description in Human.h.
//
//*****************************************************************************

#include <iostream>
#include "Human.h"

using namespace std;

namespace BlizzCheckers {

//*****************************************************************************
// PUBLIC CONSTRUCTOR : Human
//*****************************************************************************
Human::Human(Board* checkersBoard, Board::BoardToken playerColor):
  Player(checkersBoard, playerColor)
{
   // nothing to do
}


//*****************************************************************************
// DESTRUCTOR : Human
//*****************************************************************************
Human::~Human(void)
{
   //! TODO - Nothing to destruct?
   // Intentionally left blank.
}


//*****************************************************************************
// PRIVATE METHOD : getInput
//*****************************************************************************
bool Human::getInput(string& userInput)
{
   static const string WHITESPACE = " \t\f\v\n\r";

   // get from stdin
   getline(cin, userInput);

   // trim
   size_t first = userInput.find_first_not_of(WHITESPACE);
   size_t last  = userInput.find_last_not_of(WHITESPACE);
   if ((first != string::npos) && (last != string::npos))
   {
      userInput = userInput.substr(first, last-first+1);
   }
   else
   {
      userInput.clear(); // str is all whitespace
   }

   // check input format
   bool retVal = true;
   if (userInput.size() != 2)
   {
      retVal = false;
   }
   else if ((userInput[0] < 'a') || (userInput[0] > 'h'))
   {
      retVal = false;
   }
   else if ((userInput[1] < '1') || (userInput[1] > '8'))
   {
      retVal = false;
   }

   return retVal;
}


//*****************************************************************************
// PRIVATE METHOD : getCol
//*****************************************************************************
//unsigned int Human::getCol(char col)
unsigned int getCol(char col)
{
   return (unsigned int)(col - 'a');
}


//*****************************************************************************
// PRIVATE METHOD : getRow
//*****************************************************************************
//unsigned int Human::getRow(char row)
unsigned int getRow(char row)
{
   unsigned int inverseRow = (unsigned int)(row - '1');
   return (Board::MAX_LENGTH-1 - inverseRow);
}


//*****************************************************************************
// PUBLIC METHOD : turn
//*****************************************************************************
bool Human::turn(void)
{
   //! TODO check for jumps that must be taken

   // get user input for which piece to move where
   string move;
   string to;
   cout << "Select piece to move (e.g. a1): ";
   bool moveGood = getInput(move);
   cout << "Move to new location (e.g. b2): ";
   bool toGood = getInput(to);

   // validate input
   if (!moveGood)
   {
      cout << "Piece to move (" << move << ") is an invalid format." << endl;
   }
   if (!toGood)
   {
      cout << "Place to move to (" << to << ") is an invalid format." << endl;
   }
   if (!moveGood || !toGood)
   {
     cout << "Valid format is a letter (a-h) followed immediately "
          << "by a number (1-8). Examples: a1, b8, h2, c5" << endl;

     // No point continuing.
     return false;
   }

   // translate input ("a1") into coordinates (8,0)
   unsigned int moveRow = getRow(move[1]);
   unsigned int moveCol = getCol(move[0]);
   unsigned int toRow   = getRow(to[1]);
   unsigned int toCol   = getCol(to[0]);
   
   // Check if piece exists and is this player's
   Board::BoardToken tok = _board->at(moveRow, moveCol);
   if (tok != _color)
   {
      cout << "Spot you selected to move from (" << move << ") ";
      if (tok == Board::EMPTY_SQUARE)
      {
        cout << "is empty. ";
      }
      else
      {
        cout << "is not your color piece. ";
      }
      cout << "Select a square with one of your pieces on it." << endl;

      return false;
   }

   // make the move (board will not allow if invalid)
   return _board->move(_color, moveRow, moveCol)->to(toRow, toCol);
}

} // end namespace BlizzCheckers

