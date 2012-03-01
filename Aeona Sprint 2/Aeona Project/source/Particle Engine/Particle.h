#ifndef _Particle_h_
#define _Particle_h_

class Particle
{
public:
	int A;
	int R;
	int G;
	int B;

	float PosX;
	float PosY;

	float VelX;
	float VelY;

	float Size_p;
	float Rotation;

	float Life;
	float curLife;

	Particle(){}
	~Particle(){}
};
#endif