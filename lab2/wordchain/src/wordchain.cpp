/*
 * Author: wilmi895, maxra518
 * Lab 2a: Word Chain
 * Description:
 * Functions which transforms a english word into another
 * using one letter difference words. Also provides a dictionary helper
 * function for a english dictionary.
 */
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_set>
using namespace std;

const string ALPHABET = "abcdefghijklmnopqrstuvwxyz";

/*
 * Initialises the english dictionary from a dictionary file.
 */
unordered_set<string> init_dictionary(string const& file_name) {
	unordered_set<string> dictionary;
	string buffer;
	ifstream rfile(file_name);

	// Setup set with given dictionary
	while (getline(rfile, buffer)) {
		dictionary.insert(buffer);
	}
	return dictionary;
}

/*
 * Generates all the word neighbours, meaning word who differ by one letter
 * and exists in the english dictionary.
 */
vector<string> word_neighbours(string const& word,
							   unordered_set<string> const& dictionary) {
	vector<string> neighbours;

	// Change each letter in the word to find neighbour words.
	// Meaning word with a one letter difference.
	for (size_t i = 0; i < word.size(); i++) {
		string tmp_word = word;

		for (char const letter : ALPHABET) {
			tmp_word[i] = letter;
			// Adds word to the neighbour list if it exists in the dictionary,
			// the word itself is not a neighbour to itself
			if (tmp_word != word &&
				dictionary.find(tmp_word) != dictionary.end()) {
				neighbours.push_back(tmp_word);
			}
		}
	}
	return neighbours;
}

/*
 * Finds the shortest word chain between two words.
 * Uses BFS algorithm to explore neighbour words.
 */
stack<string> word_chain(string const& word1,
						 string const& word2,
						 unordered_set<string> const& dictionary) {
	// Initialize used words set with the starting word.
	unordered_set<string> used_words;
	used_words.insert(word1);

	// Initialize the first word chain with the starting word.
	stack<string> first_chain;
	first_chain.push(word1);

	queue<stack<string>> word_chains;
	word_chains.push(first_chain);

	// BFS algorithm to explore all word neighbours and find the shortest word
	// chain.
	while (!word_chains.empty()) {
		stack<string> partial_chain = move(word_chains.front());
		word_chains.pop();
		string const& last_chain_word = partial_chain.top();

		// If the last word in the chain matches target word, return chain
		if (last_chain_word == word2) {
			return partial_chain;
		}

		// Get all word neighbours to last word in chain.
		vector<string> const neighbours =
			word_neighbours(last_chain_word, dictionary);

		// Explore neighbour words.
		for (string const& neighbor_word : neighbours) {
			if (used_words.find(neighbor_word) == used_words.end()) {
				stack<string> chain_copy = partial_chain;
				chain_copy.push(neighbor_word);
				word_chains.push(chain_copy);
				used_words.insert(neighbor_word);
			}
		}
	}

	return {};
}

int main() {
	cout << "Welcome to TDDD86 Word Chain.\n";
	cout << "If you give me two English words, I will transform the\n";
	cout << "first into the second by changing one letter at a time.\n\n";

	const unordered_set<string> word_dict = init_dictionary("dictionary.txt");

	string word1;
	string word2;
	cout << "Please type two words: ";
	cin >> word1 >> word2;

	stack<string> chain = word_chain(word1, word2, word_dict);

	// Print out shortest chain in reverse order.
	while (!chain.empty()) {
		cout << chain.top() << ' ';
		chain.pop();
	}
	cout << '\n';

	return 0;
}
