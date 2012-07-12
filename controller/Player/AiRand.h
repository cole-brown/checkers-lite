//******************************************************************************
//
// The AiRand class is a computer player that randomly selects from the
// available valid moves.
// 
//*****************************************************************************
#ifndef AIRAND_H
#define AIRAND_H

#include "Player.h"

namespace BlizzCheckers {

class AiRand : public Player
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
   AiRand(Board* checkersBoard, Board::BoardToken playerColor);

   //-----------------------------------------------------------------------
   // Destructor
   //-----------------------------------------------------------------------
   virtual ~AiRand(void);

   //-----------------------------------------------------------------------
   // This function is how the AiRand takes their turn. This does not guarentee
   // the turn is successful or valid. If turn was invalid, the AiRand should be
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
   

protected:
   //**************************************************************************
   // Protected Methods
   //**************************************************************************
   //! TODO - anything protected?

private:
   //**************************************************************************
   // Private Constants
   //**************************************************************************
   //! TODO - any consts?

   //**************************************************************************
   // Private Methods
   //**************************************************************************
   //! TODO - any private methods?

   //**************************************************************************
   // Private Members
   //**************************************************************************
   //!TODO - what kind of class ain't got no members?
   
};

} // end namespace BlizzCheckers
#endif // AIRAND_H

