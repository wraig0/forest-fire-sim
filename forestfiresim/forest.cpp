// SID: 1506036
// MOD003197
// forest.cpp	Class function definitions
#include "forest.h"

// default constructor
Cell::Cell()
{
	oldState = 0;
	state = 0;
}

// 1 arg constructor
Cell::Cell(int state)
{
	setCellState(state);
}

// state of cell must be between 0 and 3
void Cell::setCellState(int newState)
{
	if (0 <= newState && newState < 3)
		state = newState;
	// if outside 0-3 make it 0
	else
		state = 0;
}

// copy the cell state, prevents over spreading of fire
// in a single parse of array
void Cell::save()
{
	oldState = state;
}

// access oldState value
int Cell::getOldState()
{
	return oldState;
}

// access state value
int Cell::getCellState()
{
	return state;
}

// default constructor
Grid::Grid()
{
	// set default dimensions to 21 by 21 unless otherwise specified
	numRows = 21;
	numCols = 21;
	init(21, 21);
}

// 2 arg constructor
Grid::Grid(int newNumRows, int newNumCols)
{
	numRows = newNumRows;
	numCols = newNumCols;
	init(numRows, numCols);
}

// rows and cols must be between 7 and 70
void Grid::init(int newNumRows, int newNumCols)
{
	// if row value is between 7 and 70 leave it
	if (7 <= newNumRows && newNumRows < 71)
	{
		numRows = newNumRows;
	}
	else
		// if outside limits set to max 70
	{
		numRows = 70;
	}
	// if col value is between 7 and 70 leave it
	if (7 <= newNumCols && newNumCols < 71)
	{
		numCols = newNumCols;
	}
	else
		// if outside limits set to max 70
	{
		numCols = 70;
	}
	// loop through all entries in array
	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			// if on the outside of forest set as border
			if (row == 0 || col == 0 || row >= numRows - 1 || col >= numCols - 1)
			{
				forest[row][col].setCellState(0);
			}
			// otherwise set as tree
			else
			{
				forest[row][col].setCellState(1);
			}
		}
	}
}

// printGrid prints a ASCII symbol to the console, corresponding to its status
void Grid::print()
{
	// loop through all entries in array
	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			// print O for border 
			if (forest[row][col].getCellState() == 0)
			{
				cout << "O ";
			}
			// print ^ for tree
			else if (forest[row][col].getCellState() == 1)
			{
				cout << "^ ";
			}
			// print % for fire
			else
			{
				cout << "% ";
			}
		}
		cout << "\n";
	}

}

// check if a 1 (unburnt tree) exists in forest 
bool Grid::check()
{
	// loop through all entries in array
	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			// search for 1 state
			if (forest[row][col].getCellState() == 1)
			{
				return true;
			}
		}
	}
	return false;
}

// copies state of all cells
void Grid::burn()
{
	// loop through all entries in array
	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			// call save to copy state over
			forest[row][col].save();
		}
	}
}

void Grid::iterator()
{
	// loop until everything is on fire
	while (this->check())
	{
		// burn neighbour cells with 50% chance
		this->update();

		// save states of cells
		this->burn();

		// print();
		this->print();

		// get user to press return before each new iteration
		cout << "\nPlease press the 'Return' key to continue." << endl;

		// console waits for return keystroke
		// note: if user enters other chars then press return will perform several loops.
		cin.ignore();
	}
	// Explain sim is finished
	cout << "\nAll trees are gone! Press return to exit.";
	cin.ignore();
}

void Grid::inputs()
{
	/****************************
	*	User Instruction		*
	****************************/
	// dimension value and half for finding centre
	int dimension, halfDimension;

	// ask user to input a value for grid dimensions
	cout << "Please enter a number between 7 and 70 and press 'Return'. \n\nDimensions of the forest will be your input for both x and y. \n\nSimulation will continue until all trees are burned." << endl;

	// store user input in dimension
	cin >> dimension;

	
	/****************************
	*	Validation				*
	****************************/
	// if the users input is not between 7 and 70 or not a valid int, force a new input
	while (dimension < 7 || dimension > 70 || cin.fail())
	{
		// ask user to give another input
		cout << "The input was out of range, please enter a number between 7 and 70." << endl;

		// clear error from invalid input
		cin.clear();

		// ignore the incorect characters and go to next line
		cin.ignore(9999, '\n');

		// store user input in dimension
		cin >> dimension;
	}


	/****************************
	*	Creation of 2d array	*
	****************************/
	// give hd a value of half the user input to start fire at centre
	halfDimension = dimension / 2;

	// dynamically create pointer to Grid object, (dimensions of grid)
	Grid* grid = new Grid(dimension, dimension);

	// call Grid method [fire start cell][coords go here] 
	grid->forest[halfDimension][halfDimension].setCellState(2);
	cin.ignore();

	grid->iterator();
}

// checks NSEW neighbours and sets them on fire if they are not on fire and are not border cell
void Grid::update()
{
	// clear prev grid from console
	system("CLS");

	// loop through all entries in array
	for (int row = 0; row < numRows; row++)
	{
		for (int col = 0; col < numCols; col++)
		{
			if (forest[row][col].getOldState() == 2)
			{
				// if to left is not border and not already on fire
				if (row > 0 && forest[row - 1][col].getCellState() != 0 && forest[row - 1][col].getCellState() != 2)
				{
					// 50% set it on fire
					if (rand() % 2 == 1)
					{
						forest[row - 1][col].setCellState(2);
					}
				}
				// if to right is not border and not already on fire
				if (forest[row + 1][col].getCellState() != 0 && forest[row + 1][col].getCellState() != 2)
				{
					// 50% set it on fire
					if (rand() % 2 == 1)
					{
						forest[row + 1][col].setCellState(2);
					}
				}
				// if to above is not border and not already on fire
				if (col > 0 && forest[row][col - 1].getCellState() != 0 && forest[row][col - 1].getCellState() != 2)
				{
					// 50% set it on fire
					if (rand() % 2 == 1)
					{
						forest[row][col - 1].setCellState(2);
					}
				}
				// if below cell is not border and not already on fire
				if (forest[row][col + 1].getCellState() != 0 && forest[row][col + 1].getCellState() != 2)
				{
					// 50% set it on fire
					if (rand() % 2 == 1)
					{
						forest[row][col + 1].setCellState(2);
					}
				}
			}
		}
	}
}
