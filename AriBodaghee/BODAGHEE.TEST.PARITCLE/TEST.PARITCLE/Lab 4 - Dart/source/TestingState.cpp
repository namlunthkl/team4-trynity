#include "TestingState.h"
#include "CGame.h"


TestingState::TestingState(void)
{
	
}
TestingState::~TestingState(){}
TestingState* TestingState::GetInstance(void)
{
	static TestingState instance;
	return &instance;
}
void TestingState::Enter(void)
{
	for( int i = 0 ; i < 1; i ++ )
	{
		p[i].Load( "Resource/data/test.xml" );
	}
}
bool TestingState::Input(void)
{
	if( CSGD_DirectInput::GetInstance()->KeyPressed(DIK_ESCAPE)   ) { return false; }

	if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_RETURN ) )
	{
		for( int i = 0; i < 1; i++ )
		{
		p[i].Fire( 350, 350 );
		}
	}
	return true;
}
void TestingState::Update(void)
{
	for( int i = 0; i < 1; i++ )
	{
		p[i].Update( CGame::GetInstance()->GetElapsedTime() );
	}
}
void TestingState::Render(void)
{
	for( int i = 0; i < 1; i++ )
	{
		p[i].Render();
	}
}
void TestingState::Exit(void)
{
	//p.~ParticleWeapon();
}