#ifndef C_ITEM_CHEST_H_
#define C_ITEM_CHEST_H_

#include "CBaseObject.h"

class CItemChest : public CBaseObject
{
	unsigned int m_uiType;
	unsigned int m_uiStatus;
	int m_nOpenSound;
	int m_nGetItemSound;
	int m_nAnimationIndex;
	int m_nChestGraphic;

public:
	enum EChestType { CHEST_POTION, CHEST_GEM, CHEST_HEARTPIECE, CHEST_AMULET_SPEED, CHEST_AMULET_LIGHT, CHEST_AMULET_ENDURANCE,
		CHEST_AMULET_STRENGTH, CHEST_MAX };
	enum EChestStatus { CHEST_STATUS_CLOSED, CHEST_STATUS_OPENING, CHEST_STATUS_JUST_OPENED, CHEST_STATUS_MESSAGE, CHEST_STATUS_OPEN };

	// Constructor
	CItemChest(unsigned int uiType, double dPositionX, double dPositionY);

	// Destructor
	~CItemChest();

	// Common routines
	void Update(float fElapsedTime);
	void Input(void);
	void Render(void);

	RectD GetCollisionRect(void);
};

#endif // C_ITEM_CHEST_H_