////////////////////////////////////////////////////////////////////////
//    File Name				:	"CMessageSystem.cpp"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/09 - 03:41 AM
//    Purpose				:	Class that handles the Message System
////////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "CMessageSystem.h"

CMessageSystem* CMessageSystem::GetInstance(void)
{
	static CMessageSystem instance;
	return &instance;
}

void CMessageSystem::InitMessageSystem(void(*pfnMsgProc)(CBaseMessage*))
{
}

void CMessageSystem::SendMsg(CBaseMessage* pMsg)
{
}

void CMessageSystem::ProcessMessages(void)
{
}

void CMessageSystem::ClearMessages(void)
{
}

void CMessageSystem::ShutdownMessageSystem(void)
{
}
