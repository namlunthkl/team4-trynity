////////////////////////////////////////////////////////////////////////
//    File Name				:	"CEnemy.cpp"
//
//    Author Name			:	Phil Sullivan
//    Creation Date			:	02/09/12 - 4:24 AM
//    Purpose				:	Enemy character class definitions
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CEnemy.h"

//	Enemy-specific
void CEnemy::ChangeState(IBaseAIState* pAIState)
{
}
//
bool CEnemy::Initialize(short sPosX, short sPosY, unsigned char ucCharType, unsigned int uiSpeed, unsigned char ucMaxHP, CAnimation* panmMove, CAnimation* panmDestruction)
{
	return true;
}

RECT CEnemy::GetCollisionRect()
{
	RECT temp;
	return temp;
}

bool CEnemy::CheckCollision(IBaseInterface* pBase)
{
	return true;
}

void CEnemy::HandleEvent(CEvent* pEvent)
{
}

void CEnemy::Update(float fElapsedTime)
{
}

void CEnemy::Render()
{
}

void CEnemy::Shutdown()
{
}

//	References
void CEnemy::AddRef()
{
}
void CEnemy::Release()
{
}
//	Type
unsigned int CEnemy::GetType()
{
	return 0;
}