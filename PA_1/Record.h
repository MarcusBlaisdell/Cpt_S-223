#pragma once
#include <string>
#include <vector>

using namespace std;

class Record
{
private:
	int          numID;
	string       studentName;
	int          total;
	vector <int> events;

public:
	Record ()
	{
		numID       = 0;
		studentName = "";
		total       = 0;
		events;
	} // end default constructor

	Record (int the_numID, string the_studentName, int the_total, vector <int> the_events)
	{
		this -> numID       = the_numID;
		this -> studentName = the_studentName;
		this -> total       = the_total;
		this -> events      = the_events;
	} // end initialized constructor

	~Record ()
	{
		// we'll have to delete our nodes
	}

	int getnumID ()
	{
		return numID;
	}

	string getStudentName()
	{
		return studentName;
	}

	int getTotal()
	{
		return total;
	}

	vector <int> getEvents()
	{
		return events;
	}

	void setNumID(int theNumID)
	{
		numID = theNumID;
	}

	void setStudentName(string theStudentName)
	{
		studentName = theStudentName;
	}

	void setTotal(int theTotal)
	{
		total = theTotal;
	}

	void setEvents(vector <int> theEvents)
	{
		events = theEvents;
	}

};
