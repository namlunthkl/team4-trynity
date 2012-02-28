#ifndef UTIL_STRUCTS_H_
#define UTIL_STRUCTS_H_

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





#endif // UTIL_STRUCTS_H_