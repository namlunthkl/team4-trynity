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

	SetPlayerPointLight( false );
	SetPlayerPointPosX( 0.5f );
	SetPlayerPointPosY( 0.5f );

	SetItem1PointLight( false );
	SetItem1PointPosX( 0.25f );
	SetItem1PointPosY( 0.25f );

	SetItem2PointLight( false );
	SetItem2PointPosX( 0.75f );
	SetItem2PointPosY( 0.25f );

	SetItem3PointLight( false );
	SetItem3PointPosX( 0.75f );
	SetItem3PointPosY( 0.75f );

	SetItem4PointLight( false );
	SetItem4PointPosX( 0.25f );
	SetItem4PointPosY( 0.75f );
}
void LightEngine::Update( void )
{
	// PLAYER LIGHT
	if( GetPlayerPointLight() )
	{
		SetPlayerPointAlpha( 1.0f );
		SetPlayerPointRed( 1.0f );
		SetPlayerPointGreen( 1.0f );
		SetPlayerPointBlue( 1.0f );
	}
	else
	{
		SetPlayerPointAlpha( 0.0f );
		SetPlayerPointRed( 0.0f );
		SetPlayerPointGreen( 0.0f );
		SetPlayerPointBlue( 0.0f );
	}

	// ITEM1 LIGHT
	if( GetItem1PointLight() )
	{
		SetItem1PointAlpha( 1.0f );
		SetItem1PointRed( 1.0f );
		SetItem1PointGreen( 1.0f );
		SetItem1PointBlue( 1.0f );
	}
	else
	{
		SetItem1PointAlpha( 0.0f );
		SetItem1PointRed( 0.0f );
		SetItem1PointGreen( 0.0f );
		SetItem1PointBlue( 0.0f );
	}

	// Item2 LIGHT
	if( GetItem2PointLight() )
	{
		SetItem2PointAlpha( 1.0f );
		SetItem2PointRed( 1.0f );
		SetItem2PointGreen( 1.0f );
		SetItem2PointBlue( 1.0f );
	}
	else
	{
		SetItem2PointAlpha( 0.0f );
		SetItem2PointRed( 0.0f );
		SetItem2PointGreen( 0.0f );
		SetItem2PointBlue( 0.0f );
	}

	// Item3 LIGHT
	if( GetItem3PointLight() )
	{
		SetItem3PointAlpha( 1.0f );
		SetItem3PointRed( 1.0f );
		SetItem3PointGreen( 1.0f );
		SetItem3PointBlue( 1.0f );
	}
	else
	{
		SetItem3PointAlpha( 0.0f );
		SetItem3PointRed( 0.0f );
		SetItem3PointGreen( 0.0f );
		SetItem3PointBlue( 0.0f );
	}


	// Item4 LIGHT
	if( GetItem4PointLight() )
	{
		SetItem4PointAlpha( 1.0f );
		SetItem4PointRed( 1.0f );
		SetItem4PointGreen( 1.0f );
		SetItem4PointBlue( 1.0f );
	}
	else
	{
		SetItem4PointAlpha( 0.0f );
		SetItem4PointRed( 0.0f );
		SetItem4PointGreen( 0.0f );
		SetItem4PointBlue( 0.0f );
	}
}
void LightEngine::Input( void )
{
	if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_6 ) )
	{
		Morning();
	}
	if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_7 ) )
	{
		Day();
	}
	if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_8 ) )
	{
		Evening();
	}
	if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_9 ) )
	{
		Night();
	}
	if( CSGD_DirectInput::GetInstance()->KeyPressed( DIK_0 ) )
	{
		SetPlayerPointLight( !GetPlayerPointLight() );
	}
}
void LightEngine::ShutDown( void )
{
	SetAmbientAlpha( 0.0f );
	SetAmbientRed( 0.0f );
	SetAmbientGreen(0.0f );
	SetAmbientBlue( 0.0f );

	SetPlayerPointLight( false );
	SetPlayerPointAlpha( 0.0f );
	SetPlayerPointRed( 0.0f );
	SetPlayerPointGreen( 0.0f );
	SetPlayerPointBlue( 0.0f );
	SetPlayerPointPosX( 0.0f );
	SetPlayerPointPosY( 0.0f );

	SetItem1PointLight( false );
	SetItem1PointAlpha( 1.0f );
	SetItem1PointRed( 2.0f );
	SetItem1PointGreen( 1.0f );
	SetItem1PointBlue( 1.0f );
	SetItem1PointPosX( 0.5f );
	SetItem1PointPosY( 0.5f );
}

