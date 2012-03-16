#include "CNPC.h"



class CGrimirNPC : public CNPC
{
	CDialogueList m_GrimirDialogues[3];

public:
	// Constructor
	CGrimirNPC(const char* szName = "noname", bool bActiveTalk = false, double dRange = 0, int sndNPC = -1,
		double dPositionX = 0, double dPositionY = 0, unsigned int uiSpeed = 0U,
		int nImageID = -1, unsigned int uiWidth = 0U, unsigned int uiHeight = 0U, bool bActive = false,
		unsigned int uiMaxHealth = 0, unsigned int uiAttackDamage = 0);
	~CGrimirNPC();

	// Load NPC's speech
	void LoadText(char const * const szFilename);

	// Common routines
	void Update(float fElapsedTime);
	void Render(void);
	void Input(void);
};