////////////////////////////////////////////////////////////////////////
//    File Name				:	"CAnimationManager.h"
//
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the Animation Manager
////////////////////////////////////////////////////////////////////////
#ifndef _CANIMATIONMANAGER_H_
#define _CANIMATIONMANAGER_H_

#include "CAnimation.h"
class CAnimationManager
{
private:
	vector<CAnimation*> m_Animations;
public:
	bool UnloadAnimation(int nAnimation);
	int LoadAnimation();
	bool UnloadAll();
	static CAnimationManager* GetInstance();
};
#endif