////////////////////////////////////////////////////////////////////////
//    File Name				:	"CNPC.h"
//
//    Author Name			:	Phil Sullivan
//    Creation Date			:	02/09/12 - 4:06 AM
//    Purpose				:	NPC character class
////////////////////////////////////////////////////////////////////////

#ifndef C_NPC_H_
#define C_NPC_H_

#include "CBaseCharacter.h"

class CNPC : public CBaseCharacter
{
private:
	char*			m_szText;
	bool			m_bTalk;
	bool			m_bNear;
	int				m_sndNPC;
public:
	//	NPC-specific
	void LoadText(char* szFilename);
};

#endif // C_NPC_H_