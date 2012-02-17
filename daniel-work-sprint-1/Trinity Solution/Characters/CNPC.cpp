////////////////////////////////////////////////////////////////////////
//    File Name				:	"CNPC.cpp"
//
//    Author Name			:	Phil Sullivan
//    Creation Date			:	02/09/12 - 4:13 AM
//    Purpose				:	NPC character class definitions
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CNPC.h"

//	NPC-specific
void CNPC::LoadText(char* szFilename)
{
}
//
bool CNPC::Initialize(short sPosX, short sPosY, unsigned char ucCharType, unsigned int uiSpeed, unsigned char ucMaxHP, CAnimation* panmMove, CAnimation* panmDestruction)
{
	return true;
}

RECT CNPC::GetCollisionRect()
{
	RECT temp;
	return temp;
}

bool CNPC::CheckCollision(IBaseInterface* pBase)
{
	return true;
}

void CNPC::HandleEvent(CEvent* pEvent)
{
}

void CNPC::Update(float fElapsedTime)
{
}

void CNPC::Render()
{
}

void CNPC::Shutdown()
{
}

//	References
void CNPC::AddRef()
{
}
void CNPC::Release()
{
}
//	Type
unsigned int CNPC::GetType()
{
	return 0;
}