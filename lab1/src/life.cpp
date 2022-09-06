/*
 * Authors: wilmi895, maxra518
 * Lab1: Game of Life
 * Description:
 * Simulates and animates conways game of life.
 * Provides interface for animating and ticking through
 * the generations.
 */

#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "grid.h"
#include "lifeutil.h"

using namespace std;

/*
 * Initializes a grid object with the initial state from a file.
 */
Grid<char> init_game_of_life(string const& file_name) noexcept {
	ifstream rfile(file_name, ios_base::in);

	int row_count = 0, col_count = 0;
	string buffer;

	// Read row count from file.
	getline(rfile, buffer);
	row_count = stoi(buffer);
	// Read column count from file.
	getline(rfile, buffer);
	col_count = stoi(buffer);

	Grid<char> game_of_life(row_count, col_count);
	buffer.reserve(static_cast<size_t>(row_count));

	for (int row = 0; row < row_count; row++) {
		getline(rfile, buffer);

		for (int col = 0; col < col_count; col++) {
			game_of_life.set(row, col, buffer[static_cast<size_t>(col)]);
		}
	}

	return game_of_life;
}

/*
 * Draws out a grid object.
 */
void draw_grid(Grid<char> const& grid) {
	for (int row = 0; row < grid.numRows(); ++row) {
		for (int col = 0; col < grid.numCols(); ++col) {
			cout << grid.get(row, col);
		}
		cout << '\n';
	}
}

/*
 * Returns updated position in the grid using rules from game of life
 */
char update_position(Grid<char> const& grid, int pos_row, int pos_col) {
	int alive_cells = 0;

	// Check for alive cells around position.
	for (int row = pos_row - 1; row < (pos_row + 2); ++row) {
		for (int col = pos_col - 1; col < (pos_col + 2); ++col) {
			if (grid.inBounds(row, col) && grid.get(row, col) == 'X' &&
				!(row == pos_row && col == pos_col)) {
				alive_cells++;
			}
		}
	}

	// Generation update rules.
	switch (alive_cells) {
	case 0 ... 1: return '-';
	case 2: return grid.get(pos_row, pos_col);
	case 3: return 'X';
	default: return '-';
	}
}

/*
 * Generates the next generation of game of life.
 */
Grid<char> tick(Grid<char> const& grid) {
	auto next_grid = grid;

	// Iterate through the entire grid and update each position.
	for (int row = 0; row < next_grid.numRows(); ++row) {
		for (int col = 0; col < next_grid.numCols(); ++col) {
			next_grid.set(row, col, update_position(grid, row, col));
		}
	}

	return next_grid;
}

/*
 * Animates game of life for 5 seconds.
 */
void animate(Grid<char>& game_of_life) {
	int const generations = 50;

	for (int i = 0; i < generations; i++) {
		pause(100);
		clearConsole();
		// Update with next generation of game of life.
		game_of_life = tick(game_of_life);
		draw_grid(game_of_life);
	}
}

/*
 * Loop which lets user input options to game of life.
 */
void game_loop(string const& file_name) {
	Grid<char> game_of_life = init_game_of_life(file_name);
	bool running			= true;
	draw_grid(game_of_life);

	while (running) {
		cout << "a)nimate, t)ick, q)uit ?";
		char choice = ' ';
		cin >> choice;

		switch (choice) {
		// Animates game of life for short period.
		case 'a': {
			animate(game_of_life);
			break;
		}
		// Ticks one generation in game of life.
		case 't': {
			game_of_life = tick(game_of_life);
			draw_grid(game_of_life);
			break;
		}
		// Quits game of life interface.
		case 'q': {
			running = false;
			break;
		}
		default: cout << "Invalid choice!\n";
		}
	}
}

int main() {
	cout << "Welcome to the TDDD86 Game of Life,"
			"\na simulation of the lifecycle of a bacteria colony."
			"\nCells (X) live and die by the following rules:"
			"\n - A cell with 1 or fewer neighbours dies."
			"\n - Locations with 2 neighbours remain stable."
			"\n - Locations with 3 neighbours will create life."
			"\n - A cell with 4 or more neighbours dies.\n\n";

	string file_name;
	cout << "Grid input file name? ";
	cin >> file_name;

	game_loop(file_name);

	cout << "Have a nice Life! " << endl;
	return 0;
}
