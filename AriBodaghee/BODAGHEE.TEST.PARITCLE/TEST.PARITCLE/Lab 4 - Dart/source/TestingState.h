#pragma once
#include "IGameState.h"
#include "SGD Wrappers\CSGD_TextureManager.h"
#include "ParticleWeapon.h"


class TestingState : public IGameState 
{
private:

	TestingState( void );
	TestingState( const TestingState& );
	TestingState& operator=( const TestingState& );
	~TestingState(void);
	int		cursorID;
	

public:
	ParticleWeapon		p[1];
	static TestingState* GetInstance( void );

	void Enter(void);
	bool Input(void);
	void Update(void);
	void Render(void);
	void Exit(void);
};