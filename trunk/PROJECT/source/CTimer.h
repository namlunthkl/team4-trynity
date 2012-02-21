////////////////////////////////////////////////////////////////////////
//    File Name				:	"CTimer.h"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/06 - 12:59 PM
//    Purpose				:	Used by CGame for game timing
//
//    Last Updater Name		:	Name of last person who updated it
//    Last Update Date		:	month/day - hour:min (AM/PM)
//    Last Update Notes		:	Notes from the last person who updated it
//
//    Other Notes			:   Notes from other updates are moved here
//								when the file is updated again
////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef CTIMER_H_
#define CTIMER_H_

// TODO: This include should probably be in the
// precompiled header, but since we don't have
// that yet
#include <Windows.h>

// Timer class
// FPS, Game Time, Elapsed Time counting
class CTimer
{
public:
	//	For Game Timing
	//		Time Stamp
	DWORD	m_dwTimeStamp;
	//		Delta Time - Time (in seconds) between frames
	float	m_fElapsedTime;
	//		Game Time - How long the game has been playing
	float	m_fGameTime;
	//		Previous Time Stamp - Stamp from the previous frame
	DWORD	m_dwPreviousTimeStamp;
	//	For FPS Counting
	//		Frame Counter - Current frame count
	int		m_nFrameCounter;
	//		FPS - Frame count from the previous second for display
	int		m_nFPS;
	//		FPS Time Stamp - Time stamp from previous second
	int		m_dwFPSTimeStamp;

	// Constructor
	CTimer(void)
	{
		m_dwTimeStamp			= 0;
		m_fElapsedTime			= 0.0f;
		m_fGameTime				= 0.0f;
		m_dwPreviousTimeStamp	= 0;
		m_nFrameCounter			= 0;
		m_nFPS					= 0;
		m_dwFPSTimeStamp		= 0;
	}
};

#endif // CTIMER_H_