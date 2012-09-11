//******************************************************************************
//
// Entry function for Checkers Lite.
// 
//*****************************************************************************

#include <iostream>
#include <new>
#include "controller/Game.h"

using namespace std;
using namespace CheckersLite;

int main(int argc, const char* argv[])
{
  try {
    // Create human vs computer game
    Game* checkers = new Game(Game::HUMAN, Game::AI_RAND);
    
    // Play the game!
    Game::PlayErrors retVal = checkers->play();

    // and now it's done
    return (int)retVal;
  }
  catch (std::bad_alloc &e)
  {
    // newing something failed
    cout << "newing memory failed: " << e.what() << endl;
    return -1;
  }
  catch (...)
  {
    // Not using exceptions, but handling them just to be overly thorough.
    cout << "Unhandled exception!" << endl;
    return -1;
  }
}

