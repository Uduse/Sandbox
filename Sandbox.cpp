// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class Train;
class LocalTrain;
class TrainList;

class Train
{
public:

	friend Train& operator+= ( TrainList &lhs, Train &rhs );
	friend fstream& operator>>( fstream &lfs, Train *rhs );

	Train();
	~Train();

	virtual bool find( char* );
	virtual void print();
protected:
	virtual iostream& read( iostream &is );
	int number;
	char* origin;
	char* destination;
private:

};

Train::Train()
{
}

Train::~Train()
{
}


void Train::print()
{
	cout << setw( 3 ) << number << " O: ";
}

class LocalTrain: public Train
{
	friend class TrainList;
	friend class TrainListNode;
public:
	LocalTrain();
	~LocalTrain();
private:
	char stops[5][11];
	iostream& read( iostream &is );
};

iostream& LocalTrain::read( iostream &is )
{

	//char tempChar;
	char s[256];
	is.getline( s, 256 );
	strtok( s, "," );
	number = atoi( strtok( NULL, "," ) );
	origin = strtok( NULL, "," );
	destination = strtok( NULL, "," );

	int counter = 0;
	char* ptr;
	while ( ( counter <= 4 ) && ( ptr = strtok( NULL, "," ) ) )
	{
		strcpy( stops[counter], ptr );
		counter++;
	}
}

LocalTrain::LocalTrain()
{
}

LocalTrain::~LocalTrain()
{
}

class TrainListNode
{
public:
	TrainListNode();
	TrainListNode( Train &lhs, TrainListNode* rhs );
	~TrainListNode();
	Train* thisTrain;
	TrainListNode* next;
private:
};

TrainListNode::TrainListNode( Train &lhs, TrainListNode* rhs )
{

}

class TrainList
{
	friend Train& operator+= ( TrainList &lhs, Train &rhs );
public:
	TrainList();
	~TrainList();
	void print( char* name );
	void save( char* fileName );
private:
	TrainListNode* head;
	TrainListNode* prev;
};

TrainList::TrainList()
{
}

TrainList::~TrainList()
{
}

void TrainList::print( char* name )
{
	TrainListNode* ptr = head;
	while ( ptr )
	{
		if ( ptr->thisTrain->find( name ) )
		{
			ptr->thisTrain->print();
		}
		ptr = ptr->next;
	}
}

void TrainList::save( char* fileName )
{
	TrainListNode* ptr = head;
	ofstream outf( fileName );

	while ( outf && ptr )
	{
		ptr->thisTrain->print( outf );
		ptr = ptr->next;
	}
	outf.close();
}

Train& operator+= ( TrainList &lhs, Train &rhs )
{
	TrainListNode* ptr = lhs.head;
	lhs.prev = NULL;
	while ( ptr && ptr->thisTrain->number < rhs.number )
	{
		lhs.prev = ptr;
		ptr = ptr->next;
	}
	if ( !lhs.prev )
	{
		lhs.head = new TrainListNode( rhs, ptr );
	}
	else
	{
		lhs.prev->next = new TrainListNode( rhs, ptr );
	}
	return rhs;
}

int _tmain( int argc, _TCHAR* argv[] )
{
	return 0;
}

