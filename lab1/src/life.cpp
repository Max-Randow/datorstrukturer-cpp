#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "grid.h"
#include "lifeutil.h"

using namespace std;

Grid<char> init_game_of_life(string const& file_name) noexcept {
	ifstream rfile(file_name, ios_base::in);

	const size_t header_size = 4;
	array<char, header_size> header {};
	rfile.read(header.data(), header_size);
	// Convert character to corresponding number.
	Grid<char> game_of_life(header[0] - '0', header[2] - '0');

	string line_buf;
	line_buf.reserve(static_cast<size_t>(game_of_life.numRows()));
	int row = 0;

	while (getline(rfile, line_buf)) {
		for (int col = 0; col < game_of_life.numCols(); col++) {
			game_of_life.set(row, col, line_buf[static_cast<size_t>(col)]);
		}
		row++;
	}

	return game_of_life;
}

int main() {
	// ios_base::sync_with_stdio(false);
	// cin.tie(NULL);

	Grid<char> game_of_life = init_game_of_life("simple.txt");


	cout << "Have a nice Life! " << endl;
	return 0;
}
