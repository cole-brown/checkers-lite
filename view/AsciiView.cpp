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
   // Intentionally left blank.
}


//*****************************************************************************
// PUBLIC METHOD : newGame
//*****************************************************************************
void AsciiView::newGame(Board::BoardToken firstPlayer)
{
   cout << "New game! " << *playerToStr(firstPlayer) << " ("
        << tokenToChar(firstPlayer) << ") is first up.\n" << endl;   
}


//*****************************************************************************
// PUBLIC METHOD : draw
//*****************************************************************************
void AsciiView::draw(void)
{
   static const char* INDENT = "   ";

   // print out info line
   printInfo();

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
         cout << tokenToChar(_board->at(row, col)) << " ";
      }

      // final board border & row number
      cout << "| " << (Board::MAX_LENGTH - row) << endl;
   }
   cout << INDENT << "  +-----------------+\n"
        << INDENT << "    a b c d e f g h\n" << endl;

   // print out the prompt
//   cout << "Your move: ";
}


//*****************************************************************************
// PRIVATE METHOD : printInfo
//*****************************************************************************
void AsciiView::printInfo(void)
{
   // get a pointer to last move's information
   const Board::MoveInfo* const info = _board->moveInfo();

   // new game check
   Board::BoardToken player = info->_mover;
   if (player == Board::INVALID_TOKEN)
   {
      // skip info line on first. Controller should've called newGame()
      // for special info prompt.
      return;
   }

   // clear out previous draw
   cout << "\n\n\n\n" << endl;

   // print game state info
   switch (_board->state())
   {
      case Board::BLACK_WIN_STATE:
         cout << "GAME OVER! Black wins!\n" << endl;
         return;
      case Board::WHITE_WIN_STATE:
         cout << "GAME OVER! White wins!\n" << endl;
         return;
      case Board::STALEMATE:
         cout << "GAME OVER! Stalemate achieved! "
              << "Everyone loses! Congradulations all 'round!\n"
              << endl;
         return;
      case Board::ONLY_WHITE_PLAYABLE:
         cout << "Black has no moves possible right now, FYI." << endl;
         break;
      case Board::ONLY_BLACK_PLAYABLE:
         cout << "White has no moves possible right now, FYI." << endl;
         break;
      case Board::GAME_PLAYABLE:
         // nothing to do.
         break;
   }

   // print player
   cout << *playerToStr(player) << " (" << tokenToChar(player)
        << ") ";

   // print move info
   switch (info->_lastMove)
   {
      case Board::MOVE:
         cout << "moved from " << toAlphaNum(info->_startRow, info->_startCol)
              << " to " << toAlphaNum(info->_endRow, info->_endCol) << endl;
         break;
      case Board::JUMP:
         cout << "jumped from " << toAlphaNum(info->_startRow, info->_startCol)
              << " To " << toAlphaNum(info->_endRow, info->_endCol) << endl;
         break;
      case Board::OUT_OF_BOUNDS:
         cout << "tried to move outside the box. Either "
              << toAlphaNum(info->_startRow, info->_startCol) << " or "
              << toAlphaNum(info->_endRow, info->_endCol)
              << " are unacceptable. Try again." << endl;
         break;
      case Board::INVALID_MOVER:
         cout << "is an invalid player..." << endl;
         break;
      case Board::EMPTY_START:
         cout << "tried to move an empty space. Stick to your pieces."
              << " You're all the '" << tokenToChar(player) << "' ones." << endl;
         break;
      case Board::ENEMY_START:
         cout << "tried to move a piece belonging to the opponent."
              << " Stick to your pieces.  You're all the '"
              << tokenToChar(player) << "' ones." << endl;
         break;
      case Board::WRONG_DIRECTION:
         cout << "tried to move the wrong way, or not at all. Try again;"
              << " this time in the proper direction." << endl;
         break;
      case Board::BAD_MOVE_DIAG:
         cout << "almost moved... but remember to move diagonally. Up and over."
              << " Try again." << endl;
         break;
      case Board::BAD_MOVE_DIST:
         cout << "didn't move the proper distance. One up, one over for a move;"
              << " two up, two over for jumps. Try again." << endl;
         break;
      case Board::OCCUPIED_ENEMY:
         cout << "tried to move onto enemy territory. Jump over them or go"
              << " around. Try again." << endl;
         break;
      case Board::OCCUPIED_SELF:
         cout << "tried to move onto a spot already occupied by their own piece."
              << " Piggy-back rides are not allowed. Try again." << endl;
         break;
      case Board::JUMPED_NON_ENEMY:
         cout << "tried to jump over their own checkers piece. Which is "
              << " totally illegal in all 50 states. Try again." << endl;
         break;
      case Board::BAD_FORMAT:
         cout << "tried to do something, but we're not sure what. Couldn't read "
              << "your typing. \n\nValid input format is a letter (a-h) followed "
              << "immediately by a number (1-8). Examples: a1, b8, h2, c5"
              << endl;
         break;
      default:
        cout << "did something unknown... MoveType #"
             << info->_lastMove << endl;
        break;
   }

   // one blank line
   cout << "\n";
}


//*****************************************************************************
// PRIVATE METHOD : toAlphaNum
//*****************************************************************************
string AsciiView::toAlphaNum(unsigned int row, unsigned int col)
{
   string retVal = "  ";

   // set row char
   retVal[1] = ('1' + Board::MAX_LENGTH - 1 - row);

   // set col char
   retVal[0] = ('a' + col);

   return retVal;
}


//*****************************************************************************
// PRIVATE METHOD : tokenToChar
//*****************************************************************************
char AsciiView::tokenToChar(Board::BoardToken tok)
{
   // get token from the board and translate to ASCII char
   char retVal = 'I';
   switch (tok)
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
      case Board::INVALID_TOKEN: // intentional fall-through
      default:
         // this really shouldn't happen, but...
         return 'I';
   }
   return retVal;
}


//*****************************************************************************
// PRIVATE METHOD : playerToStr
//*****************************************************************************
const string* const AsciiView::playerToStr(Board::BoardToken player)
{
   static const string INVALID = "Invalid";
   static const string WHITE   = "White";
   static const string BLACK   = "Black";

   switch (player)
   {
      case Board::BLACK_PIECE:
         return &BLACK;
      case Board::WHITE_PIECE:
         return &WHITE;
      default:
         return &INVALID;
   }
}


} // end namespace BlizzCheckers

