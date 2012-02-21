#ifndef _FlyWeight_h_
#define _FlyWeight_h_

class FlyWeight
{

public:
	float fSize;
	float MaxLife;
	float MinVelX;
	float MaxVelX;
	float MinVelY;
	float MaxVelY;
	float SpwnAreaWidth;
	float SpwnAreaHeight;
	
	float RotationValue;
	
	int FadeEffect;
	float FadeValue;

	
	

	int RedEffect;
	float RedValue;

	int GreenEffect;
	float GreenValue;

	int BlueEffect;
	float BlueValue;

	int ScaleEffect;
	float ScaleValue;

	int Source;
	int Dest;

	float EmitterPosX;
	float EmitterPosY;
	int MaxParticles;
	float EmitterVelX;
	float EmitterVelY;

	FlyWeight();
	~FlyWeight();

};
#endif