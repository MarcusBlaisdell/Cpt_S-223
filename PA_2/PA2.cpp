#include "PA2.h"
#include <queue>

//PA #2 TODO: finds the smallest tree in a given forest, allowing for a single skip
int PA2::findSmallestTree(vector<HuffmanTree<char> *> forest, int index_to_ignore)
// int PA2::findSmallestTree(vector<HuffmanTree<char> > forest, int index_to_ignore)
{
	//Finds the smallest tree (by weight) in the supplied forest.  
	//Note that this function accepts a second optional parameter of an index to skip.  
	//Use this index to allow your function to also find the 2nd smallest tree in the 
	//forest.
	
	// iterate through our vector and find the smallest tree:

		// declare variables, we need a temp Huffman Tree and ints for
		// the smallest and second smallest, initialize smallest to first 
		// weight
	
	int mySmallest = 0, returnSmallest = 0;

	if (index_to_ignore != 0)
	{
		mySmallest = forest[0]->getWeight();
	}
	else
	{
		mySmallest = forest[1]->getWeight();
		returnSmallest = 1;
	}

		// iterate through our vector to find the smallest or the second smallest
		// if we have an index to skip

	for (int i = 0; i < forest.size(); i++)
	{
			// get the smallest weight and return its index in the vector

		if ((forest[i]->getWeight() < mySmallest) && (i != index_to_ignore))
		{
			mySmallest = forest[i]->getWeight();
			returnSmallest = i;

		} // end if new value is smaller than previous, set smallest to new value

	} // end for loop to find smallest

	return returnSmallest;

	// return -1;
}

//PA #2 TOOD: Generates a Huffman character tree from the supplied text
HuffmanTree<char>* PA2::huffmanTreeFromText(vector<string> data)
{
	//Builds a Huffman Tree from the supplied vector of strings.
	//This function implement's Huffman's Algorithm as specified in page 
	//456 of the book.

	//In order for your tree to be the same as mine, you must take care 
	//to do the following:
	//1.	When merging the two smallest subtrees, make sure to place the 
	//      smallest tree on the left side!
	//2.	Have the newly created tree take the spot of the smallest 
	//		tree in the forest(e.g.vector[smallest] = merged_tree).
	//3.	Use vector.erase(begin() + second_smallest_index) to remove 
	//      the other tree from the forest.

		// first we need our frequency map, read each string from the 
		// vector of strings and if the character has not been read 
		// already, create a new huffmanNode, store it in a vector of 
		// huffman nodes.
		// if the character has been encountered before (is in our vector), 
		// increment its weight

		// create our unordered_map of frequencies:
	unordered_map <char, int > newFrequencyMap;

		// read through our vector of strings and build our map:

		// while our vector still has strings:
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data[i].size(); j++)
		{
				newFrequencyMap[data[i][j]]++;
		} // end for loop to read all positions in our individual string

	} // end while vector of strings still has lines

		// create a forest of HuffmanTrees from all of the values in our hash table

	vector<HuffmanTree <char> *> myForest;

	// iterate through the hash table and create a huffman tree for each element
	// and then push that tree onto my forest vector

	for (auto myIterator = newFrequencyMap.begin(); myIterator != newFrequencyMap.end(); ++myIterator)
	{
			// create HuffmanTreeLeafNodes
		HuffmanTree<char> * tempTree = new HuffmanTree<char>(myIterator->first, myIterator->second);

		myForest.push_back(tempTree);
		
	}  // end iterate through hash table
	
		// merge all of our trees into one
		// iterate until we have only one element in our vector
	while (myForest.size() > 1)
	{
		// set smallest and second smallest
		
		int mySmallest = 0;
		int secondSmallest = 0;

			// find smallest and second smallest indexes
		mySmallest = findSmallestTree(myForest, -1);
		secondSmallest = findSmallestTree(myForest, mySmallest);

			// take our two smallest HuffmanTrees and make a new Huffman tree with them,
			// set our smallest index to our new tree
		
		HuffmanTree<char> *tempTree = new HuffmanTree<char>(myForest[mySmallest], myForest[secondSmallest]);		
		myForest[mySmallest] = tempTree;

			// and delete our second smallest index
	 	myForest.erase(myForest.begin() + secondSmallest);

	} // end while loop to go through whole forest 
	
	return myForest[0];

}

