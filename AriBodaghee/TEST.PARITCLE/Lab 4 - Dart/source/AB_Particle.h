#ifndef PARTICLE_H_
#define PARTICLE_H_

class CParticle
{
private:
	float m_fAlpha;
	float m_fRed;
	float m_fGreen;
	float m_fBlue;
	float m_fPositionX;
	float m_fPositionY;
	float m_fVelocityX;
	float m_fVelocityY;
	float m_fSize;
	float m_fRotation;
	float m_fLife;
public:

	float GetAlpha( void )		{ return m_fAlpha; }
	float GetRed( void )		{ return m_fRed; }
	float GetGreen( void )		{ return m_fGreen; }
	float GetBlue( void )		{ return m_fBlue; }
	float GetPositionX( void )	{ return m_fPositionX; }
	float GetPositionY( void )	{ return m_fPositionY; }
	float GetVelocityX( void )	{ return m_fVelocityX; }
	float GetVelocityY( void )	{ return m_fVelocityY; }
	float GetSize( void )		{ return m_fSize; }
	float GetRotation( void )	{ return m_fRotation; }
	float GetLife( void )		{ return m_fLife; }

	void SetAlpha( float fAlpha )			{ m_fAlpha = fAlpha; }
	void SetRed( float fRed )				{ m_fRed = fRed; }
	void SetGreen( float fGreen )			{ m_fGreen = fGreen; }
	void SetBlue( float fBlue )				{ m_fBlue = fBlue; }
	void SetPositionX( float fPositionX )	{ m_fPositionX = fPositionX; }
	void SetPositionY( float fPositionY )	{ m_fPositionY = fPositionY; }
	void SetVelocityX( float fVelocityX )	{ m_fVelocityX = fVelocityX; }
	void SetVelocityY( float fVelocityY )	{ m_fVelocityY = fVelocityY; }
	void SetSize( float fSize )				{ m_fSize = fSize; }
	void SetRotation( float fRotation )		{ m_fRotation = fRotation; }
	void SetLife( float fLife )				{ m_fLife = fLife; }

	CParticle();
	~CParticle();

	void Update( float deltaTime );
};
#endif