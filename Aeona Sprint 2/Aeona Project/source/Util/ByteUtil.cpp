////////////////////////////////////////////////////////////////////////
//    File Name				:	"ByteUtil.h"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/19 - 2:52 PM
//    Purpose				:	File with all functions and macros needed
//								to manipulate bits
////////////////////////////////////////////////////////////////////////


#include "ByteUtil.h"

// Set a bit to on / 1
void TurnBitOn(Byte& byteArgument, BitIndex bitToSet)
{ byteArgument |= (1 << (7 - bitToSet)); }

// Set a bit to off / 0
void TurnBitOff(Byte& byteArgument, BitIndex bitToSet)
{ byteArgument &= ~(1 << (7 - bitToSet)); }

// Set a bit to on or off depending on the last argument
void SetBit(Byte& byteArgument, BitIndex bitToSet, bool bValue)
{ bValue ? TurnBitOn(byteArgument, bitToSet) : TurnBitOff(byteArgument, bitToSet); }

// Returns true if bit is 1, false otherwise
bool TestBit(Byte byteArgument, BitIndex bitToTest)
{ return (byteArgument & (1 << (7 - bitToTest))) ? true : false; }

// Toggles a bit value
void ToggleBit(Byte byteArgument, BitIndex bitToToggle)
{ byteArgument ^= (1 << (7 - bitToToggle)); }

// Gets how many bits are turned on on the byte
char GetNumberOfBitsOn(Byte byteArgument)
{
	char cReturn = 0;
	for(int i=0; i < 8; ++i)
		if(TestBit(byteArgument, i)) cReturn += 1;
	return cReturn;
}

// Gets how many bits are turned off on the byte
char GetNumberOfBitsff(Byte byteArgument)
{
	char cReturn = 0;
	for(int i=0; i < 8; ++i)
		if(!TestBit(byteArgument, i)) cReturn += 1;
	return cReturn;
}