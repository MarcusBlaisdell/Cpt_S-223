#ifndef PA_2_H
#define PA_2_H

#include "HuffmanTree.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "BinaryFile.h"
#include "StringSplitter.h"


using namespace std;

class PA2
{
public:
	//PA #2 TODO: finds the smallest tree in a given forest, allowing for a single skip
	static int findSmallestTree(vector<HuffmanTree<char> *> forest, int index_to_ignore = -1);

	//PA #2 TOOD: Generates a Huffman character tree from the supplied text
	static HuffmanTree<char> *huffmanTreeFromText(vector<string> data);

	//PA #2 TODO: Generates a Huffman character tree from the supplied encoding map
	//NOTE: I used a recursive helper function to solve this!
	static HuffmanTree<char> *huffmanTreeFromMap(unordered_map<char, string> huffmanMap);
		// huffmanTreeFromMap recursive helper function
	static HuffmanNode <char> * huffmanTreeHelper(HuffmanNode<char> *myRoot, char myValue, string myPath);

	//PA #2 TODO: Generates a Huffman encoding map from the supplied Huffman tree
	//NOTE: I used a recursive helper function to solve this!
	static unordered_map<char, string> huffmanEncodingMapFromTree(HuffmanTree<char> *tree);
		// recursive helper function for huffmanEncodingMapFromTree
	// static unordered_map<char, string> PA2::encodeHelperFunction(HuffmanInternalNode<char> *myTree, string myString, 
	//		unordered_map<char, string> myHash);
	static unordered_map<char, string> PA2::encodeHelperFunction(HuffmanNode<char> *myTree, string myString,
		unordered_map<char, string> &myHash);

	//PA #2 TODO: Writes an encoding map to file.  Needed for decompression.
	static void writeEncodingMapToFile(unordered_map<char, string> huffmanMap, string file_name);

	//PA #2 TODO: Reads an encoding map from a file.  Needed for decompression.
	static unordered_map<char, string> readEncodingMapFromFile(string file_name);

	//PA #2 TODO: Converts a vector of bits (bool) back into readable text using the supplied Huffman map
	static string decodeBits(vector<bool> bits, unordered_map<char, string> huffmanMap);

	//PA #2 TODO: Using the supplied Huffman map compression, converts the supplied text into a series of bits (boolean values)
	static vector<bool> toBinary(vector<string> text, unordered_map<char, string> huffmanMap);

};

#endif
