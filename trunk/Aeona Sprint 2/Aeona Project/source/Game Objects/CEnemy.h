////////////////////////////////////////////////////////////////////////
//    File Name				:	"CEnemy.h"
//
//    Author Name			:	Phil Sullivan
//    Creation Date			:	02/09/12 - 4:17 AM
//    Purpose				:	Enemy character class
////////////////////////////////////////////////////////////////////////

#ifndef C_ENEMY_H_
#define C_ENEMY_H_

#include "CBaseObject.h"
#include "../AI_States/IBaseAIState.h"
#include "../Animation/CAnimationPlayer.h"

class CEnemy : public CBaseObject
{
private:
	unsigned char	m_ucDamage;
	unsigned char	m_ucEnemyType;
	IBaseAIState*	m_pAIState;
	int				m_sndEnemy;

	int m_nCurrentAnimation;
	CAnimationPlayer* m_pAnimation[4];
	//temp
	float			m_fEnemyMoveTimer;
public:
	enum Animation { ANM_UP, ANM_DOWN, ANM_RIGHT, ANM_LEFT };

	//	Enemy-specific
	void ChangeState(IBaseAIState* pAIState);
	//
	bool Initialize(short sPosX, short sPosY, unsigned char ucCharType, unsigned int uiSpeed, unsigned char ucMaxHP, CAnimation* panmMove, CAnimation* panmDestruction);
	RECT GetCollisionRect();
	bool CheckCollision(IBaseInterface* pBase);
	void HandleEvent(CEvent* pEvent);
	void Update(float fElapsedTime);
	void Render();
	void Shutdown();
	void LoadAnimation();
	
	inline unsigned int GetType(void) { return TYPE_BASE_ENEMY; }
};

#endif // C_ENEMY_H_