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
// PUBLIC METHOD : turn
//*****************************************************************************
bool Human::turn(void)
{
   cout << "Human player (" << _color << ") took turn." << endl;
   return true;
}


} // end namespace BlizzCheckers

