#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;
class Grid {
    private:
    public: // public static class constants, for direction indicators
   
    static const int NORTH = 0;
    static const int WEST = 1;
    static const int SOUTH = 2;
    static const int EAST = 3;

    //selfdefined
    int row,col;
    //這個是ON or OFF
    int PATH;
    //這個是方向
    int ds;
    //selfdefined end

    // public member functions
    Grid(); // build 1 x 1 grid with mover in only square, facing east
    Grid(int r, int c); // build grid with r rows, c cols,
    // blocks around edge with random exit
    // and random mover position and direction
    Grid(int r, int c, int mr, int mc, int d);
    // build empty grid with r rows, c cols, and
    // mover at row mr, col mc, and facing direction d

    void Display() const; // display the grid on screen
    void TogglePath(); // toggle whether or not moved path is shown
    void PutDown(); // put down an item at the mover's position
    bool PutDown(int r, int c); // put down an item at (r, c), if possible
    bool Move(int s); // move forward s spaces, if possible
    void TurnLeft(); // turn the mover to the left
    bool PickUp(); // pick up item at current position
    bool PlaceBlock(int r, int c); // put a block at (r, c), if possible
    void Grow(int gr, int gc); // grow the grid by gr rows, gc columns
    
    // Accessors
    bool FrontIsClear() const; // check to see if space in front of mover is clear
    bool RightIsClear() const; // check to see if space to right of mover is clear */
    // return number of rows in the grid
    int GetNumRows() const;
    // return number of columns in the grid
    int GetNumCols() const;
    int GetRow() const;
    int GetCol() const;
};
