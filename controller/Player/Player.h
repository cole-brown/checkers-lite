//******************************************************************************
//
// The Player class models how players interact with the game.
// 
//*****************************************************************************
#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"

namespace BlizzCheckers {

class Player
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
   //    playerColor - BLACK_PIECE or WHITE_PIECE
   //
   // Outputs: 
   //    Nothing
   //
   // Exceptions:
   //    None - Nothing
   //-----------------------------------------------------------------------
   Player(Board* checkersBoard, Board::BoardToken playerColor);

   //-----------------------------------------------------------------------
   // Destructor
   //-----------------------------------------------------------------------
   virtual ~Player(void);

   //-----------------------------------------------------------------------
   // This function is how the player takes their turn. This does not guarentee
   // the turn is successful or valid. If turn was invalid, the player should be
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
   virtual bool turn(void) = 0;

   //-----------------------------------------------------------------------
   // Returns the player's board piece color.
   //
   // Inputs:
   //    None
   //
   // Outputs: 
   //    BoardToken - BLACK_PIECE or WHITE_PIECE
   //
   // Exceptions:
   //    None - Nothing
   //-----------------------------------------------------------------------
   Board::BoardToken color() { return _color; }


protected:
   //**************************************************************************
   // Protected Members
   //**************************************************************************

   // pointer to checkers board model (not owned by this class)
   Board* _board;

   // color pieces that this player is playing
   Board::BoardToken _color;
};

} // end namespace BlizzCheckers
#endif // PLAYER_H

