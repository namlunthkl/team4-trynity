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
	float MinSpwnRadius;
	float MaxSpwnRadius;

	int FadeEffect;
	float FadeValue;

	int ScaleEffect;
	float ScaleValue;

	int RotationEffect;
	float RotationValue;

	int RedEffect;
	float RedValue;

	int GreenEffect;
	float GreenValue;

	int BlueEffect;
	float BlueValue;

	int SpwnPattern;
	int Source;
	int Dest;
	bool UseBlend;
	float EmitterPosX;
	float EmitterPosY;
	int MaxParticles;
	float EmitterVelX;
	float EmitterVelY;

	FlyWeight();
	~FlyWeight();

};
#endif