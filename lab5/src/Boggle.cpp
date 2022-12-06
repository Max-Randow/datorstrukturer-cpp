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

Grid<char> const& Boggle::getBoard() const { return board; }
int Boggle::getPlayerScore() const { return playerScore; }
int Boggle::getAiScore() const { return aiScore; }
int Boggle::numCubes() { return NUM_CUBES; }

void Boggle::initBoard() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			board.set(
				i, j,
				CUBES[i * BOARD_SIZE + j][randomInteger(0, CUBE_SIDES - 1)]);
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

bool Boggle::findGuess(string const& word) {
	for (int i = 0; i < board.numRows(); i++) {
		for (int j = 0; j < board.numCols(); j++) {
			if (board[i][j] == backtrack(word, 1, i, j)) {
				return true;
			}
		}
	}

	return false;
}


bool Boggle::backtrack(string word, int wordIndex, int i, int j) {
	if (wordIndex == word.length()) {
		return true;
	}

	auto node = make_pair(i, j);
	visited.insert(node);
	vector<pair<int, int>> neighbors = getNeighbors(i, j);

	for (pair<int, int> const& neighbor : neighbors) {
		if (alreadyVisited(neighbor)) {
			continue;
		}
		int const x			 = neighbor.first;
		int const y			 = neighbor.second;
		char const character = board[y][x];

		if (character == word[wordIndex]) {
			if (backtrack(word, wordIndex + 1, x, y)) {
				visited.erase(node);
				return true;
			}
		}
	}

	return false;
}


bool Boggle::alreadyVisited(pair<int, int> node) const {
	return visited.find(node) != visited.end();
}

vector<string> Boggle::findAllRemainingWords() const {}


vector<pair<int, int>> Boggle::getNeighbors(int const i, int const j) const {
	vector<pair<int, int>> neighbors {};

	for (int a = -1; a <= 1; ++a) {
		for (int b = -1; b <= 1; ++b) {
			int const row = a + i;
			int const col = b + j;
			if (board.inBounds(row, col) && !(row == i && col == j)) {
				neighbors.push_back(make_pair(row, col));
			}
		}
	}
	return neighbors;
}
