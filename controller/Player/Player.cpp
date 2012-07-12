//*****************************************************************************
//
// Reference the class description in Player.h.
//
//*****************************************************************************

#include "Player.h"
#include "model/Board.h"

namespace BlizzCheckers {

//*****************************************************************************
// PUBLIC CONSTRUCTOR : Player
//*****************************************************************************
Player::Player(Board* checkersBoard, Board::BoardToken playerColor):
  _board(checkersBoard),
  _color(playerColor)
{
  // nothing more to do
}


//*****************************************************************************
// DESTRUCTOR : Player
//*****************************************************************************
Player::~Player(void)
{
   // Intentionally left blank.
}

} // end namespace BlizzCheckers

