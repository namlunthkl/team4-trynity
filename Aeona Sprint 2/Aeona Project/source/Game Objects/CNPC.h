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
#include "../CBitmapFont.h"
#include "../Util/CDialogueList.h"
#include "../Messaging/IListener.h"
class CNPC : public CBaseCharacter , public IListener
{
public:
	string			m_szName;

	//	NPC's speech
	string			m_szText;
	CDialogueList	m_Dialogue;


	
	//	Range for the NPC to say something
	double			m_dRange;
	//	Should the NPC be talking?
	bool			m_bTalk;
	//	Should the NPC...
	//		false	- only speak when the player presses a button?
	//		true	- speak whenever the player gets in range
	bool			m_bActiveTalk;

	// Sound that the NPC plays
	int				m_sndNPC;

	// For speech to look like a real time typing
	unsigned int	m_uiTextIndex;
	DWORD			m_dwTimeStamp;

protected:
	CDialogueList*	m_pCurrentDialogue;
	tSpeechNode*	m_pCurrentSpeech;
	int				m_nCurrentOption;

public:
	// Constructor
	CNPC(const char* szName = "noname", bool bActiveTalk = false, double dRange = 0, int sndNPC = -1,
		double dPositionX = 0, double dPositionY = 0, unsigned int uiSpeed = 0U,
		int nImageID = -1, unsigned int uiWidth = 0U, unsigned int uiHeight = 0U, bool bActive = false,
		unsigned int uiMaxHealth = 0, unsigned int uiAttackDamage = 0);
	virtual ~CNPC();
	// Load NPC's speech
	virtual void LoadText(char const * const szFilename);

	// Common routines
	virtual void Update(float fElapsedTime);
	virtual void Render(void);
	virtual void Input(void);
	inline unsigned int GetType(void) const { return TYPE_CHAR_NPC; }
	void HandleEvent(CEvent* pEvent);
};

#endif // C_NPC_H_