//*****************************************************************************
//
// Reference the class description in AsciiView.h.
//
//*****************************************************************************

#include <iostream>
#include "AsciiView.h"
#include "model/Board.h"

using namespace std;

namespace BlizzCheckers {

//*****************************************************************************
// PUBLIC CONSTRUCTOR : AsciiView
//*****************************************************************************
AsciiView::AsciiView(Board* checkersBoard):
  _board(checkersBoard)
{
  // nothing more to do
}


//*****************************************************************************
// DESTRUCTOR : AsciiView
//*****************************************************************************
AsciiView::~AsciiView(void)
{
   //! TODO - Nothing to destruct?
   // Intentionally left blank.
}


//*****************************************************************************
// PUBLIC METHOD : draw
//*****************************************************************************
void AsciiView::draw(void)
{
   // TODO move these?
   static const char* INDENT = "   ";

   // clear out previous draw
   //! TODO system(CLEAR_CMD);
   cout << "\n\n\n\n" << endl;

   // print out info line
   cout << "Red (X) moved h6 to g5.\n" << endl;

   // print out the board
   cout << INDENT << "    a b c d e f g h\n"
        << INDENT << "  +-----------------+" << endl;
   for (unsigned int row = 0; row < Board::MAX_LENGTH; row++)
   {
      // initial row number & board border
      cout << INDENT << (Board::MAX_LENGTH - row) << " | ";

      // loop through columns in row, printing out proper token.
      for (unsigned int col = 0; col < Board::MAX_WIDTH; col++)
      {
         //! TODO check for invalid, return error.
         cout << getTokenAt(row,col) << " ";
      }

      // final board border & row number
      cout << "| " << (Board::MAX_LENGTH - row) << endl;
   }
   cout << INDENT << "  +-----------------+\n"
        << INDENT << "    a b c d e f g h\n" << endl;

   // print out the prompt
   cout << "Your move: ";
}


//*****************************************************************************
// PRIVATE METHOD : getTokenAt
//*****************************************************************************
char AsciiView::getTokenAt(unsigned int row, unsigned int col)
{
  //! TODO move the chars to class as consts

  // get token from the board and translate to ASCII char
  char retVal = 'I';
  switch (_board->at(row, col))
  {
     case Board::EMPTY_SQUARE:
       retVal = '.';
       break;
     case Board::BLACK_PIECE:
       retVal = 'X';
       break;
     case Board::WHITE_PIECE:
       retVal = 'O';
       break;
     case Board::INVALID_TOKEN:
       // intentional fall-through
     default:
        // this really shouldn't happen, but...
        return 'I';
  }
  return retVal;
}



} // end namespace BlizzCheckers

