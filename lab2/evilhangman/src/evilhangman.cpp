#include <algorithm>
#include <fstream>
#include <iostream>
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
	string const& file_name) {
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

int main() {
	auto init_pair					= init_dictionary("dictionary.txt");
	vector<string> const dictionary = move(init_pair.first);
	unordered_set<size_t> const word_lengths = move(init_pair.second);

	cout << "Welcome to Hangman.\n";
	size_t wanted_word_len = 0;

	while (true) {
		cout << "Choose the word size: ";
		cin >> wanted_word_len;

		if (word_lengths.find(wanted_word_len) != word_lengths.end()) {
			break;
		}
		cout << "No words exist with length " << wanted_word_len << '\n';
	}


	vector<string> equal_len_words;
	copy_if(dictionary.cbegin(), dictionary.cend(), equal_len_words.begin(),
			[&wanted_word_len](string const& word) {
				return word.length() == wanted_word_len;
			});

	// Maps string with indicies of equal letters to word families.
	unordered_map<string, vector<string>> word_families;
	// The same but the size of each family.
	unordered_map<string, size_t> word_familiy_sizes;

	return 0;
}
