/*
 * Author: wilmi895
 * File: encoding.cpp
 * Usage:
 * Defines functions for compressing a file using huffman encoding.
 * Contains several helper functions for constructing the frequencies
 * and the encoding tree used by the huffman algorithm.
 */
#include "encoding.h"

#include <queue>
#include <sstream>
#include <string>

using namespace std;

/*
 * Build huffman frequency table from stream input.
 */
map<int, int> buildFrequencyTable(istream& input) {
	map<int, int> freqTable;
	int character = input.get();

	while (!input.fail()) {
		freqTable[character]++;
		character = input.get();
	}
	freqTable[PSEUDO_EOF] = 1;
	return freqTable;
}

/*
 * Builds the huffman encoding tree from a character frequency table.
 */
HuffmanNode* buildEncodingTree(map<int, int> const& freqTable) {
	priority_queue<HuffmanNode> heap {};

	for (auto const& charFreq : freqTable) {
		heap.push(HuffmanNode(charFreq.first, charFreq.second));
	}

	// Continually join two nodes in a root node to create the tree.
	while (heap.size() > 1) {
		HuffmanNode root {};
		root.zero = new HuffmanNode(heap.top());
		heap.pop();
		root.one = new HuffmanNode(heap.top());
		heap.pop();
		root.count = root.zero->count + root.one->count;

		heap.push(root);
	}

	return new HuffmanNode(heap.top());
}

/*
 * Helper function for building the encoding map.
 */
void buildEncodingMapHelper(HuffmanNode const* const root,
							string encoding,
							map<int, string>& encodingMap) {
	if (root->isLeaf()) {
		encodingMap[root->character] = move(encoding);
		return;
	}

	buildEncodingMapHelper(root->zero, encoding + "0", encodingMap);
	buildEncodingMapHelper(root->one, encoding + "1", encodingMap);
}

/*
 * Builds the huffman encoding map using an encoding tree.
 */
map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
	map<int, string> encodingMap;

	buildEncodingMapHelper(encodingTree, "", encodingMap);

	return encodingMap;
}

/*
 * Converts a ascii char number to a decimal int.
 */
int asciiToDecimal(char const ascii) { return ascii - '0'; }

/*
 * Takes a string of bits and writes those bits to the output.
 */
void writeBits(string const& input, obitstream& output) {
	for (char const bit : input) {
		output.writeBit(asciiToDecimal(bit));
	}
}

/*
 * Encodes an input stream using huffman encoding.
 */
void encodeData(istream& input,
				map<int, string> const& encodingMap,
				obitstream& output) {
	int character = input.get();

	while (!input.fail()) {
		writeBits(encodingMap.at(character), output);
		character = input.get();
	}

	writeBits(encodingMap.at(PSEUDO_EOF), output);
}

/*
 * Decodes a huffman encoded input stream.
 */
void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
	HuffmanNode const* current_node = encodingTree;

	bool bit = static_cast<bool>(input.readBit());

	while (!input.fail()) {
		if (current_node->isLeaf()) {
			int const character = current_node->character;

			if (character == PSEUDO_EOF) {
				break;
			}
			output.put(static_cast<char>(character));
			current_node = encodingTree;

		} else {
			current_node = bit ? current_node->one : current_node->zero;
			bit			 = static_cast<bool>(input.readBit());
		}
	}
}

/*
 * Constructs and writes the header for a huffman encoded file.
 */
void writeHeader(obitstream& output, map<int, int> const& frequencyTable) {
	stringstream header;
	header << '{';

	for (pair<int, int> const frequency : frequencyTable) {
		header << frequency.first << ':' << frequency.second << ',';
	}
	// Overwrite last ','
	header.seekp(-1, stringstream::cur);
	header << '}';

	output.write(header.str().c_str(), header.tellp());
}

/*
 * Compresses input stream using Huffman encoding and places it in output
 * stream.
 */
void compress(istream& input, obitstream& output) {
	map<int, int> const frequencyTable = buildFrequencyTable(input);
	HuffmanNode* const encodingTree	   = buildEncodingTree(frequencyTable);
	map<int, string> const encodingMap = buildEncodingMap(encodingTree);
	freeTree(encodingTree);

	writeHeader(output, frequencyTable);
	input.clear();
	input.seekg(0, ios::beg);
	encodeData(input, encodingMap, output);
}

/*
 * Reads in header from huffman encoded file.
 */
map<int, int> readHeader(ibitstream& input) {
	map<int, int> frequencyTable {};
	string character;
	string frequency;
	int byte = input.get();

	while (!input.fail() && byte != '}') {
		byte = input.get();

		// Read a character from the header.
		while (!input.fail() && byte != ':') {
			character += to_string(asciiToDecimal(byte));
			byte = input.get();
		}

		// Read a frequency for a character from the header.
		byte = input.get();
		while (!input.fail() && byte != ',' && byte != '}') {
			frequency += to_string(asciiToDecimal(byte));
			byte = input.get();
		}

		// Store the character/frequency pair as integers.
		frequencyTable[stoi(character)] = stoi(frequency);
		character.clear();
		frequency.clear();
	}

	return frequencyTable;
}

/*
 * Decompresses a huffman encoded input stream and places it in output stream.
 */
void decompress(ibitstream& input, ostream& output) {
	map<int, int> frequencyTable	= readHeader(input);
	HuffmanNode* const encodingTree = buildEncodingTree(frequencyTable);
	decodeData(input, encodingTree, output);
	freeTree(encodingTree);
}

/*
 * Frees a huffmantree
 */
void freeTree(HuffmanNode* node) {
	if (node == nullptr) {
		return;
	}
	if (!node->isLeaf()) {
		freeTree(node->zero);
		freeTree(node->one);
	}
	delete node;
}
