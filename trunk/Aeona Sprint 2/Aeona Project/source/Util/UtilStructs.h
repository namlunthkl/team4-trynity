#ifndef UTIL_STRUCTS_H_
#define UTIL_STRUCTS_H_

#include "../Wrappers/CSGD_XAudio2.h"
#define AUDIO CSGD_XAudio2::GetInstance()
#include "../Camera/CCameraControl.h"

struct Point
{
	int x;
	int y;
	Point(int nX = 0, int nY = 0)
	{
		x = nX;
		y = nY;
	}
	bool operator==(const Point& p)
	{
		if(x == p.x && y == p.y)
			return true;
		else return false;
	}
	bool operator!=(const Point& p)
	{
		if(x == p.x && y == p.y)
			return false;
		else return true;
	}
	Point& operator=(const Point& p)
	{
		if(*this != p)
		{
			x = p.x;
			y = p.y;
		}
		return *this;
	}
};

struct PointL
{
	int x;
	int y;
	PointL(int nX = 0, int nY = 0)
	{
		x = nX;
		y = nY;
	}
	bool operator==(const PointL& p)
	{
		if(x == p.x && y == p.y)
			return true;
		else return false;
	}
	bool operator!=(const PointL& p)
	{
		if(x == p.x && y == p.y)
			return false;
		else return true;
	}
	PointL& operator=(const PointL& p)
	{
		if(*this != p)
		{
			x = p.x;
			y = p.y;
		}
		return *this;
	}
};

struct PointD
{
	double x;
	double y;
	PointD(double dX = 0, double dY = 0)
	{
		x = dX;
		y = dY;
	}
	bool operator==(const PointD& p)
	{
		if(x == p.x && y == p.y)
			return true;
		else return false;
	}
	bool operator!=(const PointD& p)
	{
		if(x == p.x && y == p.y)
			return false;
		else return true;
	}
	PointD& operator=(const PointD& p)
	{
		if(*this != p)
		{
			x = p.x;
			y = p.y;
		}
		return *this;
	}
	double GetDistanceUntil(const PointD& p)
	{
		double dDistance = 0;

		// Get Deltas
		double dDeltaX = p.x - x;
		double dDeltaY = p.y - y;

		// Get absolute value
		if(dDeltaX < 0) dDeltaX = -dDeltaX;
		if(dDeltaY < 0) dDeltaY = -dDeltaY;

		// Teorema de Pitágoras!
		dDistance = sqrt((dDeltaX * dDeltaX) + (dDeltaY * dDeltaY));

		// Return distance
		return dDistance;
	}
};

struct PointF
{
	float x;
	float y;
	PointF(float fX = 0, float fY = 0)
	{
		x = fX;
		y = fY;
	}
	bool operator==(const PointF& p)
	{
		if(x == p.x && y == p.y)
			return true;
		else return false;
	}
	bool operator!=(const PointF& p)
	{
		if(x == p.x && y == p.y)
			return false;
		else return true;
	}
	PointF& operator=(const PointF& p)
	{
		if(*this != p)
		{
			x = p.x;
			y = p.y;
		}
		return *this;
	}
};

struct Rect
{
	int left;
	int top;
	int right;
	int bottom;
	int width;
	int height;
	Rect(int nLeft = 0, int nTop = 0, int nRight = 0, int nBottom = 0)
	{
		left = nLeft;
		top = nTop;
		right = nRight;
		bottom = nBottom;
		width = nRight - nLeft;
		height = nBottom - nTop;
	}
	void OffsetRect(int nOffsetX, int nOffsetY)
	{
		left += nOffsetX;
		right += nOffsetX;
		top += nOffsetY;
		bottom += nOffsetY;
	}

	RECT GetWindowsRECT(void)
	{
		RECT rectTemp;
		rectTemp.left = (long)left;
		rectTemp.top = (long)top;
		rectTemp.right = (long)right;
		rectTemp.bottom = (long)bottom;
		return rectTemp;
	}
};

struct RectD
{
	double left;
	double top;
	double right;
	double bottom;
	double width;
	double height;
	RectD(double dLeft = 0, double dTop = 0, double dRight = 0, double dBottom = 0)
	{
		left = dLeft;
		top = dTop;
		right = dRight;
		bottom = dBottom;
		width = dRight - dLeft;
		height = dBottom - dTop;
	}
	void OffsetRect(double dOffsetX, double dOffsetY)
	{
		left += dOffsetX;
		right += dOffsetX;
		top += dOffsetY;
		bottom += dOffsetY;
	}
	RECT GetWindowsRECT(void)
	{
		RECT rectTemp;
		rectTemp.left = (long)left;
		rectTemp.top = (long)top;
		rectTemp.right = (long)right;
		rectTemp.bottom = (long)bottom;
		return rectTemp;
	}
};

struct Sound
{
	DWORD	m_dwTimeStamp;
	DWORD	m_dwDelta;
	int		m_nSoundID;
	Sound(char const * const szFile = nullptr, DWORD dwDelta = 200)
	{
		Load(szFile);
		m_dwDelta = dwDelta;
	}
	void Load(char const * const szFile)
	{
		m_nSoundID = AUDIO->SFXLoadSound(szFile);
		m_dwTimeStamp = timeGetTime();
	}
	void Play(void)
	{
		if(m_nSoundID != -1)
		{
			if(timeGetTime() - m_dwTimeStamp > m_dwDelta)
			{
				AUDIO->SFXPlaySound(m_nSoundID);
				m_dwTimeStamp = timeGetTime();
			}
		}
	}
	void Unload(void)
	{
		if(m_nSoundID != -1)
			AUDIO->SFXUnloadSound(m_nSoundID);
	}
};






#endif // UTIL_STRUCTS_H_