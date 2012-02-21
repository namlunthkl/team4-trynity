////////////////////////////////////////////////////////////////////////
//    File Name				:	"CMessageSystem.h"
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/09 - 03:16 AM
//    Purpose				:	Class that handles the Message System
////////////////////////////////////////////////////////////////////////

#ifndef CMESSAGESYSTEM_H_
#define CMESSAGESYSTEM_H_

#include "Messages.h"
#include <queue>
using std::queue;

class CMessageSystem
{
	queue<CBaseMessage*> m_MsgQueue;
	void(*m_pfnMsgProc)(CBaseMessage*);

	// Constructor & Trilogy
	CMessageSystem() { m_pfnMsgProc; }
	CMessageSystem(const CMessageSystem&);
	CMessageSystem& operator=(const CMessageSystem&);
	~CMessageSystem() {}

public:
	static CMessageSystem* GetInstance(void);
	inline int GetNumMessages(void) { return (int)m_MsgQueue.size(); }
	void InitMessageSystem(void(*pfnMsgProc)(CBaseMessage*));
	void SendMsg(CBaseMessage* pMsg);
	void ProcessMessages(void);
	void ClearMessages(void);
	void ShutdownMessageSystem(void);
};

#endif // CMESSAGESYSTEM_H_