////////////////////////////////////////////////////////////////////////
//    File Name				:	"ByteUtil.h"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/19 - 2:52 PM
//    Purpose				:	File with all functions and macros needed
//								to manipulate bits
////////////////////////////////////////////////////////////////////////

#ifndef BYTEUTIL_H_
#define BYTEUTIL_H_

typedef signed char Byte;
typedef signed char BitIndex;

void TurnBitOn(Byte& byteArgument, BitIndex bitToSet);
void TurnBitOff(Byte& byteArgument, BitIndex bitToSet);
bool TestBit(Byte byteArgument, BitIndex bitToTest);
void ToggleBit(Byte& byteArgument, BitIndex bitToSet);
char GetNumberOfBitsOn(Byte byteArgument);
char GetNumberOfBitsOff(Byte byteArgument);

struct Point
{
	int x;
	int y;
	Point(int x=0, int y=0)
	{ this->x = x; this->y = y; }
};

struct PointL
{
	long x;
	long y;
	PointL(long x=0, long y=0)
	{ this->x = x; this->y = y; }
};

struct PointD
{
	double x;
	double y;
	PointD(double x=0, double y=0)
	{ this->x = x; this->y = y; }
};

struct PointF
{
	float x;
	float y;
	PointF(float x=0, float y=0)
	{ this->x = x; this->y = y; }
};

#endif // BYTEUTIL_H_