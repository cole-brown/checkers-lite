//*****************************************************************************
//
// Reference the class description in Game.h.
//
//*****************************************************************************

#include "Game.h"
#include "model/Board.h"
#include "view/AsciiView.h"

namespace BlizzCheckers {

//*****************************************************************************
// PUBLIC CONSTRUCTOR : Game
//*****************************************************************************
Game::Game(void)
{
   // create the board
   _board = new Board();

   // create the view
   _view = new AsciiView(_board);
}


//*****************************************************************************
// DESTRUCTOR : Game
//*****************************************************************************
Game::~Game(void)
{
   // free up pointers
   delete _board;
}


//*****************************************************************************
// PUBLIC METHOD : play
//*****************************************************************************
Game::PlayErrors Game::play(void)
{
   // Assume success, change when error is encountered.
   PlayErrors retVal = PLAY_OK;

   // Main gameplay loop
   bool done = false;
   while (!done)
   {
      done = true;

      // is turn possible?

      // let player take turn

      // check for end-of-game conditions (win/stalemate)

      // update UI
//      _view->setInfo();
//      _view->setPrompt();
      _view->draw();
   }

   // return whatever retVal is set to now
   return retVal;
}


} // end namespace BlizzCheckers

