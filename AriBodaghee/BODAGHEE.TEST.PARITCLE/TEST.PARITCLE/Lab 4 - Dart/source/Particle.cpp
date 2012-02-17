#include "Particle.h"

Particle::Particle()
{
}

Particle::~Particle()
{
}

void Particle::Update( float DT )
{
	PosX += VelX * DT;
	PosY += VelY * DT;
	Life -= 10000 * DT;

	if (A < 0)
		A = 0;
	else if (A > 255)
		A = 255;

	if (R < 0)
		R = 0;
	else if (R > 255)
		R = 255;

	if (G < 0)
		G = 0;
	else if (G > 255)
		G = 255;

	if (B < 0)
		B = 0;
	else if (B > 255)
		B = 255;
}