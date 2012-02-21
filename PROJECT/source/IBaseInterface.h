////////////////////////////////////////////////////////////////////////
//    File Name				:	"IBaseInterface.h"
//
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the IBaseInterface
////////////////////////////////////////////////////////////////////////
#ifndef _IBASINTERFACE_H_
#define _IBASINTERFACE_H_
#include "Animation/CAnimation.h"

class IBaseInterface
{
private:
	unsigned int m_uiRefCount,m_nImageID,m_uiSpeed;
	short m_sVelX,m_sVelY,m_sPosX,m_sPosY;
	int m_anmMove;
	int m_anmDestruction;
	bool m_bActive;
public:
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void AddRef() = 0;
	virtual void Release() = 0;
	virtual unsigned int GetType() = 0;
	virtual RECT GetCollisionRect() = 0;
	virtual bool CheckCollision(IBaseInterface* pBase) = 0;

	short GetPosX(void) { return m_sPosX; }
	short GetPosY(void) { return m_sPosY; }
	void SetPosX(short sPosX) { m_sPosX = sPosX; }
	void SetPosY(short sPosY) { m_sPosY = sPosY; }
};

#endif