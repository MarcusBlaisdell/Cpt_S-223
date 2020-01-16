#include <fstream>
#include <iostream>
#include <string>
#include "StringSplitter.h"
#include "Record.h"
#include <list>

using namespace std;


int main(int argc, char *argv[])
{
	ofstream output_file("output.txt");

		// use a for loop to read in all of the input arguments
		// and output them to output_file
	for (int i = 1; i < argc; i++)
	{
		cout << argv[i] << endl;
		// output_file << argv[i] << endl;

		// open file for read
	ifstream input_file( argv[i] );
	//ifstream input_file{"input.txt"};

		// instantiate a Record
	Record newRecord;

	list<Record> newRecords;

	// ask, was the file opened successfully
	if (input_file.is_open() == true)
	{
		// if file was opened, we can begin reads
		while (input_file.good() == true)
		{
				// holds current line information:
			string line = "";

				// get next line from file
			getline(input_file, line);


			// use his parser:
			vector<string> pieces = StringSplitter::split(line, ",");

			for (int i = 3; i < pieces.size(); i++)
			{
				int newNumID = stoi(pieces[0]);
				newRecord.setNumID(newNumID);
				newRecord.setStudentName(pieces[1]);
				int newTotal = stoi(pieces[2]);
				newRecord.setTotal(newTotal);
				int newEvent = stoi(pieces[i]);
				vector <int> newEvents;
				newEvents.push_back(newEvent);
				newRecord.setEvents (newEvents);

				cout << pieces[i] << endl;
			}

				// additional file parsing:
			// cout << line << endl;
		} // end while loop to read in from file
	} // end if file open was successful

	input_file.close  ();
	output_file.close ();

	} // end for loop to cout the input arguments to output file

	/*
		// use his parser:
	vector<string> pieces = StringSplitter::split("This is a test", " ");
	int i = 0;
	for (i = 0; i < pieces.size(); i++)
	{
		cout << pieces[i] << endl;
	}
	*/

} // end main
