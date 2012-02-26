////////////////////////////////////////////////////////////////////////
//    File Name				:	"CPlayer.h"
//
//    Author Name			:	Phil Sullivan
//    Creation Date			:	02/09/12 - 3:34 AM
//    Purpose				:	Game player character class
////////////////////////////////////////////////////////////////////////

#ifndef C_PLAYER_H_
#define C_PLAYER_H_

#include "CBaseObject.h"

class CPlayer : public CBaseObject
{
private:
	CPlayer*		m_pInstance;
	unsigned char	m_cWeapons;
	unsigned char	m_cMasks;
	bool			m_bHasHeartPiece;
	short			m_sBaseDamage;
	unsigned char	m_cCurrentWeapon;
	int				m_sndPlayer;

public:
	CPlayer();
	~CPlayer();

	//	Player-specific
	void Attack();
	void ChargedBlast();
	void GetHurt();
	void Die();
	void CallOut();
	void LevelUp();
	//
	bool Initialize(short sPosX, short sPosY, unsigned char ucCharType, unsigned int uiSpeed, unsigned char ucMaxHP, CAnimation* panmMove, CAnimation* panmDestruction);
	RECT GetCollisionRect();
	bool CheckCollision(IBaseInterface* pBase);
	void HandleEvent(CEvent* pEvent);
	void Update(float fElapsedTime);
	void Render();
	void Shutdown();
	inline unsigned int GetType(void) { return TYPE_PLAYER; }
};

#endif // C_PLAYER_H_