//PA #2 TODO: Generates a Huffman character tree from the supplied encoding map
//NOTE: I used a recursive helper function to solve this!
HuffmanTree<char>* PA2::huffmanTreeFromMap(unordered_map<char, string> huffmanMap)
{
	//Generates a Huffman Tree based on the supplied Huffman Map. Recall that a 
	//Huffman Map contains a series of codes(e.g. 'a' = > 001).Each digit(0, 1) 
	//in a given code corresponds to a left branch for 0 and right branch for 1.

	HuffmanTree <char> *returnTree = new HuffmanTree <char> (nullptr);

	for (auto myIterator = huffmanMap.begin(); myIterator != huffmanMap.end(); myIterator++)
	{

		char myValue = myIterator->first;
		string myPath = myIterator->second;

		huffmanTreeHelper(returnTree->getRoot(), myValue, myPath);
	}

	return returnTree;
}

HuffmanNode<char> * PA2::huffmanTreeHelper(HuffmanNode<char> *myRoot, char myValue, string myPath)
{
		// base case is building leaf node
		// adding internal node
			// does internal exist

		// base case
	
	if (myPath.empty())
	{
		HuffmanLeafNode<char>*newNode = new HuffmanLeafNode<char>(myValue, 0);
		return newNode;
	} // end if our string is empty
	
	else if (!myPath.empty() && myRoot != nullptr)
	{
		myPath.erase(myPath.begin());
		if (myPath[0] == '0')
		{
			myPath.erase(myPath.begin());
			HuffmanInternalNode <char>*newInternal = dynamic_cast <HuffmanInternalNode <char> *>(myRoot);
			newInternal->setLeftChild(huffmanTreeHelper
				(dynamic_cast <HuffmanInternalNode<char> *>(myRoot)->getLeftChild(), myValue, myPath));
		} // end if path is left

		if (myPath[0] == '1')
		{
			
			HuffmanInternalNode <char>*newInternal = dynamic_cast <HuffmanInternalNode <char> *>(myRoot);
			newInternal->setRightChild(huffmanTreeHelper
				(dynamic_cast <HuffmanInternalNode<char> *>(myRoot)->getRightChild(), myValue, myPath));
		} // end if path is left 
	} // end if string is not emptys
	else if (myRoot == nullptr)
	{
		myPath.erase(myPath.begin());
		HuffmanInternalNode <char>* newInternal = new HuffmanInternalNode <char>(nullptr, nullptr);
		if (myPath[0] == '0')
		{
			//HuffmanInternalNode <char>*newInternal = dynamic_cast <HuffmanInternalNode <char> *>(myRoot);
			// dynamic_cast <HuffmanInternalNode<char>*>(newInternal)->setLeftChild(huffmanTreeHelper
			// 	(dynamic_cast <HuffmanInternalNode<char> *>(newInternal)->getLeftChild(), myValue, myPath));
			dynamic_cast <HuffmanInternalNode<char>*>(newInternal)->setLeftChild(huffmanTreeHelper
				(newInternal->getLeftChild(), myValue, myPath));
		} // end if path is left

		if (myPath[0] == '1')
		{
			// HuffmanInternalNode <char>*newInternal = dynamic_cast <HuffmanInternalNode <char> *>(myRoot);
			newInternal->setRightChild(huffmanTreeHelper
				(newInternal->getRightChild(), myValue, myPath));
		} // end if path is left 
	} // end create new internal node

} // end huffmanTreeHelper function

