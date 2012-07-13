//******************************************************************************
//
// The Board class contains a model of the checkers board and the pieces on it.
// 
//*****************************************************************************
#ifndef BOARD_H
#define BOARD_H

#include <vector>

namespace BlizzCheckers {

class Board
{
public:
   //**************************************************************************
   // Public Constants
   //**************************************************************************

   // Possible values for each location on the checkers board.
   // Note: This checkers has no kings.
   enum BoardToken
   {
      INVALID_TOKEN = -1,
      EMPTY_SQUARE  = 0,
      BLACK_PIECE   = 1,
      WHITE_PIECE   = 2
   };

   // all possible states of the game
   enum GameState
   {
      // END GAME states first
      BLACK_WIN_STATE,
      WHITE_WIN_STATE,
      STALEMATE,

      // PLAYABLE states last
      GAME_PLAYABLE,
      ONLY_WHITE_PLAYABLE,
      ONLY_BLACK_PLAYABLE
   };

   // misc constants
   enum {
     // American Checkers boards are 8x8 squares
     MAX_WIDTH  = 8,
     MAX_LENGTH = MAX_WIDTH,

     // players start with 12 pieces
     MAX_PIECES = 12,

     // directions of movement:
     // black moves down the board, so each move adds (at least) one to the column
     MOVE_DIR_BLACK = 1,
     // white moves up the board, so each move subtracts (at least) one
     MOVE_DIR_WHITE = -1
   };

   // All possible results of a move. Only MOVE and JUMP indicate successes.
   enum MoveType
   {
     MOVE = 0,
     JUMP,
     OUT_OF_BOUNDS,
     INVALID_MOVER, // mover must be WHITE_PIECE or BLACK_PIECE
     EMPTY_START, // selected a blank square as the starting location
     ENEMY_START, // the selected start location has the opponent's piece
     WRONG_DIRECTION, // didn't go in the direction indicated by MOVE_DIR_<color>
     BAD_MOVE_DIAG, // non-diagonal move
     BAD_MOVE_DIST, // move isn't proper length
     OCCUPIED_ENEMY, // end spot is occupied by the opponent and can't be jumped
     OCCUPIED_SELF,  // no piggy back rides allowed
     JUMPED_NON_ENEMY, // only allowed to jump over your opponent's pieces
     BAD_FORMAT
   };

   // structure for holding information about the last move
   struct MoveInfo
   {
      // these are for saving off the location of the piece to be moved and
      // where it's moving to
      unsigned int _startRow;
      unsigned int _startCol;
      unsigned int _endRow;
      unsigned int _endCol;

      // Whose turn it was.
      BoardToken _mover;
   
      // How the last move went.
      MoveType _lastMove;
   };

   // compact struct for noting positions of pieces on the board
   struct BoardPos
   {
      unsigned int _row;
      unsigned int _col;
      unsigned int _toRow;
      unsigned int _toCol;
      BoardPos(unsigned int row, unsigned int col,
               unsigned int toRow = 0, unsigned int toCol = 0)
      {
         _row = row;
         _col = col;
         _toRow = toRow;
         _toCol = toCol;
      }
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
   Board(void);

   //-----------------------------------------------------------------------
   // Destructor
   //-----------------------------------------------------------------------
   virtual ~Board(void);

   //-----------------------------------------------------------------------
   // Returns true if supplied player's turn is possible. False if they're
   // currently stuck with no moves to make.
   //
   // If a moves vector is supplied, it will be filled with the possible moves.
   // If jumps are possible, only the jumps will be supplied.
   //
   // Inputs:
   //    player - WHITE_PIECE or BLACK_PIECE
   //
   // Outputs: 
   //    bool  - true if possible, false if not
   //    moves - Positions of movable pieces. If jumps possible, will only
   //            show those.
   //
   // Exceptions:
   //    None - Nothing
   //-----------------------------------------------------------------------
   bool turnPossible(BoardToken player, std::vector<BoardPos>* moves = NULL);

   //-----------------------------------------------------------------------
   // Returns the games current state. Win, stalemate, or otherwise.
   //
   // Inputs:
   //    None
   //
   // Outputs: 
   //    GameState - see GameState enum for all possibilities
   //
   // Exceptions:
   //    None - Nothing
   //-----------------------------------------------------------------------
   GameState state(void);

   //-----------------------------------------------------------------------
   // Returns the board token at the supplied row & column. Gives INVALID_TOKEN
   // if row or column is out of bounds.
   //
   // Inputs:
   //    row - row coordinate
   //    col - column coordinate
   //
   // Outputs: 
   //    BoardToken - token at row,col or INVALID_TOKEN
   //
   // Exceptions:
   //    None - Nothing
   //-----------------------------------------------------------------------
   BoardToken at(unsigned int row, unsigned int col);

   //-----------------------------------------------------------------------
   // Selects piece to be moved. Returns this pointer so it can be chained
   // with to(). e.g. board->move(x,y)->to(newX,newY)
   //
   // Inputs:
   //    mover - color of mover's pieces: BLACK_PIECE or WHITE_PIECE
   //    row - row of piece to be moved
   //    col - column of piece to be moved
   //
   // Outputs: 
   //    Board* - this
   //
   // Exceptions:
   //    None - Nothing
   //-----------------------------------------------------------------------
   Board* move(BoardToken mover, unsigned int row, unsigned int col);

   //-----------------------------------------------------------------------
   // Attempts to move piece selected by move() to location specified by
   // parameters. Check return value for success. Check moveInfo() for details.
   //
   // Inputs:
   //    row - row of piece to be moved
   //    col - column of piece to be moved
   //
   // Outputs: 
   //    bool - true for a successful move, false for failure
   //
   // Exceptions:
   //    None - Nothing
   //-----------------------------------------------------------------------
   bool to(unsigned int row, unsigned int col);

   //-----------------------------------------------------------------------
   // Returns information about how last move when.
   //
   // Inputs:
   //    None
   //
   // Outputs: 
   //    MoveInfo - struct filled with the info
   //
   // Exceptions:
   //    None - Nothing
   //-----------------------------------------------------------------------
   const MoveInfo* const moveInfo(void) { return &_info; }

   //-----------------------------------------------------------------------
   // Sets _info._lastMove. For when the the player flubbed so hard move().to()
   // is not possible, and you want the view to tell them something next time
   // around.
   //
   // Inputs:
   //    mover - color of mover's pieces: BLACK_PIECE or WHITE_PIECE
   //    move - one of the MoveType values. Hopefully not MOVE or JUMP.
   //
   // Outputs: 
   //    Nothing
   //
   // Exceptions:
   //    None - Nothing
   //-----------------------------------------------------------------------
   void setLastMove(BoardToken mover, MoveType move)
   {
      _info._mover = mover;
      _info._lastMove = move;
   }
   

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

   // This 2d array is the checkers board.
   // I'm allowing this here because 64 ints is not that much memory and there's
   // only one board per game.
   BoardToken _board[MAX_WIDTH][MAX_LENGTH];

   // information about last move. From, to, who moved, how it went.
   MoveInfo _info;
};

} // end namespace BlizzCheckers
#endif // BOARD_H

