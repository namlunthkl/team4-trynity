////////////////////////////////////////////////////////////////////////
//    File Name				:	"CChest.h"
//
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/09/12 - 3:34 AM
//    Purpose				:	CChest
////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef CCHEST_H_
#define CCHEST_H_

// Include parent class
#include "CNPC.h"
#include "../Items/IBaseItem.h"
#include "../Particle Engine/ParticleWeapon.h"
#include "../Weapons/IBaseWeapon.h"
#include "../CBitmapFont.h"
#include "../Util/CDialogueList.h"

class CChest : public CNPC
{
private:
	IBaseItem * m_pItem;
public:
	CChest(const char* szName = "noname", bool bActiveTalk = false, double dRange = 0, int sndNPC = -1,
		double dPositionX = 0, double dPositionY = 0, unsigned int uiSpeed = 0U,
		int nImageID = -1, unsigned int uiWidth = 0U, unsigned int uiHeight = 0U, bool bActive = false,
		unsigned int uiMaxHealth = 0, unsigned int uiAttackDamage = 0);
	~CChest();
	void Render(void);
	void OpenChest(void);
	void LoadAnimations(char const * const szFilename);
	unsigned int GetType(void) const { return TYPE_CHAR_CHEST; }
protected:

};
#endif