#include "AB_FlyWeight.h"

CFlyWeight::CFlyWeight()
{
	SetSize( 0.0f );
	SetMaxLife( 0.0f );

	SetMinVelocityX( 0.0f );
	SetMaxVelocityX( 0.0f );
	SetMinVelocityY( 0.0f );
	SetMaxVelocityY( 0.0f );

	SetSpawnAreaWidth( 0.0f );
	SetSpawnAreaHeight( 0.0f );
	SetMinSpawnRadius( 0.0f );
	SetMaxSpawnRadius( 0.0f );
	
	SetEmitterPositionX( 0.0f );
	SetEmitterPositionY( 0.0f );
	SetEmitterVelocityX( 0.0f );
	SetEmitterVelocityY( 0.0f );

	SetFadeValue( 0 );
	SetScaleValue( 0 );
	SetRotationValue( 0 );
	SetRedValue( 0 );
	SetGreenValue( 0 );
	SetBlueValue( 0 );

	SetFadeEffect( 0 );
	SetScaleEffect( 0 );
	SetRotationEffect( 0 );
	SetRedEffect( 0 );
	SetGreenEffect( 0 );
	SetBlueEffect( 0 );
	
	SetSpawnPattern( 0 );
	SetSource( 0 );
	SetDestination( 0 );
	SetMaxParticles( 0 );
	
	SetUseBlend( false );
}
CFlyWeight::~CFlyWeight(){}