//******************************************************************************
//
// The Game class controls the flow of the game and the player's interactions
// with the board and pieces.
// 
//*****************************************************************************
#ifndef GAME_H
#define GAME_H

namespace BlizzCheckers {


// forward declarations
class Board;
class AsciiView;

class Game
{
public:
   //**************************************************************************
   // Public Constants
   //**************************************************************************

   // Return values for play().
   // 0 == OK
   // negative == error
   enum PlayErrors
   {
     // error-free game played
     PLAY_OK  = 0,

     // errors encountered during gameplay
     PLAY_ERR = -1
   };
  

   //**************************************************************************
   // Public Methods
   //**************************************************************************

   //-----------------------------------------------------------------------
   // This is the only constructor.  Its primary purpose is to 
   // initialize class configuration variables.
   //
   // Inputs:
   //    None
   //
   // Outputs: 
   //    Nothing
   //
   // Exceptions:
   //    None - Nothing
   //-----------------------------------------------------------------------
   Game(void);

   //-----------------------------------------------------------------------
   // Destructor
   //-----------------------------------------------------------------------
   virtual ~Game(void);

   //-----------------------------------------------------------------------
   // Main play loop for the checkers game. Player turn taking, stalemate or
   // win condition checks.
   //
   // Returns PLAY_OK for
   //
   // Inputs:
   //    None
   //
   // Outputs: 
   //    PlayErrors - PLAY_OK for error-free game, regardless of win/loss/tie
   //               - Other values for errors. See PlayValues enum.
   //
   // Exceptions:
   //    None - Nothing
   //-----------------------------------------------------------------------
   PlayErrors play(void);
   

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

   // the checkers board
   Board* _board;

   // the user interface
   AsciiView* _view;
   
};

} // end namespace BlizzCheckers
#endif // GAME_H

