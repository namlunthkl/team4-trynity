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
int m_nImageId/*, m_nFrames.size()??? m_nNumberOfFrames*/;
float m_nSpeed;
string m_szName;
bool m_bIsLooping,m_bIsPlaying,m_bIsOscillating;

public:
	//	Accessors
	vector<CFrame>* GetFrames() { return &m_nFrames; }
	int GetImageId() const { return m_nImageId; }
	float GetSpeed() const { return m_nSpeed; }
	string GetName() const { return m_szName; }
	bool GetIsLooping() const { return m_bIsLooping; }
	bool GetIsPlaying() const { return m_bIsPlaying; }
	bool GetIsOscillating() const { return m_bIsOscillating; }
	//	Mutators
	void SetImageId(int val) { m_nImageId = val; }
	void SetSpeed(float val) { m_nSpeed = val; }
	void SetName(string val) { m_szName = val; }
	void SetIsLooping(bool val) { m_bIsLooping = val; }
	void SetIsPlaying(bool val) { m_bIsPlaying = val; }
	void SetIsOscillating(bool val) { m_bIsOscillating = val; }
};
#endif