//PA #2 TODO: Generates a Huffman encoding map from the supplied Huffman tree
//NOTE: I used a recursive helper function to solve this!
unordered_map<char, string> PA2::huffmanEncodingMapFromTree(HuffmanTree<char> *tree)
{
	//Generates a Huffman Map based on the supplied Huffman Tree.  Again, recall 
	//that a Huffman Map contains a series of codes(e.g. 'a' = > 001).Each digit(0, 1) 
	//in a given code corresponds to a left branch for 0 and right branch for 1.  
	//As such, a given code represents a pre-order traversal of that bit of the 
	//tree.  I used recursion to solve this problem.

	unordered_map<char, string> result{};
	string theString("");

		// if our tree is empty, return an empty hash table
	if (tree->getRoot() == nullptr)
	{
		return result;
	} // end if root is empty
	
	/*
		// if our root is a leaf, hash it
	if (tree->getRoot()->isLeaf())
	
		// HuffmanTree<char> *newTree = tree;
		HuffmanNode<char> *newRoot = tree->getRoot();
		HuffmanLeafNode<char> *newLeaf = dynamic_cast<HuffmanLeafNode<char>*>(newRoot);
		
		result.insert({ newLeaf->getValue (), 0 });
	} // end if root is a leaf
	*/

		// otherwise, use recursive function to fill our hash table

	// HuffmanTree<char> *newTree = tree;
	// cout << "newTree: " << newTree->getWeight() << endl;

	// HuffmanTree<char>* some_tree = tree;
	// HuffmanNode<char> *generic_root = tree->getRoot();
	// HuffmanInternalNode<char>* i_root = dynamic_cast<HuffmanInternalNode<char>*>(generic_root);

	// result = PA2::encodeHelperFunction(i_root, theString, -result);
	result = PA2::encodeHelperFunction(tree->getRoot(), theString, result);
	
	return result;
}

// PA #2 Recursive Helper function for huffmanEncodingMapFromTree
// unordered_map<char, string> PA2::encodeHelperFunction(HuffmanInternalNode<char> *myTree, string myString,
//	unordered_map<char, string> myHash)
//
// Adam changed this to accept a HuffmanNode during office hours, it works so I'm using it

unordered_map<char, string> PA2::encodeHelperFunction(HuffmanNode<char> *myTree, string myString, 
 		unordered_map<char, string> &myHash)
{
	/////
	// is leaf?
	// yes? hash value and string
	// if left node:
	// add "0" to string, call function, pass string
	// is right node:
	// remove the left "0" we just added, 
	// add "1" to string to replace the "0", call function, pass string
	/////
	
		// base case, our node is a leaf
	if (myTree->isLeaf())
	{
		cout << "isLeaf" << endl;
			// cast to leaf node
		HuffmanLeafNode<char> *newLeaf = dynamic_cast<HuffmanLeafNode<char>*>(myTree);
		cout << "newLeaf: " << newLeaf->getValue() << endl;
			// add to hash table
		myHash.insert({ newLeaf->getValue(), myString });
	} // end base case, root is a leaf

	else
	{
		HuffmanInternalNode<char>* i_root = dynamic_cast<HuffmanInternalNode<char>*>(myTree);

		if (i_root->getLeftChild() != nullptr)
		{
			cout << "left child" << endl;
			myString += "0";
			cout << "string" << myString << endl;
			HuffmanNode<char> *rootLeft = i_root->getLeftChild();
			myHash = encodeHelperFunction(rootLeft, myString, myHash);
		} // end add a zero if there is a left child

		if (i_root->getRightChild() != nullptr)
		{
			cout << "right child" << endl;
				// we just added a 0, now we need to put a 1 in so we need to erase the 0:
			myString.erase(myString.size() - 1);
			myString += "1";
			HuffmanNode<char> *rootRight = i_root->getRightChild();
			myHash = encodeHelperFunction(rootRight, myString, myHash);
		} // end add a zero if there is a right child
	} // end else

	return myHash;

} // end encodeHelperFunction

//PA #2 TODO: Writes an encoding map to file.  Needed for decompression.
void PA2::writeEncodingMapToFile(unordered_map<char, string> huffmanMap, string file_name)
{
	//Writes the supplied encoding map to a file.  My map file has one 
	//association per line (e.g. 'a' and 001).  Each association is separated by 
	//a sentinel value.  In my case, I went with a double pipe (||).

		// open our output file
	ofstream output_file(file_name);

		// iterate through our hash table and output each element to our output file
	for (auto myIterator = huffmanMap.begin(); myIterator != huffmanMap.end(); ++myIterator)
	{
		output_file << myIterator->first << "||" << myIterator->second << endl;
	}  // end iterate through hash table

		// close the file
	output_file.close();
}

