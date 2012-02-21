////////////////////////////////////////////////////////////////////////
//    File Name				:	"IBaseInterface.h"
//
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the IBaseInterface
////////////////////////////////////////////////////////////////////////
#ifndef _IBASINTERFACE_H_
#define _IBASINTERFACE_H_

#include "StdAfx.h"

#include "Animation/CAnimation.h"

#include <Windows.h>

class IBaseInterface
{
private:
	unsigned int m_uiRefCount,m_nImageID,m_uiSpeed;
	short m_sVelX,m_sVelY,m_sPosX,m_sPosY;
	int m_anmMove;
	int m_anmDestruction;
	bool m_bActive;
public:
	virtual void Update(float fElapsedTime) = 0;
	virtual void Render() = 0;
	virtual void AddRef() = 0;
	virtual void Release() = 0;
	virtual unsigned int GetType() = 0;
	virtual RECT GetCollisionRect() = 0;
	virtual bool CheckCollision(IBaseInterface* pBase) = 0;

	short GetPosX(void) { return m_sPosX; }
	short GetPosY(void) { return m_sPosY; }
	short GetVelX(void) { return m_sVelX; }
	short GetVelY(void) { return m_sVelY; }
	int GetImageID(void)	{ return m_nImageID; }
	unsigned int GetRefCount(void)	{ return m_uiRefCount; }
	void SetPosX(short sPosX) { m_sPosX = sPosX; }
	void SetPosY(short sPosY) { m_sPosY = sPosY; }
	void SetVelX(short sVelX) { m_sVelX = sVelX; }
	void SetVelY(short sVelY) { m_sVelY = sVelY; }
	void SetImageID(int nImageID)	{ m_nImageID = nImageID; }
	void SetRefCount(unsigned int uiRefCount)	{ m_uiRefCount = uiRefCount; }
};

#endif