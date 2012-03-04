#include "StdAfx.h"
#include "Emitter.h"
#include "..\CGame.h"
#include "..\Wrappers\SGD_Math.h"



Emitter::Emitter()
{
	Image = -1;
	ColorStartA = 255;
	ColorStartR = 255;
	ColorStartG = 255;
	ColorStartB = 255;
	ColorEndA   = 255;
	ColorEndR   = 255;
	ColorEndG   = 255;
	ColorEndB   = 255;
	fSize = 0.0f;
	MaxParticles = 0;
	MaxLife = 0.0f;
	MinVelX = 0.0f;
	MaxVelX = 0.0f;
	MinVelY = 0.0f;
	MaxVelY = 0.0f;
	SpawnWidth = 0.0f;
	SpawnHeight = 0.0f;
	ScaleStart = 0.0f;
	ScaleEnd = 0.0f;
	Rotation = 0.0f;
	Source = 0;
	Destination = 0;
	EmitterPosX = 0.0f;
	EmitterPosY = 0.0f;

	Continuous = true;
	reAnimate = false;

	GravityPosX = 0.0f;
	GravityPosY = 0.0f;
	GravityPower = 0.0f;
	GravityDistX = 0.0f;
	GravityDistY = 0.0f;
}
Emitter::Emitter(const Emitter& E)
{
	for(unsigned int i = 0; i < E.Particle_List.size(); i++)
		Particle_List.push_back(E.Particle_List[i]);
}
Emitter& Emitter::operator=(const Emitter& E)
{
	if(this == &E)
		return *this;
	else
		*this = E;

	return *this;
}
Emitter::~Emitter()
{
	ShutDown();
}

void Emitter::Init()
{
	Particle* tempParticle;

	for (int i = 0; i < MaxParticles; i++)
	{
		tempParticle = new Particle();
		tempParticle->Life = -1;
		Particle_List.push_back(tempParticle);
	}
}
void Emitter::Update( float DT )
{
	for( int i = 0; i < MaxParticles; ++i )
	{
		Particle_List[i]->Rotation += Rotation * DT;
		Particle_List[i]->Life -= DT;

		Particle_List[i]->A = (int)(Lerp( (float)ColorStartA, (float)ColorEndA, ( Particle_List[i]->curLife - Particle_List[i]->Life ) / Particle_List[i]->curLife ));
		Particle_List[i]->R = (int)(Lerp( (float)ColorStartR, (float)ColorEndR, ( Particle_List[i]->curLife - Particle_List[i]->Life ) / Particle_List[i]->curLife )); 
		Particle_List[i]->G = (int)(Lerp( (float)ColorStartG, (float)ColorEndG, ( Particle_List[i]->curLife - Particle_List[i]->Life ) / Particle_List[i]->curLife ));
		Particle_List[i]->B = (int)(Lerp( (float)ColorStartB, (float)ColorEndB, ( Particle_List[i]->curLife - Particle_List[i]->Life ) / Particle_List[i]->curLife ));
		fSize = Lerp( ScaleStart, ScaleEnd, ( Particle_List[i]->curLife - Particle_List[i]->Life ) / Particle_List[i]->curLife );
		Particle_List[i]->Size_p = fSize;

		GravityDistX = GravityPosX - Particle_List[i]->PosX;
		GravityDistY = GravityPosY - Particle_List[i]->PosY;

		float length;
		length = sqrt( ( GravityDistX * GravityDistX ) + ( GravityDistY * GravityDistY ) );

		GravityDistX = GravityDistX / length;
		GravityDistY = GravityDistY / length;

		GravityDistX *= GravityPower;
		GravityDistY *= GravityPower;

		Particle_List[i]->PosX += Particle_List[i]->VelX * DT;
		Particle_List[i]->PosY += Particle_List[i]->VelY * DT;

		Particle_List[i]->VelX += GravityDistX;
		Particle_List[i]->VelY += GravityDistY;

		if( Particle_List[i]->Life < 0 && Continuous )
		{
			ReSpwn( Particle_List[i] );
		}
		if( Particle_List[i]->Life < 0 && reAnimate == true && Continuous != true )
		{
			ReSpwn( Particle_List[i] );

			if( i >= MaxParticles - 1 )
			{
				reAnimate = false;
			}
		}
	}
}
void Emitter::ReSpwn(Particle* P)
{
	P->Life = RandomFloat( 0.0f, MaxLife );
	P->curLife = P->Life;
	P->Size_p = ScaleStart;

	P->Rotation = Rotation;

	P->VelX = RandomFloat( MinVelX , MaxVelX );
	P->VelY = RandomFloat( MinVelY , MaxVelY );

	P->PosX = RandomFloat( EmitterPosX, ( EmitterPosX + SpawnWidth ) );
	P->PosY = RandomFloat( EmitterPosY, ( EmitterPosY + SpawnHeight) );
}
void Emitter::Render()
{
	DWORD tempBlends[2] = {0};
	CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->GetRenderState(D3DRS_SRCBLEND, &tempBlends[0]);
	CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->GetRenderState(D3DRS_DESTBLEND, &tempBlends[1]);

	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();

	CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->SetRenderState(D3DRS_SRCBLEND, Source);
	CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->SetRenderState(D3DRS_DESTBLEND, Destination);

	for (unsigned int i = 0; i < Particle_List.size(); i++ )
	{
		if ( Particle_List[i]->Life > 0)
		{
			if( Image != -1 )
			{
				int OffSetX = (int)((int)(CSGD_TextureManager::GetInstance()->GetTextureWidth( Image ) >> 1 ) * Particle_List[i]->Size_p );
				int OffSetY = (int)((int)(CSGD_TextureManager::GetInstance()->GetTextureHeight( Image ) >> 1 ) * Particle_List[i]->Size_p );

				CSGD_TextureManager::GetInstance()->Draw( Image, (int)Particle_List[i]->PosX,
					(int)Particle_List[i]->PosY, Particle_List[i]->Size_p, Particle_List[i]->Size_p, NULL, (float)OffSetX, (float)OffSetY,
					Particle_List[i]->Rotation, 
					D3DCOLOR_ARGB( Particle_List[i]->A, Particle_List[i]->R, Particle_List[i]->G, Particle_List[i]->B ) );
			}
		}
	}
	CSGD_Direct3D::GetInstance()->GetSprite()->Flush();
	CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->SetRenderState(D3DRS_SRCBLEND, tempBlends[0]);
	CSGD_Direct3D::GetInstance()->GetDirect3DDevice()->SetRenderState(D3DRS_DESTBLEND, tempBlends[1]);
}
void Emitter::ShutDown(void)
{
	for(unsigned int i = 0; i < Particle_List.size(); i++)
		delete (Particle*)(Particle_List[i]);

	Particle_List.clear();

	MaxParticles = 0;
}