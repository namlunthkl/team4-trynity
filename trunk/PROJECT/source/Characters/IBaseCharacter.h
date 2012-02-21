////////////////////////////////////////////////////////////////////////
//    File Name				:	"IBaseCharacter.h"
//
//    Author Name			:	Phil Sullivan
//    Creation Date			:	02/09/12 - 3:03 AM
//    Purpose				:	Base character from which all the other
//								characters inherit
////////////////////////////////////////////////////////////////////////

#ifndef I_BASE_CHARACTER_H_
#define I_BASE_CHARACTER_H_

#include "..\IBaseInterface.h"
#include "..\Messaging\CEventSystem.h"

class IBaseCharacter : public IBaseInterface
{
private:
	unsigned char m_ucCharType;
	unsigned char m_ucCurHP;
	unsigned char m_ucMaxHP;
	unsigned char m_cState;
public:
	virtual bool Initialize(short sPosX, short sPosY, unsigned char ucCharType, unsigned int uiSpeed, unsigned char ucMaxHP, CAnimation* panmMove, CAnimation* panmDestruction) = 0;
	virtual RECT GetCollisionRect() = 0;
	virtual bool CheckCollision(IBaseInterface* pBase) = 0;
	virtual void HandleEvent(CEvent* pEvent) = 0;
	virtual void Update(float fElapsedTime) = 0;
	virtual void Render() = 0;
	virtual void Shutdown() = 0;
	//	References
	virtual void AddRef() = 0;
	virtual void Release() = 0;
	//	Type
	virtual unsigned int GetType() = 0;
};

#endif // I_BASE_CHARACTER_H_