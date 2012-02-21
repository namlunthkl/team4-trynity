#pragma once

#include <vector>
#include "Emitter.h"
using namespace std;


class ParticleWeapon
{
	bool Fired;
	vector<Emitter*> Emitters;

public:
	ParticleWeapon(void);
	~ParticleWeapon(void);

	void Fire(int PosX , int PosY );
	void Update(float DT);
	void Render();
	bool Load(const char* szXMLFileName);

	inline bool GetFired(void) const { return Fired; }
};

