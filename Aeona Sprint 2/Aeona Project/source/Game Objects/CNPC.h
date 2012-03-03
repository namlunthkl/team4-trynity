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

class CNPC : public CBaseCharacter
{
	//	NPC's speech
	string			m_szText;
	CDialogueList	m_Dialogue;
	tSpeechNode*	m_pCurrentSpeech;
	int				m_nCurrentOption;
	//	Range for the NPC to say something
	double			m_dRange;
	//	Should the NPC be talking?
	bool			m_bTalk;
	//	Should the NPC...
	//		false	- only speak when the player presses a button?
	//		true	- speak whenever the player gets in range
	bool			m_bActiveTalk;

	// Font to speak
	CBitmapFont*	m_pFont;
	// Image for the message box
	int				m_imgMsgBox;
	// Sound that the NPC plays
	int				m_sndNPC;

	// For speech to look like a real time typing
	unsigned int	m_uiTextIndex;
	DWORD			m_dwTimeStamp;

public:
	// Constructor
	CNPC(bool bActiveTalk = false, double dRange = 0, int sndNPC = -1, CBitmapFont* pFont = nullptr,
		double dPositionX = 0, double dPositionY = 0, unsigned int uiSpeed = 0U,
		int nImageID = -1, unsigned int uiWidth = 0U, unsigned int uiHeight = 0U, bool bActive = false,
		unsigned int uiMaxHealth = 0, unsigned int uiAttackDamage = 0);

	// Load NPC's speech
	void LoadText(char* szFilename);

	// Common routines
	void Update(float fElapsedTime);
	void Render(void);
	void Input(void);
	inline unsigned int GetType(void) const { return TYPE_CHAR_NPC; }
};

#endif // C_NPC_H_