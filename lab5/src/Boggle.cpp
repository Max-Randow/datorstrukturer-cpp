/*
 * Authors: wilmi895, maxra518
 * Contains the game logic for boggle.
 * Implements interfacing methods to update and retrieve game state.
 */

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

/*
 * Gets the game board.
 */
Grid<char> const& Boggle::getBoard() const { return board; }

/*
 * Gets the player score.
 */
int Boggle::getPlayerScore() const { return playerScore; }

/*
 * Gets the ai score.
 */
int Boggle::getAiScore() const { return aiScore; }

/*
 * Gets the number of cubes on the board.
 */
int Boggle::numCubes() { return NUM_CUBES; }

/*
 * Initializes the board with a shuffled board.
 */
void Boggle::initBoard() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			int const randInt = randomInteger(0, CUBE_SIDES - 1);
			board.set(i, j, CUBES[i * BOARD_SIZE + j][randInt]);
		}
	}
	shuffle(board);
}

/*
 * Initializes the board with a custom configuration.
 */
void Boggle::initBoard(string const& cubes) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			board.set(i, j, cubes[i * BOARD_SIZE + j]);
		}
	}
}

/*
 * Resets the game state.
 */
void Boggle::resetGame() {
	playerScore = 0;
	aiScore		= 0;
	guessedWords.clear();
}

/*
 * Gets the guessed words.
 */
set<string> const& Boggle::getGuessedWords() const { return guessedWords; }

/*
 * Check if a word exists in the lexicon.
 */
bool Boggle::existsWord(string const& word) const {
	return lexicon.contains(word);
}

/*
 * Check if the word is atleast the minimum word length.
 */
bool Boggle::isMinimumWordLength(string const& word) const {
	return static_cast<int>(word.length()) >= MIN_WORD_LENGTH;
}

/*
 * Check if the word is already guessed.
 */
bool Boggle::alreadyGuessedWord(const string& word) const {
	return guessedWords.find(word) != guessedWords.end();
}

/*
 * Check if the node is already visited (a cube on the board).
 */
bool Boggle::alreadyVisited(pair<int, int> const& node) const {
	return visited.find(node) != visited.end();
}

/*
 * Update the player score with respect to the minimum word length.
 */
void Boggle::updatePlayerScore(string const& word) {
	playerScore += static_cast<int>(word.length()) - MIN_WORD_LENGTH + 1;
}

/*
 * Update the ai score with respect to the minimum word length.
 */
void Boggle::updateAiScore(string const& word) {
	aiScore += static_cast<int>(word.length()) - MIN_WORD_LENGTH + 1;
}

/*
 * Tries to find the guess on the board.
 */
bool Boggle::findGuess(string const& guess) {
	// Start the search from each position in the board until found.
	for (int i = 0; i < board.numRows(); i++) {
		for (int j = 0; j < board.numCols(); j++) {
			if (searchWord(guess, 0, make_pair(i, j))) {
				return true;
			}
		}
	}

	return false;
}

/*
 * Recursively searches for a word on the board and backtracks if
 * a path can't contain the word.
 */
bool Boggle::searchWord(string const& word,
						int const letterIndex,
						pair<int, int> const& node) {
	// When we have matched all letters to a letter in the board,
	// then the index is equal to the length.
	if (static_cast<size_t>(letterIndex) == word.length()) {
		visited.clear();
		guessedWords.insert(word);
		updatePlayerScore(word);
		return true;
	}
	// If the current letter does not match the letter in the
	// current board position, discard this path.
	if (word[letterIndex] != board[node.second][node.first]) {
		return false;
	}

	visited.insert(node);
	vector<pair<int, int>> const neighbors = getNeighbors(node);

	for (pair<int, int> const& neighbor : neighbors) {
		if (!alreadyVisited(neighbor) &&
			searchWord(word, letterIndex + 1, neighbor)) {
			return true;
		}
	}

	visited.erase(node);
	return false;
}

/*
 * Searches for all the remaining words (not already guessed) on the board.
 * Backtracks when more words can't be found on a path.
 */
void Boggle::searchRemainingWords(string const& word,
								  pair<int, int> const& startNode,
								  set<string>& foundWords) {
	vector<pair<int, int>> const neighbors = getNeighbors(startNode);

	for (pair<int, int> const& neighbor : neighbors) {
		if (alreadyVisited(neighbor)) {
			continue;
		}

		string const new_word = word + board[neighbor.second][neighbor.first];

		// Requirements to give score to the computer.
		// Word has to be minimum length, not guessed by the human player,
		// not already be found by the computer (palidromes or multiple words),
		// and the word has to exist.
		if (isMinimumWordLength(new_word) && !alreadyGuessedWord(new_word) &&
			foundWords.find(new_word) == foundWords.end() && existsWord(word)) {
			updateAiScore(new_word);
			foundWords.insert(new_word);
		}
		// The current word could be a prefix to another word, search further.
		// Even though it could also be an existing word which gives points.
		if (lexicon.containsPrefix(new_word)) {
			visited.insert(startNode);
			searchRemainingWords(new_word, startNode, foundWords);
			visited.erase(startNode);
		}
	}
}

/*
 * Finds all remaining words (not guessed already), starting from each position
 * on the board.
 */
set<string> Boggle::findAllRemainingWords() {
	set<string> foundWords {};
	for (int i = 0; i < board.numRows(); i++) {
		for (int j = 0; j < board.numCols(); j++) {
			searchRemainingWords("", make_pair(i, j), foundWords);
		}
	}
	return foundWords;
}

/*
 * Gets all neighbors to a cube node on the board.
 */
vector<pair<int, int>> Boggle::getNeighbors(pair<int, int> const& node) const {
	vector<pair<int, int>> neighbors {};
	int const x = node.first;
	int const y = node.second;

	for (int a = -1; a <= 1; ++a) {
		for (int b = -1; b <= 1; ++b) {
			int const row = a + x;
			int const col = b + y;
			if (board.inBounds(row, col) && !(row == x && col == y)) {
				neighbors.emplace_back(make_pair(row, col));
			}
		}
	}
	return neighbors;
}
