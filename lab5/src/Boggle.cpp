// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace it with your own

#include "Boggle.h"

#include <iostream>
#include <sstream>
#include <unordered_set>

#include "random.h"
#include "shuffle.h"
#include "strlib.h"

static const int NUM_CUBES	= 16;  // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] =
	{  // the letters on all 6 sides of every cube
		"AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS", "AOOTTW", "CIMOTU",
		"DEILRX", "DELRVY", "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
		"EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"};

Boggle::Boggle() : lexicon(DICTIONARY_FILE) {
	board.resize(BOARD_SIZE, BOARD_SIZE);
}

Grid<char> Boggle::getBoard() const { return board; }

void Boggle::initBoard() {
	
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			board.set(i, j,
					  CUBES[static_cast<size_t>(i * j)]
						   [randomInteger(0, CUBE_SIDES)]);
		}
	}
	shuffle(board);
}

void Boggle::initBoard(string cubes) {

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			board.set(i, j, cubes[static_cast<size_t>(i * j)]);
		}
	}
	shuffle(board);
}

int Boggle::getPlayerScore() const {
	return playerScore;
}

int Boggle::getAiScore() const {
	return aiScore;
}

unordered_set<string>const& Boggle::getGuessedWords() const{
	return guessedWords;
}

int Boggle::numCubes() const { return NUM_CUBES; }

bool Boggle::correctWordLength(const string& word) const {
	return word.length() >= static_cast<size_t>(MIN_WORD_LENGTH);
}
