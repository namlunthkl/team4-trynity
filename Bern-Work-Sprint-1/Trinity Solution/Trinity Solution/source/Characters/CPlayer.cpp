////////////////////////////////////////////////////////////////////////
//    File Name				:	"CPlayer.cpp"
//
//    Author Name			:	Phil Sullivan
//    Creation Date			:	02/09/12 - 3:57 AM
//    Purpose				:	Game player character class definitions
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CPlayer.h"

void CPlayer::Attack()
{
}

void CPlayer::ChargedBlast()
{
}

void CPlayer::GetHurt()
{
}

void CPlayer::Die()
{
}

void CPlayer::CallOut()
{
}

void CPlayer::LevelUp()
{
}

bool CPlayer::Initialize(short sPosX, short sPosY, unsigned char ucCharType, unsigned int uiSpeed, unsigned char ucMaxHP, CAnimation* panmMove, CAnimation* panmDestruction)
{
	return true;
}

RECT CPlayer::GetCollisionRect()
{
	RECT temp;
	return temp;
}

bool CPlayer::CheckCollision(IBaseInterface* pBase)
{
	return true;
}

void CPlayer::HandleEvent(CEvent* pEvent)
{
}

void CPlayer::Update(float fElapsedTime)
{
}

void CPlayer::Render()
{
}

void CPlayer::Shutdown()
{
}

//	References
void CPlayer::AddRef()
{
}
void CPlayer::Release()
{
}
//	Type
unsigned int CPlayer::GetType()
{
	return 0;
}