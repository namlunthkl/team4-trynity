////////////////////////////////////////////////////////////////////////
//    File Name				:	"CAnimation.h"
//
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the Animations
////////////////////////////////////////////////////////////////////////
#ifndef _CANIMATION_H_
#define _CANIMATION_H_

#include "CFrame.h"
class CAnimation
{
private:

vector<CFrame> m_nFrames;
int m_nId;
bool m_bIsLooping,m_bIsPlaying,m_bIsOscillating;
int m_ImageId;

public:

};
#endif