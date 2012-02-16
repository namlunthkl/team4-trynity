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


CStringTable::CStringTable(int nCapacity)
{
	m_nCapacity = nCapacity;
}

int CStringTable::LoadString(const char const * szString)
{
	if(m_vszStringArray.size() < m_nCapacity)
	{
		m_vszStringArray.push_back(szString);
		return m_vszStringArray.size() - 1;
	}
	else
		return -1;
}

const char* CStringTable::GetString(const int nIndex) const
{
	if(nIndex >= 0 && nIndex < m_vszStringArray.size())
	{
		return m_vszStringArray[nIndex].c_str();
	}
	else
		return nullptr;
}

void CStringTable::RemoveString(int nIndex)
{
	if(nIndex >= 0 && nIndex < m_vszStringArray.size())
	{
		m_vszStringArray.erase(m_vszStringArray.begin() + nIndex);
	}
}


void CStringTable::Clear(void)
{
	m_vszStringArray.clear();
}