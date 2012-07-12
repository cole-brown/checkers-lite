//*****************************************************************************
//
// Reference the class description in AiRand.h.
//
//*****************************************************************************

#include "AiRand.h"

namespace BlizzCheckers {

//*****************************************************************************
// PUBLIC CONSTRUCTOR : AiRand
//*****************************************************************************
AiRand::AiRand(Board* checkersBoard, Board::BoardToken playerColor):
  Player(checkersBoard, playerColor)
{
   // nothing to do
}


//*****************************************************************************
// DESTRUCTOR : AiRand
//*****************************************************************************
AiRand::~AiRand(void)
{
   //! TODO - Nothing to destruct?
   // Intentionally left blank.
}

//*****************************************************************************
// PUBLIC METHOD : turn
//*****************************************************************************
bool AiRand::turn(void)
{
   return true;
}


} // end namespace BlizzCheckers

