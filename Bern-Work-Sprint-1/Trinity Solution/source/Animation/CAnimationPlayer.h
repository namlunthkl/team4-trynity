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
#include "../Messaging/IListener.h"
class CAnimationPlayer : public IListener
{
private:
	int m_nAnimationId;
	//float m_fDuration;
	bool m_bIsPlaying, m_bIsLooping;
	unsigned int m_nFrameNumber;
	double m_fTimer;
public:
	inline CAnimationPlayer(int nAnimationID, bool bIsLooping) 
	{
		m_nAnimationId = nAnimationID; 
		m_bIsLooping = bIsLooping;
	}
	void Play();
	void Stop();
	void Reset();
	void Update(float fElapsedTime);
	void Render(int nPosX, int nPosY);
	void init();
	void HandleEvent(CEvent* pEvent);
};
#endif