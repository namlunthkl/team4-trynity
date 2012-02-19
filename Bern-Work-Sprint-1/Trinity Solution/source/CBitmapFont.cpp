//	File	:	CBitmapFont.cpp
//	Author	:	Phil Sullivan
//	Date	:	Jan. 13, 2012

#include "StdAfx.h"
#include "CGame.h"
#include "CBitmapFont.h"

CBitmapFont::CBitmapFont()
{
	m_nCharWidth = 24;
	m_nCharHeight = 26;
	m_nNumCols = 16;
	m_cStartChar = 0;
	m_nImageID = TEX_MNG->LoadTexture("resource/Font.png", D3DCOLOR_XRGB(0, 0, 0));
}

RECT CBitmapFont::CellAlgorithm(int nID)
{
	RECT rCell;
	rCell.left = (nID % m_nNumCols) * m_nCharWidth;
	rCell.top = (nID / m_nNumCols) * m_nCharHeight;
	rCell.right = rCell.left + m_nCharWidth;
	rCell.bottom = rCell.top + m_nCharHeight;
	return rCell;
}

void CBitmapFont::Write(const char* szTextToPrint, int nPosX, int nPosY, DWORD dwColor)
{
	int nOriginalX = nPosX;
	int length = strlen(szTextToPrint);
	for(int i = 0; i < length; ++i)
	{
		char ch = szTextToPrint[i];
		if(ch == ' ')
		{
			nPosX += 1;
			continue;
		}
		else if(ch == '\n')
		{
			nPosX = nOriginalX;
			nPosY += 1;
			continue;
		}
		int id = (int)(ch - m_cStartChar);
		RECT rLetter = CellAlgorithm(id);
		CSGD_TextureManager::GetInstance()->Draw(m_nImageID, nPosX * m_nCharWidth, nPosY * m_nCharHeight, 1.0f, 1.0f, &rLetter, 0, 0, 0, dwColor);
		nPosX += 1;
	}
}

void CBitmapFont::WriteCentered(const char* szTextToPrint, int nPosY, DWORD dwColor)
{
	int length = strlen(szTextToPrint);
	if(length % 2 != 0 || length > 32)
	{
		szTextToPrint = "XXXXXXXXXXXXXXXX";	//	I do this, because if I try to WriteCentered an odd-length string,
		length = strlen(szTextToPrint);		//	or, a string longer than the screen, I blatantly replace the text
	}										//	with X's so I notice it in-game.  Only supports even # length
	int nPosX = 16 - (length / 2);			//	strings that are 32 chars or less.
	for(int i = 0; i < length; ++i)
	{
		char ch = szTextToPrint[i];
		if(ch == ' ')
		{
			nPosX += 1;
			continue;
		}
		int id = (int)(ch - m_cStartChar);
		RECT rLetter = CellAlgorithm(id);
		CSGD_TextureManager::GetInstance()->Draw(m_nImageID, nPosX * m_nCharWidth, nPosY * m_nCharHeight, 1.0f, 1.0f, &rLetter, 0, 0, 0, dwColor);
		nPosX += 1;
	}
}