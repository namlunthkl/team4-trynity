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
void SetBit(Byte& byteArgument, BitIndex bitToSet, bool bValue);
bool TestBit(Byte byteArgument, BitIndex bitToTest);
void ToggleBit(Byte& byteArgument, BitIndex bitToSet);
char GetNumberOfBitsOn(Byte byteArgument);
char GetNumberOfBitsOff(Byte byteArgument);

#endif // BYTEUTIL_H_