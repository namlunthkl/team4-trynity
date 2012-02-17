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
	SetVisualizer( 0,0,CGame::GetInstance()->GetScreenH(),CGame::GetInstance()->GetScreenW() );
	m_EM = EmitterManager::GetInstance();
	m_nVisualizerID = CSGD_TextureManager::GetInstance()->LoadTexture("Resource/Graphics/Light.bmp",0xff000000);
	m_EM->Load( "xmltext.txt" );
}
bool TestingState::Input(void)
{
	if( CSGD_DirectInput::GetInstance()->KeyPressed(DIK_ESCAPE) || CSGD_DirectInput::GetInstance()->KeyPressed( DIK_RETURN ) ) { return false; }

	
	return true;
}
void TestingState::Update(void)
{

}
void TestingState::Render(void)
{
	CSGD_TextureManager::GetInstance()->Draw(m_nVisualizerID,m_rVisualizer.left,m_rVisualizer.top,0.75f,0.75f,NULL,0,0,0,0xffffffff);
	
}
void TestingState::Exit(void)
{

}