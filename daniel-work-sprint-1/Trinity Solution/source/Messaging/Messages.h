////////////////////////////////////////////////////////////////////////
//    File Name				:	"Messages.h"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/09 - 03:47 AM
//    Purpose				:	File where all messages are defines
////////////////////////////////////////////////////////////////////////

#ifndef MESSAGES_H_
#define MESSAGES_H_

typedef int MSGID;
enum eMsgTypes { MSG_BASE };

class CBaseMessage
{
	MSGID	m_msgID;

public:
	CBaseMessage(MSGID msgID) { m_msgID = msgID; }
	virtual ~CBaseMessage(void) {}
	inline MSGID GetMsgID(void)	{ return m_msgID; }
};

// Declare other messages in here

#endif MESSAGES_H_