//    File Name				:	"CStringTable.cpp"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/15 - 11:26 AM
//    Purpose				:	Class that stores strings in an array
//								so that other objects can keep an index
//								to strings they need instead of a full
//								string
////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "CStringTable.h"


CStringTable::CStringTable(unsigned int uiCapacity)
{
	m_uiCapacity = uiCapacity;
}

int CStringTable::LoadStringOnTable(char const * const szString)
{
	// Check if the string is already in the array
	for(unsigned int i = 0; i < m_vszStringArray.size(); ++i)
	{
		if(m_vszStringArray[i] == szString)
			return i;
	}


	if(m_vszStringArray.size() < m_uiCapacity)
	{
		m_vszStringArray.push_back(szString);
		return m_vszStringArray.size() - 1;
	}
	else
		return -1;
}

const char* CStringTable::GetString(unsigned int uiIndex) const
{
	if(uiIndex < m_vszStringArray.size())
	{
		return m_vszStringArray[uiIndex].c_str();
	}
	else
		return nullptr;
}

int CStringTable::GetStringIndex(char const * const szString) const
{
	for(unsigned int i = 0; i < m_vszStringArray.size(); ++i)
	{
		if(m_vszStringArray[i] == szString)
			return i;
	}
	return -1;
}

void CStringTable::RemoveString(unsigned int uiIndex)
{
	if(uiIndex < m_vszStringArray.size())
	{
		m_vszStringArray.erase(m_vszStringArray.begin() + uiIndex);
	}
}


void CStringTable::Clear(void)
{
	m_vszStringArray.clear();
}