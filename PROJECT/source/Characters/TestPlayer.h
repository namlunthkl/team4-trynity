#ifndef CTESTPLAYER_H_
#define CTESTPLAYER_H_

#include "../IBaseInterface.h"
#include "../Animation/CAnimationPlayer.h"
#include "../Animation/CAnimationManager.h"
#include "../Particle Engine/ParticleWeapon.h"

class TestPlayer : public IBaseInterface
{
public:
	unsigned int m_uiSpriteIndex;
	unsigned int m_uiDirection;
	unsigned int m_uiCurrentAnimation;

	CAnimationPlayer* m_pAnimation[4];
	ParticleWeapon m_footsteps;
	// Contructor
	TestPlayer(void) {}
	// Destructor
	~TestPlayer(void) {}

	enum Animation { ANM_UP, ANM_DOWN, ANM_RIGHT, ANM_LEFT };
	enum AnimationFile { ANM_FILE_UP = 3, ANM_FILE_DOWN, ANM_FILE_RIGHT, ANM_FILE_LEFT };

	// Initialize all variables to BASE_CHAR defaults
	virtual void Enter(void);

	// Input
	void Input(void);
	// Draw to the screen
	void Render(void);
	void Update(float fElapsedTime);

	// Get the rectangle used for collision
	RECT GetCollisionRect(void);

	void AddRef() {}
	void Release() {}
	unsigned int GetType() { return 1;}
	bool CheckCollision(IBaseInterface* pBase) { return false; }
};


#endif // CTESTPLAYER_H_