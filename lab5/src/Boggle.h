// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header and replace it with your own

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>

#include "grid.h"
#include "lexicon.h"

using namespace std;

class Boggle {
public:
	const string DICTIONARY_FILE = "EnglishWords.dat";
	const int MIN_WORD_LENGTH	 = 4;
	const int BOARD_SIZE		 = 4;

	Boggle();

	Grid<char> getBoard() const;
	void initBoard(string cubes);
	void initBoard();
	static int numCubes();
	bool correctWordLength(const string& word) const;

private:
	Grid<char> board;
	Lexicon lexicon;
};

#endif
