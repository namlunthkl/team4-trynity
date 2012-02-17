#ifndef _Particle_h_
#define _Particle_h_


class Particle
{
public:
	float A;
	float R;
	float G;
	float B;

	float PosX;
	float PosY;

	float VelX;
	float VelY;

	float Size_p;
	float Rotation;

	float Life;

	Particle();
	~Particle();
	void Update(float DT);

};
#endif