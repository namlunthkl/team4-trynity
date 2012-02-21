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
	cursorID = CSGD_TextureManager::GetInstance()->LoadTexture( "Resource/Particles/Spark.bmp", D3DCOLOR_ARGB( 255, 255, 255, 255 ) );
	for( int i = 0 ; i < 1; i ++ )
	{
		p[i].Load( "Resource/data/MainMenuFog.xml" );
	}
}
bool TestingState::Input(void)
{
	if( CSGD_DirectInput::GetInstance()->KeyPressed(DIK_ESCAPE)   ) { return false; }
	if( CSGD_DirectInput::GetInstance()->KeyPressed(DIK_RETURN)   ) {}

	if( CSGD_DirectInput::GetInstance()->MouseButtonPressed(0)  )
	{
		for( int i = 0; i < 1; i++ )
		{
			p[i].Fire( (float)(CSGD_DirectInput::GetInstance()->MouseGetPosX() ), (float)(CSGD_DirectInput::GetInstance()->MouseGetPosY() ) );
		}
	}
	return true;
}
void TestingState::Update(void)
{
	for( int i = 0; i < 1; i++ )
	{
		//p[i].Fire( (int)(CSGD_DirectInput::GetInstance()->MouseGetPosX()), (int)(CSGD_DirectInput::GetInstance()->MouseGetPosY()) );
		p[i].Update( CGame::GetInstance()->GetElapsedTime() );
	}
}
void TestingState::Render(void)
{
	CSGD_TextureManager::GetInstance()->Draw( cursorID, CSGD_DirectInput::GetInstance()->MouseGetPosX(), CSGD_DirectInput::GetInstance()->MouseGetPosY() );
	for( int i = 0; i < 1; i++ )
	{
		p[i].Render();
	}
}
void TestingState::Exit(void)
{
	
}