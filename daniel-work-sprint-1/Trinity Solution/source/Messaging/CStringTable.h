//    File Name				:	"CStringTable.h"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/15 - 11:26 AM
//    Purpose				:	Class that stores strings in an array
//								so that other objects can keep an index
//								to strings they need instead of a full
//								string
////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef STRING_TABLE_H_
#define STRING_TABLE_H_

// CStringTable - data structure that stores string
class CStringTable
{
	// Vector of strings - Where all names are stored
	vector<string> m_vszStringArray;

	// Capacity - maximum size of the vector
	unsigned int m_uiCapacity;

public:
	CStringTable(unsigned int uiCapacity);

	int LoadString(char const * const szString);

	const char* GetString(unsigned int uiIndex) const;

	void RemoveString(unsigned int uiIndex);

	void Clear(void);

};

#endif // STRING_TABLE_H_