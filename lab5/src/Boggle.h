/*
 * Authors: wilmi895, maxra518
 * Contains the game logic for boggle.
 * Implements interfacing methods to update and retrieve game state.
 */

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "grid.h"
#include "lexicon.h"

using namespace std;

class Boggle {
public:
	const string DICTIONARY_FILE = "EnglishWords.dat";
	const int MIN_WORD_LENGTH	 = 4;
	const int BOARD_SIZE		 = 4;

	Boggle();

	Grid<char> const& getBoard() const;
	void initBoard(string const& cubes);
	void initBoard();
	void resetGame();
	static int numCubes();
	bool existsWord(string const& word) const;
	bool isMinimumWordLength(string const& word) const;
	bool alreadyGuessedWord(string const& word) const;

	int getPlayerScore() const;
	int getAiScore() const;

	set<string> const& getGuessedWords() const;
	bool findGuess(string const& word);
	set<string> findAllRemainingWords();


private:
	Grid<char> board;
	Lexicon lexicon;
	int playerScore = 0;
	int aiScore		= 0;
	set<string> guessedWords;
	set<pair<int, int>> visited;

	vector<pair<int, int>> getNeighbors(pair<int, int> const& node) const;
	void searchRemainingWords(string const& word,
							  pair<int, int> const& node,
							  set<string>& foundWords);
	bool searchWord(string const& word,
					int wordIndex,
					pair<int, int> const& node);
	bool alreadyVisited(pair<int, int> const& node) const;
	void updateAiScore(string const& word);
	void updatePlayerScore(string const& word);
};

#endif
