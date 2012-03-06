#include "StdAfx.h"
#include "LightEngine.h"
#include "..\Wrappers\CSGD_DirectInput.h"
#include "..\CGame.h"

LightEngine::LightEngine(void){}
LightEngine::~LightEngine(void)
{
	ShutDown();
}
LightEngine* LightEngine::GetInstance(void)
{
	static LightEngine instance;
	return &instance;
}
void LightEngine::Initialize( void )
{
	SetAmbientAlpha( 1.0f );
	SetAmbientRed( 1.0f );
	SetAmbientGreen(1.0f );
	SetAmbientBlue( 1.0f );

	SetPointAlpha( 1.0f );
	SetPointRed( 2.0f );
	SetPointGreen( 1.0f );
	SetPointBlue( 1.0f );

	SetPointPosX( 0.5f );
	SetPointPosY( 0.5f );
}
void LightEngine::Update( void )
{

}
void LightEngine::Input( void )
{
	if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_6 ) )
	{
		//Morning
		SetAmbientAlpha( 1.0f );
		SetAmbientRed(  1.0f );
		SetAmbientGreen(1.0f );
		SetAmbientBlue( 2.0f );
	}
	if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_7 ) )
	{
		//DayTime
		SetAmbientAlpha( 1.0f );
		SetAmbientRed(  1.0f );
		SetAmbientGreen(1.0f );
		SetAmbientBlue( 1.0f );
	}
	if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_8 ) )
	{
		//Evening
		SetAmbientAlpha( 1.0f );
		SetAmbientRed(  1.5f );
		SetAmbientGreen(1.0f );
		SetAmbientBlue( 1.0f );
	}
	if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_9 ) )
	{
		//Night
		SetAmbientAlpha( 1.0f );
		SetAmbientRed(  0.2f );
		SetAmbientGreen(0.2f );
		SetAmbientBlue( 0.5f );
	}
}
void LightEngine::ShutDown( void )
{
	SetAmbientAlpha( 0.0f );
	SetAmbientRed( 0.0f );
	SetAmbientGreen(0.0f );
	SetAmbientBlue( 0.0f );

	SetPointAlpha( 0.0f );
	SetPointRed( 0.0f );
	SetPointGreen( 0.0f );
	SetPointBlue( 0.0f );

	SetPointPosX( 0.0f );
	SetPointPosY( 0.0f );
}

void LightEngine::SetPointPos( float fPosX, float fPosY )
{
	SetPointPosX( fPosX / CGame::GetInstance()->GetScreenWidth() );
	SetPointPosY( fPosY / CGame::GetInstance()->GetScreenHeight());
}