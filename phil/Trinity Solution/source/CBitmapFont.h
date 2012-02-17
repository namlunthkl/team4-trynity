//	File	:	CBitmapFont.h
//	Author	:	Phil Sullivan
//	Date	:	Jan. 13, 2012

#ifndef CBITMAPFONT_H
#define CBITMAPFONT_H

#include <Windows.h>

class CBitmapFont
{
private:
	//	Cell Algorithm
	int m_nCharWidth;
	int m_nCharHeight;
	int m_nNumCols;

	RECT CellAlgorithm(int nID);

	char m_cStartChar;
	int m_nImageID;

public:
	CBitmapFont();
	void Write(const char* szTextToPrint, int nPosX, int nPosY, DWORD dwColor);
	void WriteCentered(const char* szTextToPrint, int nPosY, DWORD dwColor);
};

#endif