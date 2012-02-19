//	File	:	CBitmapFont.cpp
//	Author	:	Phil Sullivan
//	Date	:	Jan. 13, 2012

#include "StdAfx.h"
#include "CGame.h"
#include "CBitmapFont.h"

CBitmapFont::CBitmapFont()
{
	m_nCharWidth = 16;
	m_nCharHeight = 32;
	m_nNumCols = 8;
	m_cStartChar = 65;
	m_bModified = false;
	m_nImageID = TEX_MNG->LoadTexture("resource/BitmapFont.png", D3DCOLOR_XRGB(255, 0, 255));
}

RECT CBitmapFont::CellAlgorithm(int nID)
{
	RECT rCell;

	

	rCell.left = (nID % m_nNumCols) * m_nCharWidth;
	rCell.top = (nID / m_nNumCols) * m_nCharHeight;
	rCell.right = rCell.left + m_nCharWidth;
	rCell.bottom = rCell.top + m_nCharHeight;

	if(nID == 8)
	{
		rCell.right -= 10;
		m_nCharWidth = 6;
		m_bModified = true;
	}
	else if(nID == 9 || nID == 10 || nID == 11)	//	JKL
	{
		rCell.left -= 10;
		rCell.right -= 10;
	}
	else if(nID == 12)			//	M
	{
		rCell.left -= 10;
		m_nCharWidth = 26;
		m_bModified = true;
	}
	else if(nID == 22)			//	W
	{
		rCell.right += 10;
		m_nCharWidth = 26;
		m_bModified = true;
	}
	else if(nID == 23)			//	X
	{
		rCell.left -= 112;
		rCell.right -= 112;
		rCell.top += m_nCharHeight;
		rCell.bottom += m_nCharHeight;
	}
	else if(nID == 24 || nID == 25)
	{
		rCell.left += 16;
		rCell.right += 16;
	}
	else if(nID == 40)			//	i
	{
		rCell.right -= 10;
		m_nCharWidth = 6;
		m_bModified = true;
	}
	else if(nID == 41)			//	j
	{
		rCell.right -= 6;
		m_nCharWidth = 10;
		m_bModified = true;
	}
	else if(nID == 43)			//	l
	{
		rCell.right -= 10;
		m_nCharWidth = 6;
		m_bModified = true;
	}
	else if(nID == 44)			//	m
	{
		rCell.left -= 10;
		m_nCharWidth = 26;
		m_bModified = true;
	}
	else if(nID == 54)			//	w
	{
		rCell.right += 10;
		m_nCharWidth = 26;
		m_bModified = true;
	}
	else if(nID == 55)			//	x
	{
		rCell.left -= 112;
		rCell.right -= 112;
		rCell.top += m_nCharHeight;
		rCell.bottom += m_nCharHeight;
	}
	else if(nID == 56 || nID == 57)	//	y - z
	{
		rCell.left += 16;
		rCell.right += 16;
	}

	return rCell;
}

void CBitmapFont::Write(const char* szTextToPrint, int nPosX, int nPosY, DWORD dwColor)
{
	int length = strlen(szTextToPrint);
	for(int i = 0; i < length; ++i)
	{
		m_nCharWidth = 16;	//reset
		char ch = szTextToPrint[i];
		if(ch == ' ')
		{
			nPosX += m_nCharWidth;
			continue;
		}
		int id = (int)(ch - m_cStartChar);
		RECT rLetter = CellAlgorithm(id);
		CSGD_TextureManager::GetInstance()->Draw(m_nImageID, nPosX, nPosY * m_nCharHeight, 1.0f, 1.0f, &rLetter, 0, 0, 0, dwColor);
		nPosX += m_nCharWidth;
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