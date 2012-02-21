////////////////////////////////////////////////////////////////////////
//    File Name				:	"Messages.h"
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/09 - 03:47 AM
//    Purpose				:	File where all messages are defines
////////////////////////////////////////////////////////////////////////

#ifndef MESSAGES_H_
#define MESSAGES_H_

typedef int MSGID;
enum eMsgTypes { MSG_NULL = 0, MSG_CREATE_PLAYER, MSG_MAX };

class CBaseMessage
{
private:
	MSGID	m_msgID;

public:
	CBaseMessage(MSGID msgID) { m_msgID = msgID; }
	virtual ~CBaseMessage(void) {}
	inline MSGID GetMsgID(void)	{ return m_msgID; }
};

// Declare other messages in here
class CCreatePlayerMessage : public CBaseMessage
{
	int m_nPosX;
	int m_nPosY;
public:
	CCreatePlayerMessage(int nPosX, int nPosY) : CBaseMessage(MSG_CREATE_PLAYER)
	{ m_nPosX = nPosX; m_nPosY = nPosY; }
	int GetPosX(void) { return m_nPosX; }
	int GetPosY(void) { return m_nPosY; }
};


#endif MESSAGES_H_