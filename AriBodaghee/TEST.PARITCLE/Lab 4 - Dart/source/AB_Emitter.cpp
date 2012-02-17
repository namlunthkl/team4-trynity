#include "AB_Emitter.h"
#include "CGame.h"

CEmitter::CEmitter()
{
	m_pData = new CFlyWeight();
	m_pTarget = NULL;
}
CEmitter::CEmitter( const CEmitter& e )
{
	for( unsigned int i = 0; i < e.m_pParticle_List.size(); ++i )
	{
		m_pParticle_List.push_back( e.m_pParticle_List[i] );
	}
	m_pData = e.m_pData;
}
CEmitter& CEmitter::operator=(const CEmitter& e )
{
	if( this == &e ){ return *this; }
	else			{ *this = e; }
	return *this;
}
CEmitter::~CEmitter()
{
	for( unsigned int i = 0; i < m_pParticle_List.size(); ++i )
	{
		delete( CParticle* )( m_pParticle_List[i] );
	}
	delete m_pData;
	m_pParticle_List.clear();
}
void CEmitter::Init()
{
	CParticle* tempParticle;
	for( int i = 0; i < m_pData->GetMaxParticles(); ++i )
	{
		tempParticle = new CParticle();
		tempParticle->SetLife( -1 );
		m_pParticle_List.push_back( tempParticle );

		if( !m_bContinuous ) { ReSpawn( tempParticle ); }
	}
}
void CEmitter::Update( float deltaTime )
{
	for( unsigned int i = 0; i < m_pParticle_List.size(); ++i )
	{
		if( m_pParticle_List[i]->GetLife() > 0 )
		{
			if( m_pData->GetFadeEffect() == 2 )			{ m_pParticle_List[i]->SetAlpha( m_pParticle_List[i]->GetAlpha() - ( m_pData->GetFadeValue() * deltaTime ) ); }
			else if( m_pData->GetFadeEffect() == 1 )	{ m_pParticle_List[i]->SetAlpha( m_pParticle_List[i]->GetAlpha() + ( m_pData->GetFadeValue() * deltaTime ) ); }

			if( m_pData->GetRotationEffect() == 2 )		{ m_pParticle_List[i]->SetRotation( m_pParticle_List[i]->GetRotation() - ( m_pData->GetRotationValue() / 10.0f * deltaTime ) ); }
			else if( m_pData->GetRotationEffect() == 1 ){ m_pParticle_List[i]->SetRotation( m_pParticle_List[i]->GetRotation() + ( m_pData->GetRotationValue() / 10.0f * deltaTime ) ); }

			if( m_pData->GetScaleEffect() == 2 )		{ m_pParticle_List[i]->SetSize( m_pParticle_List[i]->GetSize() + ( ( m_pData->GetScaleValue() / 100 ) * deltaTime ) ); }
			else if( m_pData->GetScaleEffect() == 1 )	{ m_pParticle_List[i]->SetSize( m_pParticle_List[i]->GetSize() - ( ( m_pData->GetScaleValue() / 100 ) * deltaTime ) ); }

			if( m_pData->GetRedEffect() == 2 )			{ m_pParticle_List[i]->SetRed( m_pParticle_List[i]->GetRed() + ( m_pData->GetRedValue() * deltaTime ) ); }
			else if( m_pData->GetRedEffect() == 1 )		{ m_pParticle_List[i]->SetRed( m_pParticle_List[i]->GetRed() - ( m_pData->GetRedValue() * deltaTime ) ); }

			if( m_pData->GetGreenEffect() == 2 )		{ m_pParticle_List[i]->SetGreen( m_pParticle_List[i]->GetGreen() + ( m_pData->GetGreenValue() * deltaTime ) ); }
			else if( m_pData->GetGreenEffect() == 1 )	{ m_pParticle_List[i]->SetGreen( m_pParticle_List[i]->GetGreen() - ( m_pData->GetGreenValue() * deltaTime ) ); }

			if( m_pData->GetBlueEffect() == 2 )			{ m_pParticle_List[i]->SetBlue( m_pParticle_List[i]->GetBlue() + ( m_pData->GetBlueValue() * deltaTime ) ); }
			else if( m_pData->GetBlueEffect() == 1 )	{ m_pParticle_List[i]->SetBlue( m_pParticle_List[i]->GetBlue() - ( m_pData->GetBlueValue() * deltaTime ) ); }

			m_pParticle_List[i]->Update( deltaTime );
		}
		else if( m_bContinuous )
		{
			ReSpawn( m_pParticle_List[i] );
		}

		if( m_bLocked && m_pTarget != NULL )
		{
			m_pData->SetEmitterPositionX( m_pTarget->GetPosX() + m_pTarget->GetWidth() / 2 );
			m_pData->SetEmitterPositionY( m_pTarget->GetPosY() + m_pTarget->GetHeight() / 2 );
		}
		else
		{
		m_pData->SetEmitterPositionX( m_pData->GetEmitterPositionX() + ( m_pData->GetEmitterVelocityX() * deltaTime ) );
		m_pData->SetEmitterPositionY( m_pData->GetEmitterPositionY() + ( m_pData->GetEmitterVelocityY() * deltaTime ) );
		}
	}
}
void CEmitter::ReSpawn( CParticle* p )
{
	p->SetLife( (float)( rand()% (int)( m_pData->GetMaxLife() * 1000 ) ) );
	p->SetSize( m_pData->GetSize() );

	if( m_pData->GetRotationEffect() > 0 )	{ p->SetRotation( (float)( rand()% 100 / 11 ) ); }
	else									{ p->SetRotation( 0.0f ); }
	if( rand()% 1000 >= 500 )				{ p->SetVelocityX( (  rand()% (int)( m_pData->GetMaxVelocityX() - m_pData->GetMinVelocityX() + 1 ) + m_pData->GetMinVelocityX() ) ); }
	else									{ p->SetVelocityX( -( rand()% (int)( m_pData->GetMaxVelocityX() - m_pData->GetMinVelocityX() + 1 ) + m_pData->GetMinVelocityX() ) ); }
	if( rand()% 1000 <= 500 )				{ p->SetVelocityY( (  rand()% (int)( m_pData->GetMaxVelocityY() - m_pData->GetMinVelocityY() + 1 ) + m_pData->GetMinVelocityY() ) ); }
	else									{ p->SetVelocityY( -( rand()% (int)( m_pData->GetMaxVelocityY() - m_pData->GetMinVelocityY() + 1 ) + m_pData->GetMinVelocityY() ) ); }

	if( m_pData->GetFadeEffect() == 0 || m_pData->GetFadeEffect() == 2 ) { p->SetAlpha( 255 ); }
	else { p->SetAlpha( 0.0f ); }
	if( m_pData->GetRedEffect() == 0 || m_pData->GetRedEffect() == 1 ) { p->SetRed( 255 ); }
	else { p->SetRed( 0.0f ); }
	if( m_pData->GetGreenEffect() == 0 || m_pData->GetGreenEffect() == 1 ) { p->SetGreen( 255 ); }
	else { p->SetGreen( 0.0f ); }
	if( m_pData->GetBlueEffect() == 0 || m_pData->GetBlueEffect() == 1 ) { p->SetBlue( 255 ); }
	else { p->SetBlue( 0.0f ); }

	if( m_pData->GetSpawnPattern() == 1 )
	{
		if( rand()% 1000 <= 500 )	{ p->SetPositionX( m_pData->GetEmitterPositionX() - rand()%( (int)m_pData->GetMaxSpawnRadius() + 1 ) ); }
		else						{ p->SetPositionX( m_pData->GetEmitterPositionX() + rand()%( (int)m_pData->GetMaxSpawnRadius() + 1 ) ); }
		if( rand()% 1000 <= 500 )	{ p->SetPositionY( m_pData->GetEmitterPositionY() - rand()%( (int)m_pData->GetMaxSpawnRadius() + 1 ) ); }
		else						{ p->SetPositionY( m_pData->GetEmitterPositionY() + rand()%( (int)m_pData->GetMaxSpawnRadius() + 1 ) ); }
	}
	if( m_pData->GetSpawnPattern() == 2 )
	{
		p->SetPositionX( (float)( rand()% CGame::GetInstance()->GetScreenW() ) );
		p->SetPositionY( (float)( rand()% CGame::GetInstance()->GetScreenH() ) );
	}
	if( m_pData->GetSpawnPattern() == 3 )
	{
		p->SetPositionX( m_pData->GetEmitterPositionX() - ( rand()%(int)( m_pData->GetSpawnAreaWidth() * 2 + 1 ) - m_pData->GetSpawnAreaWidth() ) / 2 );
		p->SetPositionY( m_pData->GetEmitterPositionY() - ( rand()%(int)( m_pData->GetSpawnAreaHeight() * 2 + 1 ) - m_pData->GetSpawnAreaHeight() ) / 2 );
	}
}
void CEmitter::Render( void )
{
	DWORD tempBlends[2] = {0};
	CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->GetRenderState( D3DRS_SRCBLEND, &tempBlends[0] );
	CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->GetRenderState( D3DRS_DESTBLEND, &tempBlends[1] );

	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
	int image;
	CEmitter* tempEmitter = this;

	if( tempEmitter->m_nImage == -1 )	{ return; }
	else								{ image = tempEmitter->m_nImage; }

	if( tempEmitter->m_pData->GetUseBlend() )
	{
		CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->SetRenderState( D3DRS_SRCBLEND, tempEmitter->m_pData->GetSource() );
		CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->SetRenderState( D3DRS_DESTBLEND, tempEmitter->m_pData->GetDestination() );
	}

	for( int i = tempEmitter->m_pParticle_List.size() - 1; i >= 0; --i )
	{
		CParticle* tempParticle = tempEmitter->m_pParticle_List[i];
		if( tempParticle->GetLife() <= 0 ) { continue; }
		int OffSetX = (int)( tempParticle->GetPositionX() - (float)CSGD_TextureManager::GetInstance()->GetTextureWidth( image ) * tempParticle->GetSize() / 2.0f );
		int OffSetY = (int)( tempParticle->GetPositionY() - (float)CSGD_TextureManager::GetInstance()->GetTextureHeight( image ) * tempParticle->GetSize() / 2.0f );
	
		if( tempParticle->GetRotation() == 0 )	
		{ CSGD_TextureManager::GetInstance()->Draw( image, OffSetX, OffSetY, tempParticle->GetSize(), tempParticle->GetSize(), NULL, 0,0,0, D3DCOLOR_ARGB( (int)tempParticle->GetAlpha(), (int)tempParticle->GetRed(),(int)tempParticle->GetGreen(),(int)tempParticle->GetBlue() ) ); }
		else									
		{ CSGD_TextureManager::GetInstance()->Draw( image, (int)tempParticle->GetPositionX(), (int)tempParticle->GetPositionY(), tempParticle->GetSize(), tempParticle->GetSize(), NULL, 0,0,0, D3DCOLOR_ARGB( (int)tempParticle->GetAlpha(), (int)tempParticle->GetRed(),(int)tempParticle->GetGreen(),(int)tempParticle->GetBlue() ) ); }
		
	}
	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();

	CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->SetRenderState( D3DRS_SRCBLEND, tempBlends[0] );
	CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->SetRenderState( D3DRS_DESTBLEND, tempBlends[1] );
	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
}
void CEmitter::LockonOBJ(CBase* OBJ)
{
	if( OBJ != NULL )
	{
		m_bLocked = true;
		m_pTarget = OBJ;
	}
}