//*****************************************************************************
//
// Reference the class description in Human.h.
//
//*****************************************************************************

#include <iostream>
#include <sstream>
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
   // Intentionally left blank.
}


//*****************************************************************************
// PRIVATE METHOD : getInput
//*****************************************************************************
void Human::getInput(string& userInput)
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
}

//*****************************************************************************
// PRIVATE METHOD : checkInput
//*****************************************************************************
bool Human::checkInput(string& userInput)
{
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
// PRIVATE METHOD : toAlphaNum
//*****************************************************************************
string Human::toAlphaNum(unsigned int row, unsigned int col)
{
   string retVal = "  ";

   // set row char
   retVal[1] = ('1' + Board::MAX_LENGTH - 1 - row);

   // set col char
   retVal[0] = ('a' + col);

   return retVal;
}


//*****************************************************************************
// PRIVATE METHOD : jumpTurn
//*****************************************************************************
bool Human::jumpTurn(vector<Board::BoardPos>* moves)
{
   static const char* INDENT = "   ";
   
   // give the user the news
   bool plural = (moves->size() == 1) ? false : true;
   cout << (plural ? "A jump is" : "Jumps are") << " possible and therefore "
        << "MUST be taken.\n\nJumps:" << endl;

   // list out the jumps possible...
   unsigned int i = 0;
   for (vector<Board::BoardPos>::iterator it = moves->begin();
        it < moves->end();
        it++)
   {
      cout << INDENT << "#" << i << ": " << toAlphaNum(it->_row, it->_col)
           << " -> " << toAlphaNum(it->_toRow, it->_toCol) << endl;
      i++;
   }

   // let user choose
   cout << "Choose your jump move number (0-" << (moves->size()-1) << "): #";
   string jumpStr;
   getInput(jumpStr);

   // figure out what they chose
   unsigned int jump;
   stringstream jss(jumpStr);
   jss >> jump;

   // validate
   if (!(jump < moves->size()))
   {
     // Fake a move and return
     _board->setLastMove(_color, Board::BAD_FORMAT);
     return false;
   }

   // make the chosen move
   return _board->move(_color, (*moves)[jump]._row, (*moves)[jump]._col)
                ->to((*moves)[jump]._toRow, (*moves)[jump]._toCol);
}


//*****************************************************************************
// PUBLIC METHOD : turn
//*****************************************************************************
bool Human::turn(void)
{
   // check for jumps that must be taken
   vector<Board::BoardPos> moves;
   _board->turnPossible(_color, &moves, true); // only jumps

   // there is a jump
   if (moves.size() > 0)
   {
     // so we must take it and skip the do-whatever phase, below.
     return jumpTurn(&moves);
   }

   // get user input for which piece to move where
   string move;
   string to;
   cout << "Select piece to move (e.g. a1): ";
   getInput(move);
   bool moveGood = checkInput(move); 
   cout << "Move to new location (e.g. b2): ";
   getInput(to);
   bool toGood = checkInput(to);

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

     // Fake a move and return
     _board->setLastMove(_color, Board::BAD_FORMAT);
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

      // allow the move attempt anyways, so the board can record the failure
      // and the view can print it out.
   }

   // make the move (board will not allow if invalid)
   return _board->move(_color, moveRow, moveCol)->to(toRow, toCol);
}

} // end namespace BlizzCheckers

