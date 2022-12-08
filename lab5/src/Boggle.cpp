// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace it with your own

#include "Boggle.h"

#include <iostream>
#include <sstream>
#include <unordered_set>
#include <utility>

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
			int const randInt = randomInteger(0, CUBE_SIDES - 1);
			board.set(i, j, CUBES[i * BOARD_SIZE + j][randInt]);
		}
	}
	shuffle(board);
}

void Boggle::initBoard(string const& cubes) {
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

bool Boggle::alreadyVisited(pair<int, int> const& node) const {
	return visited.find(node) != visited.end();
}

void Boggle::updatePlayerScore(string const& word) {
	playerScore += word.length() - static_cast<size_t>(MIN_WORD_LENGTH + 1);
}

void Boggle::updateAiScore(string const& word) {
	aiScore += word.length() - static_cast<size_t>(MIN_WORD_LENGTH + 1);
}

bool Boggle::findGuess(string const& word) {
	for (int i = 0; i < board.numRows(); i++) {
		for (int j = 0; j < board.numCols(); j++) {
			if (searchWord(word, 0, make_pair(i, j))) {
				return true;
			}
		}
	}
	return false;
}


bool Boggle::searchWord(string const& word,
						int const wordIndex,
						pair<int, int> const& node) {
	if (static_cast<size_t>(wordIndex) == word.length()) {
		return true;
	}
	if (word[wordIndex] != board[node.second][node.first]) {
		return false;
	}
	visited.insert(node);
	vector<pair<int, int>> const neighbors = getNeighbors(node);

	for (pair<int, int> const& neighbor : neighbors) {
		if (!alreadyVisited(neighbor) &&
			searchWord(word, wordIndex + 1, neighbor)) {
			visited.erase(neighbor);
			return true;
		}
	}
	visited.erase(node);

	return false;
}

void Boggle::searchRemainingWords(string const& word,
								  pair<int, int> const& startNode,
								  unordered_set<string>& foundWords) {
	visited.insert(startNode);
	vector<pair<int, int>> const neighbors = getNeighbors(startNode);

	for (pair<int, int> const& neighbor : neighbors) {
		if (alreadyVisited(neighbor)) {
			continue;
		}
		string const new_word = word + board[neighbor.second][neighbor.first];

		if (lexicon.contains(new_word) && alreadyGuessedWord(new_word)) {
			updateAiScore(new_word);
			foundWords.insert(new_word);
		}
		if (lexicon.containsPrefix(new_word)) {
			searchRemainingWords(new_word, startNode, foundWords);
		}
	}
	visited.erase(startNode);
}

unordered_set<string> Boggle::findAllRemainingWords() {
	unordered_set<string> foundWords {};
	for (int i = 0; i < board.numRows(); i++) {
		for (int j = 0; j < board.numCols(); j++) {
			searchRemainingWords("", make_pair(i, j), foundWords);
		}
	}
	return foundWords;
}

vector<pair<int, int>> Boggle::getNeighbors(pair<int, int> const& node) const {
	vector<pair<int, int>> neighbors {};
	int const i = node.first;
	int const j = node.second;

	for (int a = -1; a <= 1; ++a) {
		for (int b = -1; b <= 1; ++b) {
			int const row = a + i;
			int const col = b + j;
			if (board.inBounds(row, col) && !(row == i && col == j)) {
				neighbors.emplace_back(make_pair(row, col));
			}
		}
	}
	return neighbors;
}
