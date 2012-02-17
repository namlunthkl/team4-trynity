#include "AB_Particle.h"

CParticle::CParticle(){}
CParticle::~CParticle(){}
void CParticle::Update( float deltaTime )
{
	SetPositionX( GetPositionX() + ( GetVelocityX() * deltaTime ) );
	SetPositionY( GetPositionY() + ( GetVelocityY() * deltaTime ) );
	SetLife( GetLife() - ( 10000 * deltaTime ) );

	if( GetAlpha() < 0 )		{ SetAlpha( 0 ); }
	else if( GetAlpha() > 255 ) { SetAlpha( 255 ); }

	if( GetRed() < 0 )			{ SetRed( 0 ); }
	else if( GetRed() > 255 )	{ SetRed( 255 ); }

	if( GetGreen() < 0 )		{ SetGreen( 0 ); }
	else if( GetGreen() > 255 ) { SetGreen( 255 ); }

	if( GetBlue() < 0 )			{ SetBlue( 0 ); }
	else if( GetBlue() > 255 )	{ SetBlue( 255 ); }
}