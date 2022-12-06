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

static const int NUM_CUBES	   = 16;  // the number of cubes in the game
static const int CUBE_SIDES	   = 6;	  // the number of sides on each cube
static string CUBES[NUM_CUBES] = {	// the letters on all 6 sides of every cube
	"AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS", "AOOTTW", "CIMOTU",
	"DEILRX", "DELRVY", "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
	"EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"};

Boggle::Boggle() : lexicon(DICTIONARY_FILE) {
	board.resize(BOARD_SIZE, BOARD_SIZE);
}

Grid<char> Boggle::getBoard() const { return board; }
int Boggle::getPlayerScore() const { return playerScore; }
int Boggle::getAiScore() const { return aiScore; }
int Boggle::numCubes() { return NUM_CUBES; }

void Boggle::initBoard() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			board.set(i, j,
					  CUBES[i * BOARD_SIZE + j][randomInteger(0, CUBE_SIDES)]);
		}
	}
	shuffle(board);
}

void Boggle::initBoard(string cubes) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			board.set(i, j, cubes[i * BOARD_SIZE + j]);
		}
	}
	shuffle(board);
}

unordered_set<string> const& Boggle::getGuessedWords() const {
	return guessedWords;
}

bool Boggle::validWord(const string& word) const {
	return word.length() >= static_cast<size_t>(MIN_WORD_LENGTH) &&
		   lexicon.contains(word);
}

bool Boggle::alreadyGuessedWord(const string& word) const {
	return guessedWords.find(word) != guessedWords.end();
}

void Boggle::updatePlayerScore(string const& word) {
	playerScore += word.length() - 3;
}

bool Boggle::findValidWord(string const& word) const {}

vector<string> Boggle::findAllRemainingWords() const {}




vector<pair<int, int>> Boggle::getNeighbors(int const i, int const j) const {
	vector<pair<int, int>> neighbors {};

	for(int a = -1; a<=1; ++a){
		for(int b = -1; b<=1; ++b){
			if(board.inBounds(a+i, b+j)){
				neighbors.push_back(make_pair(i,j));
			}
		}
	}
	return neighbors;
}
