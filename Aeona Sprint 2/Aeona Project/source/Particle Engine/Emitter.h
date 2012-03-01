#ifndef _Emitter_h_
#define _Emitter_h_
#include <string>
#include <vector>
using namespace std;
#include "Particle.h"


class Emitter
{
public:
	vector<Particle*> Particle_List;   
	bool Continuous;
	bool reAnimate;

	int Image;
	string ImageFile;

	int ColorStartA;
	int ColorStartR;
	int ColorStartG;
	int ColorStartB;
	int ColorEndA;
	int ColorEndR;
	int ColorEndG;
	int ColorEndB;

	float fSize;
	float MaxLife;

	float MinVelX;
	float MaxVelX;
	float MinVelY;
	float MaxVelY;
	float SpawnWidth;
	float SpawnHeight;

	float ScaleStart;
	float ScaleEnd;
	float Rotation;

	int Source;
	int Destination;

	float EmitterPosX;
	float EmitterPosY;
	int MaxParticles;

	float GravityPosX;
	float GravityPosY;
	float GravityPower;
	float GravityDistX;
	float GravityDistY;

	Emitter();
	Emitter(const Emitter& E);
	Emitter& operator=(const Emitter& E);
	~Emitter(void);

	void Init();
	void Update( float DT );
	void Render();
	void ReSpwn(Particle* P);

};
#endif