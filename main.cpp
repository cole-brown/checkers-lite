//******************************************************************************
//
// Entry function for Blizzard Checkers Lite.
// 
//*****************************************************************************

#include <iostream>
#include <new>
#include "controller/Game.h"

using namespace std;
using namespace BlizzCheckers;

int main(int argc, const char* argv[])
{
  try {
    // Create human vs computer game
    Game* checkers = new Game(Game::HUMAN, Game::AI_RAND);
    
    // Play the game!
    Game::PlayErrors retVal = checkers->play();
    
    // error checks
    switch (retVal)
    {
      case Game::PLAY_OK:
        // do nothing
        break;
        
      //! TODO specific errors
      // case Game::PLAY_ERR:
      //   cout << "Error playing checkers. Details details details."
      //        << " Error number: " << retVal << endl;
      //   break;
        
      default:
        cout << "Unknown error. Error number: " << retVal << endl;
        break;
    }
    
    return (int)retVal;
  }
  catch (std::bad_alloc &e)
  {
    // newing something failed
    cout << "newing memory failed: " << e.what() << endl;
    return -1; // TODO error code enum?
  }
  catch (...)
  {
    // Not using exceptions, but handling them just to be overly thorough.
    cout << "Unhandled exception!" << endl;
    return -1;
  }
}

