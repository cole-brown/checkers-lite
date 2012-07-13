//******************************************************************************
//
// The Game class controls the flow of the game and the player's interactions
// with the board and pieces.
// 
//*****************************************************************************
#ifndef GAME_H
#define GAME_H

#include <vector>
#include "model/Board.h"

namespace BlizzCheckers {


// forward declarations
class AsciiView;
class Player;

class Game
{
public:
   //**************************************************************************
   // Public Constants
   //**************************************************************************

   // Players for the game
   enum PlayerChoice
   {
     HUMAN   = 0,
     AI_RAND = 1,
   };

   // Return values for play().
   // 0 == OK
   // negative == error
   enum PlayErrors
   {
     // error-free game played
     PLAY_OK  = 0,

     // errors encountered during gameplay
     PLAY_ERR     = -100,
     PLAY_ERR_OOB = -101 // index out-of-bounds
   };
  

   //**************************************************************************
   // Public Methods
   //**************************************************************************

   //-----------------------------------------------------------------------
   // This is the only constructor.  Its primary purpose is to 
   // initialize class configuration variables.
   //
   // Inputs:
   //    whitePlayer - player type to play white pieces
   //    blackPlayer - player type to play black pieces
   //
   // Outputs: 
   //    Nothing
   //
   // Exceptions:
   //    std:bad_alloc - failed new
   //-----------------------------------------------------------------------
   Game(PlayerChoice whitePlayer, PlayerChoice blackPlayer);

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

   //-----------------------------------------------------------------------
   // Creates the specified player type and adds it to the _players vector.
   //
   // NOTE: _board must be initialized before this is called!
   //
   // Inputs:
   //    player - see PlayerChoice enum for possiblities
   //    playerColor - BLACK_PIECE or WHITE_PIECE
   //
   // Outputs: 
   //    Nothing
   //
   // Exceptions:
   //    bad_alloc - could not new memory for player object
   //-----------------------------------------------------------------------
   void addPlayer(PlayerChoice player, Board::BoardToken playerColor);
   

   //**************************************************************************
   // Private Members
   //**************************************************************************

   // the checkers board
   Board* _board;

   // the user interface
   AsciiView* _view;

   // the players
   std::vector<Player*> _players;
};

} // end namespace BlizzCheckers
#endif // GAME_H