//PA #2 TODO: Reads an encoding map from a file.  Needed for decompression.
unordered_map<char, string> PA2::readEncodingMapFromFile(string file_name)
{
	//Creates a Huffman Map from the supplied file.Essentially, this is the 
	//inverse of writeEncodingMapToFile.  Be sure to use my StringSplitter class 
	//to make your life easier!
	unordered_map<char, string> result{};

	ifstream input_file (file_name);

	if (input_file.is_open() == true)
	{
			// declare a string to store our line by line input
		string line = "";
			
			// while our input file is valid
		while (input_file.good() == true)
		{
				// if our input line is valid
			if (getline(input_file, line))
			{
					// use his parser
				vector<string> pieces = StringSplitter::split(line, "||");

					// first element is our key, second is our value
				
				result.insert({pieces[0][0], pieces[1]});
				cout << "pieces 0 0: " << pieces[0][0] << endl;
			} // end if we got information, put it in our hash table
		} // end while input file is valid
	} // end if our file was opened successfully

	return result;
}

//PA #2 TODO: Converts a vector of bits (bool) back into readable text using the supplied Huffman map
// string PA2::decodeBits(vector<bool> bits, unordered_map<char, string> huffmanMap)
string PA2::decodeBits(vector<bool> bits, unordered_map<char, string> huffmanMap)
{
	//Uses the supplied Huffman Map to convert the vector of bools (bits) back into text.
	//To solve this problem, I converted the Huffman Map into a Huffman Tree and used 
	//tree traversals to convert the bits back into text.

	ostringstream result{};

	HuffmanTree<char> *myTree = huffmanTreeFromMap (huffmanMap);

	HuffmanInternalNode <char> *tempTree = dynamic_cast <HuffmanInternalNode<char>*> (myTree);
	cout << "tempTree, Right: " << tempTree->getRightChild() << endl;

		// iterate through bits and convert to string
	for (int i = 0; i < bits.size(); i++)
	{
		if (bits[i] == 0)
		{
			if (tempTree->getLeftChild()->isLeaf())
			{
				HuffmanLeafNode<char> *theLeft = dynamic_cast <HuffmanLeafNode<char>*> (tempTree->getLeftChild());
				result << theLeft->getValue();
			}
			else
			{
				HuffmanInternalNode<char> *tempChild =
					dynamic_cast <HuffmanInternalNode <char> *> (tempTree->getLeftChild());
				// HuffmanTree<char> *tempTree = new HuffmanTree<char>(tempChild);
			}

		} // end if 0

		if (bits[i] == 1)
		{
			if (tempTree->getRightChild() != nullptr)
			{
				HuffmanNode<char> *rootRight = tempTree->getRightChild();
			}
			HuffmanInternalNode<char> *rootRight = dynamic_cast <HuffmanInternalNode<char>*> (rootRight);
			if (rootRight->isLeaf())
			{
				HuffmanLeafNode <char> *theRight = dynamic_cast <HuffmanLeafNode<char>*> (tempTree->getRightChild());
				result << theRight->getValue();
			}
			else
			{
				HuffmanInternalNode<char> *tempChild =
					dynamic_cast <HuffmanInternalNode <char> *> (tempTree->getRightChild());
				// HuffmanTree<char> *tempTree = new HuffmanTree<char>(tempChild);
			}

		} // end if 1

	} // end for 

	return result.str();
}

//PA #2 TODO: Using the supplied Huffman map compression, converts the supplied text into a series of bits (boolean values)
vector<bool> PA2::toBinary(vector<string> text, unordered_map<char, string> huffmanMap)
{
	vector<bool> result{};

	int i = 0;

	while (i < text.size())
	{
		for (int j = 0; j < text[i].size(); j++)
		{ 
			
			unordered_map<char, string>::const_iterator foundIt = huffmanMap.find(text[i][j]);

			bool newFound;
			
			for (int k = 0; k < foundIt->second.size(); k++)
			{
				if (foundIt->second[k] == '0')
				{
					newFound = 0;
				} // end if we have a 0, set to false
				else if (foundIt->second[k] == '1')
				{
					newFound = 1;
				} // end else, we have a 1, set to true

				result.push_back(newFound);

			} // end for loop to ...
			
		} // end for loop to iterate through each line of our vector of strings
		i++;
	} // end while loop to loop through file_contents

	return result;
}