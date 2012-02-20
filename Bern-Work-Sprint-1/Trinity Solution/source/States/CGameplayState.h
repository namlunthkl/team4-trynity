////////////////////////////////////////////////////////////////////////
//    File Name				:	"CGameplayState.h"
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/09/12 - 1:00 AM
//    Purpose				:	Contains the GameplayState
////////////////////////////////////////////////////////////////////////

#ifndef CGAMEPLAYSTATE_H_
#define CGAMEPLAYSTATE_H_

#include "IGameState.h"
#include "..\Tile Mapping\CMap.h"
#include "..\Animation\CAnimationPlayer.h"
class CGameplayState : public IGameState
{
	vector<CMap> m_vMaps;
	CAnimationPlayer* gethit;
	CAnimationPlayer* gethit2;
	CAnimationPlayer* attack;
	CAnimationPlayer* attack2;
	float bucket;
public:
	void Enter(void);
	bool Input(void);
	void Update(float fElapsedTime);
	void Render(void);
	void Exit(void);
	static CGameplayState* GetInstance(void);
	void CreateMaps(void);
	void CreatePuzzles(void);
};

#endif // CGAMEPLAYSTATE_H_