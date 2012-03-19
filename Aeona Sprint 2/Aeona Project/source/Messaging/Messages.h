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
enum eMsgTypes { MSG_NULL = 0, MSG_CREATE_PLAYER,MSG_CREATE_NPC, MSG_CREATE_ENEMY,
	MSG_CREATE_CHEST, MSG_DESTROY_OBJECT, MSG_MAX };

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
	string	m_szName;
	double	m_dPosX;
	double	m_dPosY;

public:

	CCreateNPCMessage(string szName, double dPosX, double dPosY) : CBaseMessage(MSG_CREATE_NPC)
	{
		m_szName = szName;
		m_dPosX = dPosX;
		m_dPosY = dPosY;
	}
	
	inline string	GetName(void) const { return m_szName; }
	inline double	GetPosX(void) const { return m_dPosX; }
	inline double	GetPosY(void) const { return m_dPosY; }
	~CCreateNPCMessage() {};
};
class CCreateEnemyMessage : public CBaseMessage
{
private:
	double	m_dPosX;
	double	m_dPosY;
	string	m_szRegion;

public:
	CCreateEnemyMessage(double dPosX, double dPosY, string szRegion) : CBaseMessage(MSG_CREATE_ENEMY)
	{
		m_dPosX = dPosX;
		m_dPosY = dPosY;
		m_szRegion = szRegion;
	}
	
	inline double	GetPosX(void) const { return m_dPosX; }
	inline double	GetPosY(void) const { return m_dPosY; }
	inline string	GetRegion(void) const { return m_szRegion; }

	~CCreateEnemyMessage() {}
};

class CCreateChestMessage : public CBaseMessage
{
	double	m_dPosX;
	double	m_dPosY;
	int		m_nType;

public:
	CCreateChestMessage(double dPosX, double dPosY, int nType) : CBaseMessage(MSG_CREATE_CHEST)
	{
		m_dPosX = dPosX;
		m_dPosY = dPosY;
		m_nType = nType;
	}

	inline double	GetPosX(void) const { return m_dPosX; }
	inline double	GetPosY(void) const { return m_dPosY; }
	inline int		GetType(void) const { return m_nType; }

	~CCreateChestMessage() {}
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