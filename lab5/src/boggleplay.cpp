// You will edit and turn in this CPP file.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace with your own

#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <sstream>
#include <unordered_set>

#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"

void drawBoggleBoard(Boggle const& board);
void drawScore(Boggle const& board);

bool isAlphaString(string const& config) {
	return config.length() == 16 &&
		   std::all_of(config.begin(), config.end(),
					   [](unsigned char c) { return std::isalpha(c); });
}

bool askCustomBoardConfig(Boggle& boggle) {
	if (!yesOrNo("Use custom configuration?")) {
		return false;
	}
	while (true) {
		cout << "Enter 16 characters to use:\n";
		string config;
		cin >> config;
		if (config.length() == boggle.numCubes() && isAlphaString(config)) {
			// Convert config string to lowercase.
			std::transform(config.begin(), config.end(), config.begin(),
						   [](unsigned char c) { return std::tolower(c); });
			boggle.initBoard(config);
			break;
		}

		cout << "Enter only alphanumeric characters\n";
	}

	return true;
}

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
	// TODO: implement this function (and add any other functions you like to
	// help you)
	if (!askCustomBoardConfig(boggle)) {
		boggle.initBoard();
	}

	while (true) {
	drawBoggleBoard(boggle);
	drawScore(boggle);
	string guess;
	cout<<"Type a word (or press enter to end your turn): "<<endl;
	cin>>guess;
	if (guess.empty()) {
		break;
	}
	else if (!boggle.validWord(guess)){
		cout<<"Invalid Word, guess again"<<endl;

	}
	if (boggle.alreadyGuessedWord(guess)) {
		cout<<"Word already guessed"<<endl;
		
	
	}
	

	}



}
void drawScore(Boggle const& boggle){
	//int playerScore = boggle.getPlayerScore();
	unordered_set<string> guessedWords = boggle.getGuessedWords();

	cout<<"Your words(" << guessedWords.size() << "):\n";
	cout<<"{"<<endl;
	for(string word : guessedWords){
		cout<<"\""<<word<<"\" \n";
	}
	cout<<"}"<<endl;
	cout<<"Your Score: "<< guessedWords.size() <<endl;



}

void drawBoggleBoard(Boggle const& boggle) {
	Grid<char> board = boggle.getBoard();

	for (int i = 0; i < board.nCols; i++) {
		for (int j = 0; j < board.nCols; j++) {
			cout << board.get(i, j);
		}
		cout << '\n';
	}
	cout << '\n';
}

/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
	std::system("CLS");
#else
	// assume POSIX
	std::system("clear");
#endif
}
