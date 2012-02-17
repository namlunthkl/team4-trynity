////////////////////////////////////////////////////////////////////////
//    File Name				:	"CAnimationPlayer.h"
//
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the Animation Player
////////////////////////////////////////////////////////////////////////
#ifndef _CANIMATIONPLAYER_H_
#define _CANIMATIONPLAYER_H_
#include "CAnimationManager.h"
class CAnimationPlayer
{
private:
	int m_nAnimationId;
	float m_fDuration;
	int m_nFrameNumber;
	float m_fTimer;
public:
	void Play();
	void Stop();
	void Reset();
	void Update(float fElapsedTime);

};
#endif