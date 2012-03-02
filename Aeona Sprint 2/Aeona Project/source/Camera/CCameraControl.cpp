#include "..\StdAfx.h"
#include "CCameraControl.h"


CCameraControl::CCameraControl(void)
{
	SetTime( 0 );
}
CCameraControl* CCameraControl::GetInstance(void)
{
	static CCameraControl instance;
	return &instance;
}
CCameraControl::~CCameraControl(void){}
void CCameraControl::InitializeCamera( int screenWidth, int screenHeight )
{
	D3DXMatrixPerspectiveOffCenterLH( &m_D3DProjection, (float)(screenWidth >> 1), (float)(screenWidth >> 1), (float)(screenHeight >> 1), (float)(screenHeight >> 1), 0.0f, 1.0f );
	SetScale( 1.0f );
	SetPositionX( 0.0f );
	SetPositionY( 0.0f );
	m_nScreenWidth = screenWidth;
	m_nScreenHeight = screenHeight;

	SetChange( true );
	SetStop( false );
	SetKillCam( false );
	SetTimeToWait( 0 );

	SetReleaseButton( false );
}
void CCameraControl::Update( float fTime )
{
	SetTime( fTime );
	if( GetKillCam() ) { KillCamSequence( 3 ); }
}
void CCameraControl::KillCamSequence( float fAmountOfTimeToPause )
{
	if( GetChange() )
	{
		if( !GetStop() ) { SetScale( GetScale() + 7.0f * GetTime() ); }
		if( GetScale() >= 3.0f )
		{
			SetStop( true );
			SetTimeToWait( GetTimeToWait() + ( GetTime() ) );
			if( GetTimeToWait() >= fAmountOfTimeToPause ) { SetChange( false ); }
		}
	}
	if( !GetChange() )
	{
		SetTimeToWait( 0 );
		SetScale( GetScale() - 2.0f * GetTime() );
		if( GetScale() <= 1.0f )
		{
			SetChange( true );
			SetStop( false );
			SetKillCam( false );
		}
	}
}
void CCameraControl::ChargeCamSequence( float fChargeTime )
{
	if( fChargeTime >= 2.0f )
	{
		SetScale( GetScale() + 0.02f * GetTime() );

		if( GetScale() >= 1.3f )
		{
			SetScale( 1.3f );
		}	
	}	
	if( fChargeTime == 0.0f && GetReleaseButton() )
	{
		SetScale( GetScale() - 3.0f * GetTime() );

		if( GetScale() <= 1.0f )
		{
			SetScale( 1.0f );
			SetReleaseButton( false );
		}
	}

}

D3DXMATRIX CCameraControl::GetView( void )
{
	//RKP
	D3DXMATRIX S, T, t1, t2;
	D3DXMatrixScaling( &S, m_D3DScale, m_D3DScale, 1.0f  );
	D3DXMatrixTranslation( &T, m_D3DPosition.x, m_D3DPosition.y, 0  );
	D3DXMatrixTranslation( &t1, (float)(-m_nScreenWidth >> 1), (float)(-m_nScreenHeight >> 1), 0.0f );
	D3DXMatrixTranslation( &t2, (float)(m_nScreenWidth >> 1), (float)(m_nScreenHeight >> 1), 0.0f );
	//RKP

	return ( T * t1 * S * t2 );
}
void CCameraControl::SetSpriteProjection( void )
{
	CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->SetTransform( D3DTS_PROJECTION, &m_D3DProjection );
}
D3DXMATRIX CCameraControl::GetOffset( void )
{
	D3DXMATRIX matFirstTranslation ;
	D3DXMatrixTranslation( &matFirstTranslation, (float)(m_nScreenWidth >> 1), (float)(m_nScreenHeight >> 1), 0.0f  );

	return matFirstTranslation;
}