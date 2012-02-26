////////////////////////////////////////////////////////////////////////
//    File Name				:	"CMessageSystem.cpp"
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
	//	Error check to make sure the message proc is valid
	if(!pfnMsgProc)
		return;

	//	Get the MessageProc
	m_pfnMsgProc = pfnMsgProc;
}

void CMessageSystem::SendMsg(CBaseMessage* pMsg)
{
	//	Make sure the message exists
	if(!pMsg)
		return;

	//	Send the message to the queue for processing later on
	m_MsgQueue.push(pMsg);
}

void CMessageSystem::ProcessMessages(void)
{
	//	Error check to make sure we get a message proc
	if(!m_pfnMsgProc)
		return;

	//	Go through the entire queue and process messages that are waiting
	while(!m_MsgQueue.empty())
	{
		m_pfnMsgProc(m_MsgQueue.front());
		delete m_MsgQueue.front();
		m_MsgQueue.pop();
	}
}

void CMessageSystem::ClearMessages(void)
{
	//	Clear out any messages waiting
	while(!m_MsgQueue.empty())
	{
		delete m_MsgQueue.front();
		m_MsgQueue.pop();
	}
}

void CMessageSystem::ShutdownMessageSystem(void)
{
	//	Clear out any messages waiting
	ClearMessages();

	//	Clear the function pointer
	m_pfnMsgProc = NULL;
}