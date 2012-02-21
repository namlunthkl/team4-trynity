#include "FlyWeight.h"

FlyWeight::FlyWeight()
{
	MaxParticles = 0;
	fSize = 0.0f;
	MaxLife  = 0.0f;
	MinVelX = 0.0f;
	MaxVelX = 0.0f;
	MinVelY = 0.0f;
	MaxVelY = 0.0f;
	SpwnAreaWidth = 0.0f;
	SpwnAreaHeight = 0.0f;

	FadeEffect = 0;
	FadeValue = 0.0f;

	ScaleEffect = 0;
	ScaleValue = 0.0f;

	RotationValue = 0.0f;

	RedEffect = 0;
	RedValue = 0.0f;

	GreenEffect = 0;
	GreenValue = 0.0f;

	BlueEffect = 0;
	BlueValue = 0.0f;

	Source = 0;
	Dest = 0;
	
	EmitterPosX = 0.0f;
	EmitterPosY = 0.0f;
	EmitterVelX = 0.0f;
	EmitterVelY = 0.0f;
}

FlyWeight::~FlyWeight(){}