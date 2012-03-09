#include "StdAfx.h"
#include "LightEngine.h"
#include "..\Wrappers\CSGD_DirectInput.h"
#include "..\Wrappers\SGD_Math.h"
#include "..\CGame.h"
#include "..\Camera\CCameraControl.h"


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
	SetCurrentCycle( 0 );
	SetCurrentTime( 0.0f );
	SetTimeToWait( 0.0f );

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

	SetPointRadius( 0.3f );
	SetItemRadius( 0.2f );

}
void LightEngine::Update( void )
{
	SetCurrentTime( GetCurrentTime() + CGame::GetInstance()->GetTimer().m_fElapsedTime );
	Cycle();
	// PLAYER LIGHT
	if( GetPlayerPointLight() )
	{
		SetPlayerPointAlpha( 1.0f );
		SetPlayerPointRed( 1.0f );
		SetPlayerPointGreen( 1.0f );
		SetPlayerPointBlue( 1.0f );
		SetPointRadius( 0.3f );
	}
	else
	{
		SetPlayerPointAlpha( 0.0f );
		SetPlayerPointRed( 0.0f );
		SetPlayerPointGreen( 0.0f );
		SetPlayerPointBlue( 0.0f );
		SetPointRadius( 0.0f );
	}

	// ITEM1 LIGHT
	if( GetItem1PointLight() )
	{
		SetItem1PointAlpha( 1.0f );
		SetItem1PointRed( 1.0f );
		SetItem1PointGreen( 1.0f );
		SetItem1PointBlue( 1.0f );
		Flicker();
	}
	else
	{
		SetItem1PointAlpha( 0.0f );
		SetItem1PointRed( 0.0f );
		SetItem1PointGreen( 0.0f );
		SetItem1PointBlue( 0.0f );
		SetItemRadius( 0.0f );
	}

	// Item2 LIGHT
	if( GetItem2PointLight() )
	{
		SetItem2PointAlpha( 1.0f );
		SetItem2PointRed( 1.0f );
		SetItem2PointGreen( 1.0f );
		SetItem2PointBlue( 1.0f );
		Flicker();
	}
	else
	{
		SetItem2PointAlpha( 0.0f );
		SetItem2PointRed( 0.0f );
		SetItem2PointGreen( 0.0f );
		SetItem2PointBlue( 0.0f );
		SetItemRadius( 0.0f );
	}

	// Item3 LIGHT
	if( GetItem3PointLight() )
	{
		SetItem3PointAlpha( 1.0f );
		SetItem3PointRed( 1.0f );
		SetItem3PointGreen( 1.0f );
		SetItem3PointBlue( 1.0f );
		Flicker();
	}
	else
	{
		SetItem3PointAlpha( 0.0f );
		SetItem3PointRed( 0.0f );
		SetItem3PointGreen( 0.0f );
		SetItem3PointBlue( 0.0f );
		SetItemRadius( 0.0f );
	}
	// Item4 LIGHT
	if( GetItem4PointLight() )
	{
		SetItem4PointAlpha( 1.0f );
		SetItem4PointRed( 1.0f );
		SetItem4PointGreen( 1.0f );
		SetItem4PointBlue( 1.0f );
		Flicker();
	}
	else
	{
		SetItem4PointAlpha( 0.0f );
		SetItem4PointRed( 0.0f );
		SetItem4PointGreen( 0.0f );
		SetItem4PointBlue( 0.0f );
		SetItemRadius( 0.0f );
	}
}
void LightEngine::Input( void ){}
void LightEngine::ShutDown( void )
{
	SetCurrentCycle( 0 );
	SetCurrentTime( 0.0f );
	SetTimeToWait( 0.0f );

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

	SetItem2PointLight( false );
	SetItem2PointAlpha( 1.0f );
	SetItem2PointRed( 2.0f );
	SetItem2PointGreen( 1.0f );
	SetItem2PointBlue( 1.0f );
	SetItem2PointPosX( 0.5f );
	SetItem2PointPosY( 0.5f );

	SetItem3PointLight( false );
	SetItem3PointAlpha( 1.0f );
	SetItem3PointRed( 2.0f );
	SetItem3PointGreen( 1.0f );
	SetItem3PointBlue( 1.0f );
	SetItem3PointPosX( 0.5f );
	SetItem3PointPosY( 0.5f );

	SetItem4PointLight( false );
	SetItem4PointAlpha( 1.0f );
	SetItem4PointRed( 2.0f );
	SetItem4PointGreen( 1.0f );
	SetItem4PointBlue( 1.0f );
	SetItem4PointPosX( 0.5f );
	SetItem4PointPosY( 0.5f );

	SetPointRadius( 0.0f );
	SetItemRadius( 0.0f );
}

