#ifndef _Emitter_h_
#define _Emitter_h_
#include <string>
#include <vector>
using namespace std;

#include "Particle.h"
#include "FlyWeight.h"

class Emitter
{
public:
	 vector<Particle*> Particle_List;
	 FlyWeight* Data;   
	 bool Continuous;
	 bool reAnimate;


	 int Image;
	 string ImageFile;

	 Emitter();

	//		Trilogy of EVIL!:
	//			Copy constructor
	Emitter(const Emitter& E);

	//			Assignment operator
	Emitter& operator=(const Emitter& E);
	
	//			~Destructor
	~Emitter(void);

	 void Init();
	 void Update( float DT );
	 void Render();
	 void ReSpwn(Particle* P);

};
#endif