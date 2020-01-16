#ifndef STRINGSPLITTER_H
#define STRINGSPLITTER_H

#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <vector>

using namespace std;

class StringSplitter
{
public:

	static vector <string> split(string text, string delimiter)
	{
		// create a place to store all of my pieces
		vector <string> pieces;

		// find quotes, this will only work for one pair of quotes, adequate for this assignment
		int quoteLocationFirst = text.find ("\"");
		int quoteLocationLast = text.find("\"", quoteLocationFirst + 1);


		// find first delimiter
		int location = text.find (delimiter);

		// tracks location of start of substring, have to shift beginning of substring
		int start = 0;

		// if the delimiter is between our quotes, re-run it to move to the next
		// instance of the delimiter that is not within our quotes

		if ((location > quoteLocationFirst) && (location < quoteLocationLast))
		{
			location = text.find(delimiter, location + 1);
		} // end if location is between our quotes, move to next instance

		// loop as long as we have more delimiters
		while (location != string::npos)
		{

			// if the delimiter is between our quotes, re-run it to move to the next
			// instance of the delimiter that is not within our quotes

			if ((location > quoteLocationFirst) && (location < quoteLocationLast))
			{
				location = text.find(delimiter, location + 1);
			} // end if location is between our quotes, move to next instance


			// grab the current piece of the string that starts at "start" and ends at "location"
			string piece = text.substr(start, location - start);

			// add to vector
			pieces.push_back (piece);

			// update our tracking information
			start = location + 1;

			// find the next delimiter
			location = text.find (delimiter, start);

		} // end while location is not string::npos

		// handle the last piece outside the while loop
		// once the while loop complete, we have one dangling piece left over
		string piece = text.substr(start, location - start);

		// add last piece to vector
		pieces.push_back (piece);

		// all done, return:
		return pieces;

	} // end split

}; // end StringSplitter class

#endif
