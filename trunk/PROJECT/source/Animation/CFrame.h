////////////////////////////////////////////////////////////////////////
//    File Name				:	"CFrame.h"
//
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the Frames of the animation
////////////////////////////////////////////////////////////////////////
#ifndef _CFRAME_H_
#define _CFRAME_H_
class CFrame
{
private:
	RECT m_DrawRect, m_CollisionRect;
	POINT m_AnchorPoint;
	double m_fDuration;
	string m_szEvent;
	
public:
	//	Accessors
	RECT GetDrawRect() const { return m_DrawRect; }
	RECT GetCollisionRect() const { return m_CollisionRect; }
	POINT GetAnchorPoint() const { return m_AnchorPoint; }
	double GetDuration() const { return m_fDuration; }
	string GetEvent() const { return m_szEvent; }
	//	Mutators
	void SetDrawRect(RECT val) { m_DrawRect = val; }
	void SetCollisionRect(RECT val) { m_CollisionRect = val; }
	void SetAnchorPoint(POINT val) { m_AnchorPoint = val; }
	void SetDuration(double val) { m_fDuration = val; }
	void SetEvent(string val) { m_szEvent = val; }
};
#endif