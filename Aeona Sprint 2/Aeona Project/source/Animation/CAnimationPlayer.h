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
	//float m_fDuration;
	bool m_bIsPlaying, m_bIsLooping, m_bPause;


	unsigned int m_nFrameNumber;
	double m_fTimer;
public:
	inline CAnimationPlayer(int nAnimationID, bool bIsLooping) 
	{
		m_nAnimationId = nAnimationID; 
		m_bIsLooping = bIsLooping;
		m_bIsPlaying = false;
		m_nFrameNumber = 0;
		m_fTimer = 0;
	}
	void Play();
	void Stop();
	void Pause();
	void Reset();
	void Update(float fElapsedTime);
	void Render(int nPosX, int nPosY);
	RECT ReturnFrameRect(void);

	RectD ReturnCollisionRect(void);

	RECT ReturnWeaponCollisionRect(void);

	Point ReturnAnchorPoint(void);
	bool GetPaused() const { return m_bPause; }
	//Point ReturnWeaponPoint(void);
	//
	//float ReturnWeaponAngle(void);

};
#endif