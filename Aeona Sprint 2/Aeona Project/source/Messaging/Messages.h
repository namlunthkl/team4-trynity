////////////////////////////////////////////////////////////////////////
//    File Name				:	"Messages.h"
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/09 - 03:47 AM
//    Purpose				:	File where all messages are defines
////////////////////////////////////////////////////////////////////////

#ifndef MESSAGES_H_
#define MESSAGES_H_
#include "../Game Objects/CNPC.h"
typedef int MSGID;
enum eMsgTypes { MSG_NULL = 0, MSG_CREATE_PLAYER,MSG_CREATE_NPC, MSG_DESTROY_OBJECT, MSG_MAX };

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

class CCreateNPCMessage : public CBaseMessage
{
private:
	//None
public:
	CCreateNPCMessage() : CBaseMessage(MSG_CREATE_NPC){;}
	~CCreateNPCMessage();
};

class CDestroyObjectMessage : public CBaseMessage
{
private:
	CBaseObject* m_pObject;
public:
	CDestroyObjectMessage (CBaseObject* pObject) : CBaseMessage(MSG_DESTROY_OBJECT)
	{
		m_pObject = pObject;
		m_pObject->AddRef();
	}
	~CDestroyObjectMessage ()
	{
		m_pObject->Release();	
	}
	CBaseObject* GetObject(void) {return m_pObject;}
};


#endif MESSAGES_H_