#ifndef PARTICLEWEAPON_H_
#define PARTICLEWEAPON_H_

#include <vector>
#include "Emitter.h"
using namespace std;


class ParticleWeapon
{
	bool Fired;
public:	
	Emitter emitter;

	ParticleWeapon(void);
	~ParticleWeapon(void);

	bool GetFired(void)		{ return Fired; }
	void SetFired( bool f)	{ Fired = f; }

	void Fire();
	void Update(float DT);
	void Render();
	bool Load(const char* szXMLFileName);
};

#endif