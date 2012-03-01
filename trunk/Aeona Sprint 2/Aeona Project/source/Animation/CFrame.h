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
	RECT m_DrawRect;
	RectD m_CollisionRect;
	Point m_AnchorPoint;
	Point m_WeaponAnchorPoint;
	float m_WeaponAngle;
	double m_fDuration;
	string m_szEvent;
	
public:
	//	Accessors
	RECT GetDrawRect() const { return m_DrawRect; }
	RectD GetCollisionRect() const { return m_CollisionRect; }
	Point GetAnchorPoint() const { return m_AnchorPoint; }
	double GetDuration() const { return m_fDuration; }
	string GetEvent() const { return m_szEvent; }
	Point GetWeaponAnchorPoint() const { return m_WeaponAnchorPoint; }
	float GetWeaponAngle() const { return m_WeaponAngle; }
	
	//	Mutators
	void SetDrawRect(RECT val) { m_DrawRect = val; }
	void SetCollisionRect(RectD val) { m_CollisionRect = val; }
	void SetAnchorPoint(Point val) { m_AnchorPoint = val; }
	void SetDuration(double val) { m_fDuration = val; }
	void SetEvent(string val) { m_szEvent = val; }
	void SetWeaponAnchorPoint(Point val) { m_WeaponAnchorPoint = val; }
	void SetWeaponAngle(float val) { m_WeaponAngle = val; }
};
#endif