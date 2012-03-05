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
	m_cStartChar = 33;
	m_nImageID = TEX_MNG->LoadTexture("resource/BitmapFont.png", D3DCOLOR_XRGB(255, 0, 255));
}

RECT CBitmapFont::CellAlgorithm(int nID)
{
	RECT rCell;
	rCell.left = (nID % m_nNumCols) * m_nCharWidth;
	rCell.top = (nID / m_nNumCols) * m_nCharHeight;
	rCell.right = rCell.left + m_nCharWidth;
	rCell.bottom = rCell.top + m_nCharHeight;

	if(nID == 8+32)
	{
		rCell.right -= 10;
		m_nCharWidth = 6;
	}
	else if(nID == 9+32 || nID == 10+32 || nID == 11+32)	//	JKL
	{
		rCell.left -= 10;
		rCell.right -= 10;
	}
	else if(nID == 12+32)			//	M
	{
		rCell.left -= 10;
		m_nCharWidth = 26;
	}
	else if(nID == 22+32)			//	W
	{
		rCell.right += 10;
		m_nCharWidth = 26;
	}
	else if(nID == 23+32)			//	X
	{
		rCell.left -= 112;
		rCell.right -= 112;
		rCell.top += m_nCharHeight;
		rCell.bottom += m_nCharHeight;
	}
	else if(nID == 24+32 || nID == 25+32)
	{
		rCell.left += 16;
		rCell.right += 16;
	}
	else if(nID == 37+32)			//	f
	{
		rCell.right -= 2;
		m_nCharWidth = 14;
	}
	else if(nID == 40+32)			//	i
	{
		rCell.right -= 10;
		m_nCharWidth = 6;
	}
	else if(nID == 41+32)			//	j
	{
		rCell.right -= 6;
		m_nCharWidth = 10;
	}
	else if(nID == 43+32)			//	l
	{
		rCell.right -= 10;
		m_nCharWidth = 6;
	}
	else if(nID == 44+32)			//	m
	{
		rCell.left -= 10;
		m_nCharWidth = 26;
	}
	else if(nID == 49+32)			//	r
	{
		rCell.right -= 6;
		m_nCharWidth = 10;
	}
	else if(nID == 51+32)			//	t
	{
		rCell.right -= 2;
		m_nCharWidth = 14;
	}
	else if(nID == 54+32)			//	w
	{
		rCell.right += 10;
		m_nCharWidth = 26;
	}
	else if(nID == 55+32)			//	x
	{
		rCell.left -= 112;
		rCell.right -= 112;
		rCell.top += m_nCharHeight;
		rCell.bottom += m_nCharHeight;
	}
	else if(nID == 56+32 || nID == 57+32)	//	y - z
	{
		rCell.left += 16;
		rCell.right += 16;
	}

	return rCell;
}

void CBitmapFont::Write(const char* szTextToPrint, int nPosX, int nPosY, DWORD dwColor, float fScale)
{
	int nOriginal = nPosX;
	int length = strlen(szTextToPrint);
	for(int i = 0; i < length; ++i)
	{
		m_nCharWidth = 16;
		char ch = szTextToPrint[i];
		if(ch == ' ')
		{
			nPosX += 11;
			continue;
		}
		else if(ch == '\n')
		{
			nPosX = nOriginal;
			nPosY += (int)(m_nCharHeight * fScale);
			continue;
		}
		int id = (int)(ch - m_cStartChar);
		RECT rLetter = CellAlgorithm(id);
		CSGD_TextureManager::GetInstance()->Draw(m_nImageID, nPosX, nPosY, fScale, fScale, &rLetter, 0, 0, 0, dwColor);
		nPosX += (int)(m_nCharWidth * fScale);
	}
}