// SID: 1506036
// MOD003197
// forest.h    Class declarations
#ifndef FORESTH
#define FORESTH

#include <iostream>



using namespace std;

class Cell
{
	//  private class variable
	int state, oldState;

public:

	// default constructor
	Cell();

	// 1 arg constructor
	Cell(int state);

	// state of cell must be between 0 and 3
	void setCellState(int newState);

	// copy the cell state, prevents over spreading of fire
	// in a single parse of array
	void save();

	// access oldState value
	int getOldState();

	// access state value
	int getCellState();
};

class Grid
{
	// private class variables
	int numRows, numCols;
public:
	// public class array, with upper limit - as in init method
	Cell forest[70][70];

	// default constructor
	Grid();

	// 2 arg constructor
	Grid(int newNumRows, int newNumCols);

	// rows and cols must be between 0 and 21
	void init(int newNumRows, int newNumCols);

	// printGrid prints a ASCII symbol to the console, corresponding to its status
	void print();

	// check if a 1 (unburnt tree) exists in forest 
	bool check();

	// copies state of all cells
	void burn();

	// checks NSEW neighbours and sets them on fire if they are not on fire and are not border cell
	void update();

	// loops through check update burn print until no trees left
	void iterator();

	// get user input for grid size - includes input validation
	void inputs();
};

#endif