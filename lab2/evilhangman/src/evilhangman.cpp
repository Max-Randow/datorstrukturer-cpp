#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";


/*
 * Initializes the english dictionary and a set of available word lengths
 * in the dictionary.
 */
pair<vector<string>, unordered_set<size_t>> init_dictionary(
	string const& file_name) noexcept {
	ifstream rfile(file_name);
	vector<string> dictionary;
	unordered_set<size_t> word_lengths;
	string buffer;

	while (getline(rfile, buffer)) {
		dictionary.push_back(buffer);
		word_lengths.insert(buffer.length());
	}
	return make_pair(dictionary, word_lengths);
}

bool inAlphabet(char const letter) noexcept {
	return binary_search(ALPHABET.cbegin(), ALPHABET.cend(), letter);
}

template<template<typename...> class Container, typename T>
bool valueExists(T const& value, Container<T> const& set) {
	return set.find(value) != set.cend();
}


struct GameSettings {
	bool show_words_left;
	size_t word_length;
	int guess_count;
};

bool AskUserYesNo(string const& message) noexcept {
	string choice;

	while (true) {
		cout << message << " (y/n): ";
		cin >> choice;

		if (choice == "y") {
			return true;
		} else if (choice == "n") {
			return false;
		}
	}
}

GameSettings setup_game(unordered_set<size_t> const& word_lengths) {
	size_t wanted_word_len = 0;

	while (true) {
		cout << "Choose the word size: ";
		cin >> wanted_word_len;

		if (valueExists(wanted_word_len, word_lengths)) {
			break;
		}
		cout << "No words exist with length " << wanted_word_len << '\n';
	}


	int guess_count = 0;

	while (true) {
		cout << "Choose amount of guesses: ";
		cin >> guess_count;

		if (guess_count > 0) {
			break;
		}
		cout << "Guesses have to be greater than 0!\n";
	}

	bool show_words_left = AskUserYesNo("Show words left after each guess?");

	return {show_words_left, wanted_word_len, guess_count};
}

void game_loop(vector<string> const& dictionary,
			   unordered_set<size_t> const& word_lengths) {
	while (true) {
		unordered_set<char> guessed_letters;
		GameSettings settings = setup_game(word_lengths);
		int guesses_left	  = settings.guess_count;
		string current_word_version(settings.word_length, '-');

		vector<string> equal_len_words;
		copy_if(dictionary.cbegin(), dictionary.cend(),
				back_inserter(equal_len_words),
				[&settings](string const& word) {
					return word.length() == settings.word_length;
				});

		// Guess loop.
		while (true) {
			cout << "Guesses left: " << guesses_left << '\n';
			cout << "Letters guessed: ";
			for (char const letter : guessed_letters) {
				cout << letter << ' ';
			}
			cout << '\n';
			cout << current_word_version << '\n';
			// TODO: fix write out words left after guess :)


			char guess = ' ';
			while (true) {
				cout << "Enter guess: ";
				string buffer;
				cin >> buffer;

				if (buffer.length() > 1) {
					cout << "Guess a single character.\n";
					continue;
				}
				guess = buffer[0];

				if (!inAlphabet(guess)) {
					cout << "Character not in alphabet.\n";
				} else if (valueExists(guess, guessed_letters)) {
					cout << "Letter already guessed, guess another.\n";
				} else {
					break;
				}
			}

			unordered_map<string, vector<string>> word_families;

			// TODO: partition words
			for (string const& word : dictionary) {
				string family_key;

				for (size_t i = 0; i < word.length(); ++i) {
					if (word[i] == guess) {
						family_key += to_string(i);
					}
				}
				word_families[family_key].push_back(word);
			}
		}

		// Utökning: Vikt ordklasser med hur många unika gissningar de har.
		//  Har vissa ord multipla bokstäver kommer de krävas färre gissningar
		if (!AskUserYesNo("Play again?")) {
			break;
		}
	}
}

int main() {
	auto init_pair							 = init_dictionary("di.txt");
	vector<string> const dictionary			 = move(init_pair.first);
	unordered_set<size_t> const word_lengths = move(init_pair.second);

	cout << "Welcome to Hangman.\n";

	game_loop(dictionary, word_lengths);

	return 0;
}
