#include "StdAfx.h"
#include "LightEngine.h"


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
	SetAmbientRed( 0.25f );
	SetAmbientGreen(0.25f );
	SetAmbientBlue( 0.25f );
	
	SetPointAlpha( 1.0f );
	SetPointRed( 1.0f );
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