void LightEngine::SetPlayerPointPos( float fPosX, float fPosY )
{
	SetPlayerPointPosX( ( fPosX - ( -CCameraControl::GetInstance()->GetPositionX() ) ) / CGame::GetInstance()->GetScreenWidth() );
	SetPlayerPointPosY( ( fPosY - ( -CCameraControl::GetInstance()->GetPositionY() ) ) / CGame::GetInstance()->GetScreenHeight());
}
void LightEngine::SetItem1PointPos( float fPosX, float fPosY )
{
	SetItem1PointPosX( ( fPosX - ( -CCameraControl::GetInstance()->GetPositionX() ) ) / CGame::GetInstance()->GetScreenWidth() );
	SetItem1PointPosY( ( fPosY - ( -CCameraControl::GetInstance()->GetPositionY() ) ) / CGame::GetInstance()->GetScreenHeight());
}
void LightEngine::SetItem2PointPos( float fPosX, float fPosY )
{
	SetItem2PointPosX( ( fPosX - ( -CCameraControl::GetInstance()->GetPositionX() ) ) / CGame::GetInstance()->GetScreenWidth() );
	SetItem2PointPosY( ( fPosY - ( -CCameraControl::GetInstance()->GetPositionY() ) ) / CGame::GetInstance()->GetScreenHeight());
}
void LightEngine::SetItem3PointPos( float fPosX, float fPosY )
{
	SetItem3PointPosX( ( fPosX - ( -CCameraControl::GetInstance()->GetPositionX() ) ) / CGame::GetInstance()->GetScreenWidth() );
	SetItem3PointPosY( ( fPosY - ( -CCameraControl::GetInstance()->GetPositionY() ) ) / CGame::GetInstance()->GetScreenHeight());
}
void LightEngine::SetItem4PointPos( float fPosX, float fPosY )
{
	SetItem4PointPosX( ( fPosX - ( -CCameraControl::GetInstance()->GetPositionX() ) ) / CGame::GetInstance()->GetScreenWidth() );
	SetItem4PointPosY( ( fPosY - ( -CCameraControl::GetInstance()->GetPositionY() ) ) / CGame::GetInstance()->GetScreenHeight());
}

void LightEngine::Flicker(void)
{
	SetItemRadius( RandomFloat( 0.15f, 0.17f ) );
}

void LightEngine::Morning( void )
{
	SetAmbientAlpha( 1.0f );
	SetAmbientRed(  1.0f );
	SetAmbientGreen(1.0f );
	SetAmbientBlue( 2.0f );
}
void LightEngine::Afternoon( void )
{
	SetAmbientAlpha( 1.0f );
	SetAmbientRed(  1.0f );
	SetAmbientGreen(1.0f );
	SetAmbientBlue( 1.5f );
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
void LightEngine::Dusk( void )
{
	SetAmbientAlpha( 1.0f );
	SetAmbientRed(  0.9f );
	SetAmbientGreen(0.5f );
	SetAmbientBlue( 0.5f );
}
void LightEngine::Night( void )
{
	SetAmbientAlpha( 1.0f );
	SetAmbientRed(  0.2f );
	SetAmbientGreen(0.2f );
	SetAmbientBlue( 0.5f );
}
void LightEngine::Dawn( void )
{
	SetAmbientAlpha( 1.0f );
	SetAmbientRed(  0.6f );
	SetAmbientGreen(0.6f );
	SetAmbientBlue( 1.0f );
}

void LightEngine::Cycle( void )
{
	if( GetCurrentTime() >= GetTimeToWait() )
	{
		SetCurrentCycle( GetCurrentCycle() + 1 );
		if( GetCurrentCycle() > 7 )
		{
			SetCurrentCycle( 1 );
		}
		switch( GetCurrentCycle() )
		{
		case 1:
			{
				Morning();
				SetCurrentTime( 0.0f );
				SetTimeToWait( 60.0f );
			}
			break;
		case 2:
			{
				Afternoon();
				SetCurrentTime( 0.0f );
				SetTimeToWait( 60.0f );
			}
			break;
		case 3:
			{
				Day();
				SetCurrentTime( 50.0f );
				SetTimeToWait( 60.0f );
			}
			break;
		case 4:
			{
				Evening();
				SetCurrentTime( 0.0f );
				SetTimeToWait( 60.0f );
			}
			break;
		case 5:
			{
				Dusk();
				SetCurrentTime( 0.0f );
				SetTimeToWait( 60.0f );
			}
			break;
		case 6:
			{
				Night();
				SetCurrentTime( 0.0f );
				SetTimeToWait( 60.0f );
			}
			break;
		case 7:
			{
				Dawn();
				SetCurrentTime( 0.0f );
				SetTimeToWait( 60.0f );
			}
			break;
		}
	}
}