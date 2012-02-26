////////////////////////////////////////////////////////////////////////
//    File Name				:	"CNPC.h"
//
//    Author Name			:	Phil Sullivan
//    Creation Date			:	02/09/12 - 4:06 AM
//    Purpose				:	NPC character class
////////////////////////////////////////////////////////////////////////

#ifndef C_NPC_H_
#define C_NPC_H_

#include "IBaseCharacter.h"

class CNPC : public IBaseCharacter
{
private:
	char*			m_szText;
	bool			m_bTalk;
	bool			m_bNear;
	int				m_sndNPC;
public:
	//	NPC-specific
	void LoadText(char* szFilename);
	//
	bool Initialize(short sPosX, short sPosY, unsigned char ucCharType, unsigned int uiSpeed, unsigned char ucMaxHP, CAnimation* panmMove, CAnimation* panmDestruction);
	RECT GetCollisionRect();
	bool CheckCollision(IBaseInterface* pBase);
	void HandleEvent(CEvent* pEvent);
	void Update(float fElapsedTime);
	void Render();
	void Shutdown();
	//	References
	void AddRef();
	void Release();
	//	Type
	unsigned int GetType();
};

#endif // C_NPC_H_