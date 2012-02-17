#ifndef FLYWEIGHT_H_
#define FLYWEIGHT_H_

class CFlyWeight
{
private:
	float	m_fSize;
	float	m_fMaxLife;
	float	m_fMinVelocityX;
	float	m_fMaxVelocityX;
	float	m_fMinVelocityY;
	float	m_fMaxVelocityY;
	float	m_fSpawnAreaWidth;
	float	m_fSpawnAreaHeight;
	float	m_fMinSpawnRadius;
	float	m_fMaxSpawnRadius;

	float	m_fEmitterPositionX;
	float	m_fEmitterPositionY;
	float	m_fEmitterVelocityX;
	float	m_fEmitterVelocityY;

	float	m_fFadeValue;
	float	m_fScaleValue;
	float	m_fRotationValue;
	float	m_fRedValue;
	float	m_fGreenValue;
	float	m_fBlueValue;

	int		m_nFadeEffect;
	int		m_nScaleEffect;
	int		m_nRotationEffect;
	int		m_nRedEffect;
	int		m_nGreenEffect;
	int		m_nBlueEffect;

	int		m_nSpawnPattern;
	int		m_nSource;
	int		m_nDestination;
	int		m_nMaxParticles;
	
	bool	m_bUseBlend;
	
public:

	float GetSize( void )								{ return m_fSize; }
	float GetMaxLife( void )							{ return m_fMaxLife; }
	float GetMinVelocityX( void )						{ return m_fMinVelocityX; }
	float GetMaxVelocityX( void )						{ return m_fMaxVelocityX; }
	float GetMinVelocityY( void )						{ return m_fMinVelocityY; }
	float GetMaxVelocityY( void )						{ return m_fMaxVelocityY; }
	float GetSpawnAreaWidth( void )						{ return m_fSpawnAreaWidth; }
	float GetSpawnAreaHeight( void )					{ return m_fSpawnAreaHeight; }
	float GetMinSpawnRadius( void )						{ return m_fMinSpawnRadius; }
	float GetMaxSpawnRadius( void )						{ return m_fMaxSpawnRadius; }

	float GetEmitterPositionX( void )					{ return m_fEmitterPositionX; }
	float GetEmitterPositionY( void )					{ return m_fEmitterPositionY; }
	float GetEmitterVelocityX( void )					{ return m_fEmitterVelocityX; }
	float GetEmitterVelocityY( void )					{ return m_fEmitterVelocityY; }

	float GetFadeValue( void )							{ return m_fFadeValue; }
	float GetScaleValue( void )							{ return m_fScaleValue; }
	float GetRotationValue( void )						{ return m_fRotationValue; }
	float GetRedValue( void )							{ return m_fRedValue; }
	float GetGreenValue( void )							{ return m_fGreenValue; }
	float GetBlueValue( void )							{ return m_fBlueValue; }

	int   GetFadeEffect( void )							{ return m_nFadeEffect; }
	int   GetScaleEffect( void )						{ return m_nScaleEffect; }
	int   GetRotationEffect( void )						{ return m_nRotationEffect; }
	int   GetRedEffect( void )							{ return m_nRedEffect; }
	int   GetGreenEffect( void )						{ return m_nGreenEffect; }
	int   GetBlueEffect( void )							{ return m_nBlueEffect; }

	int   GetSpawnPattern( void )						{ return m_nSpawnPattern; }
	int   GetSource( void )								{ return m_nSource; }
	int   GetDestination( void )						{ return m_nDestination; }
	int   GetMaxParticles( void )						{ return m_nMaxParticles; }

	bool  GetUseBlend( void )							{ return m_bUseBlend; }

	void SetSize( float fSize )							{ m_fSize = fSize; }
	void SetMaxLife( float fMaxLife )					{ m_fMaxLife = fMaxLife; }
	void SetMinVelocityX( float fMinVelocityX )			{ m_fMinVelocityX = fMinVelocityX; }
	void SetMaxVelocityX( float fMaxVelocityX )			{ m_fMaxVelocityX = fMaxVelocityX; }
	void SetMinVelocityY( float fMinVelocityY )			{ m_fMinVelocityY = fMinVelocityY; }
	void SetMaxVelocityY( float fMaxVelocityY )			{ m_fMaxVelocityY = fMaxVelocityY; }
	void SetSpawnAreaWidth( float fSpawnAreaWidth )		{ m_fSpawnAreaWidth = fSpawnAreaWidth; }
	void SetSpawnAreaHeight( float fSpawnAreaHeight )	{ m_fSpawnAreaHeight = fSpawnAreaHeight; }
	void SetMinSpawnRadius( float fMinSpawnRadius )		{ m_fMinSpawnRadius = fMinSpawnRadius; }
	void SetMaxSpawnRadius( float fMaxSpawnRadius )		{ m_fMaxSpawnRadius = fMaxSpawnRadius; }

	void SetEmitterPositionX( float fEmitterPositionX )	{ m_fEmitterPositionX = fEmitterPositionX; }
	void SetEmitterPositionY( float fEmitterPositionY )	{ m_fEmitterPositionY = fEmitterPositionY; }
	void SetEmitterVelocityX( float fEmitterVelocityX )	{ m_fEmitterVelocityX = fEmitterVelocityX; }
	void SetEmitterVelocityY( float fEmitterVelocityY )	{ m_fEmitterVelocityY = fEmitterVelocityY; }

	void SetFadeValue( float fFadeValue )				{ m_fFadeValue = fFadeValue; }
	void SetScaleValue( float fScaleValue )				{ m_fScaleValue = fScaleValue; }
	void SetRotationValue( float fRotationValue )		{ m_fRotationValue = fRotationValue; }
	void SetRedValue( float fRedValue )					{ m_fRedValue = fRedValue; }
	void SetGreenValue( float fGreenValue )				{ m_fGreenValue = fGreenValue; }
	void SetBlueValue( float fBlueValue )				{ m_fBlueValue = fBlueValue; }

	void SetFadeEffect( int nFadeEffect )				{ m_nFadeEffect = nFadeEffect; }
	void SetScaleEffect( int nScaleEffect )				{ m_nScaleEffect = nScaleEffect; }
	void SetRotationEffect( int nRotationEffect )		{ m_nRotationEffect = nRotationEffect; }
	void SetRedEffect( int nRedEffect )					{ m_nRedEffect = nRedEffect; }
	void SetGreenEffect( int nGreenEffect )				{ m_nGreenEffect = nGreenEffect; }
	void SetBlueEffect( int nBlueEffect )				{ m_nBlueEffect = nBlueEffect; }

	void SetSpawnPattern( int nSpawnPattern )			{ m_nSpawnPattern = nSpawnPattern; }
	void SetSource( int nSource )						{ m_nSource = nSource; }
	void SetDestination( int nDestination )				{ m_nDestination = nDestination; }
	void SetMaxParticles( int nMaxParticles )			{ m_nMaxParticles = nMaxParticles; }

	void SetUseBlend( bool bUseBlend )					{ m_bUseBlend = bUseBlend; }

	CFlyWeight();
	~CFlyWeight();
};

#endif