void LightEngine::SetPlayerPointPos( float fPosX, float fPosY )
{
	SetPlayerPointPosX( fPosX / CGame::GetInstance()->GetScreenWidth() );
	SetPlayerPointPosY( fPosY / CGame::GetInstance()->GetScreenHeight());
}
void LightEngine::SetItem1PointPos( float fPosX, float fPosY )
{
	SetItem1PointPosX( fPosX / CGame::GetInstance()->GetScreenWidth() );
	SetItem1PointPosY( fPosY / CGame::GetInstance()->GetScreenHeight());
}
void LightEngine::SetItem2PointPos( float fPosX, float fPosY )
{
	SetItem2PointPosX( fPosX / CGame::GetInstance()->GetScreenWidth() );
	SetItem2PointPosY( fPosY / CGame::GetInstance()->GetScreenHeight());
}
void LightEngine::SetItem3PointPos( float fPosX, float fPosY )
{
	SetItem3PointPosX( fPosX / CGame::GetInstance()->GetScreenWidth() );
	SetItem3PointPosY( fPosY / CGame::GetInstance()->GetScreenHeight());
}
void LightEngine::SetItem4PointPos( float fPosX, float fPosY )
{
	SetItem4PointPosX( fPosX / CGame::GetInstance()->GetScreenWidth() );
	SetItem4PointPosY( fPosY / CGame::GetInstance()->GetScreenHeight());
}

void LightEngine::Morning( void )
{
	SetAmbientAlpha( 1.0f );
	SetAmbientRed(  1.0f );
	SetAmbientGreen(1.0f );
	SetAmbientBlue( 2.0f );
}
void LightEngine::Day( void )
{
	SetAmbientAlpha( 1.0f );
	SetAmbientRed(  1.0f );
	SetAmbientGreen(1.0f );
	SetAmbientBlue( 1.0f );
}
void LightEngine::Evening( void )
{
	SetAmbientAlpha( 1.0f );
	SetAmbientRed(  1.5f );
	SetAmbientGreen(1.0f );
	SetAmbientBlue( 1.0f );
}
void LightEngine::Night( void )
{
	SetAmbientAlpha( 1.0f );
	SetAmbientRed(  0.2f );
	SetAmbientGreen(0.2f );
	SetAmbientBlue( 0.5f );
}
void LightEngine::Rain( void )
{
	SetAmbientAlpha(1.0f );
	SetAmbientRed(  0.6f );
	SetAmbientGreen(0.6f );
	SetAmbientBlue( 0.8f );
}
void LightEngine::Snow( void )
{
	SetAmbientAlpha(1.0f );
	SetAmbientRed(  0.6f );
	SetAmbientGreen(0.7f );
	SetAmbientBlue( 0.7f );
}
void LightEngine::Leaves( void )
{
	SetAmbientAlpha(1.0f );
	SetAmbientRed(  1.0f );
	SetAmbientGreen(1.5f );
	SetAmbientBlue( 1.2f );
}
void LightEngine::Sand( void )
{
	SetAmbientAlpha(1.0f );
	SetAmbientRed(  1.5f );
	SetAmbientGreen(1.2f );
	SetAmbientBlue( 1.2f );
}
void LightEngine::Ember( void )
{
	SetAmbientAlpha(1.0f );
	SetAmbientRed(  1.2f );
	SetAmbientGreen(0.8f );
	SetAmbientBlue( 0.8f );
}
void LightEngine::FireFlies( void )
{
	SetAmbientAlpha(1.0f );
	SetAmbientRed(  0.5f );
	SetAmbientGreen(0.3f );
	SetAmbientBlue( 0.5f );
}