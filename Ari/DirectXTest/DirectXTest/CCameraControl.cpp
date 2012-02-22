#include "CCameraControl.h"

CCameraControl::CCameraControl(void)
{
	SetTime( 0 );
}
CCameraControl::~CCameraControl(void){}
void CCameraControl::InitializeCamera()
{
	D3DXVECTOR3 eye(0,3.0f,0.01f), at(0,0,0), up(0,1,0);
	float fov = (D3DXToRadian(75)), aspect = (WINDOW_WIDTH/(float)WINDOW_HEIGHT), znear = 0.01f, zfar = 100.0f; 
	D3DXMatrixPerspectiveFovLH(&m_D3DProjection,fov,aspect,znear,zfar);
	SetYMod( 3 );
	SetChange( true );
	SetStop( false );
	SetKillCam( false );
	SetTimeToWait( 0 );
}
void CCameraControl::Update( float fTime )
{
	SetTime( fTime );
	if( GetKillCam() )
	{
		KillCamSequence( 2 );
	}
	D3DXVECTOR3 eye1(0, GetYMod(), 0.01f ), at1(0,0,0), up1(0,1,0);
	D3DXMatrixLookAtLH(&m_D3DCamera,&eye1,&at1,&up1);
}
void CCameraControl::KillCamSequence( float fAmountOfTimeToPause )
{
	if( GetChange() )
	{
		if( !GetStop() )
		{
			SetYMod( GetYMod() - ( 10 * GetTime() ) );
		}

		if( GetYMod() <= 1.0 )
		{
			SetStop( true );
			SetTimeToWait( GetTimeToWait() + ( 1 * GetTime() ) );
			if( GetTimeToWait() >= fAmountOfTimeToPause )
			{
				SetChange( false );
			}
		}
	}

	if( !GetChange() )
	{
		SetTimeToWait( 0 );
		SetYMod( GetYMod() + ( 3 * GetTime() ) );
		if( GetYMod() >= 3.0f )
		{
			SetChange( true );
			SetStop( false );
			SetKillCam( false );
		}
	}
}
void CCameraControl::ChargeCamSequence( float fChargeTime )
{

}