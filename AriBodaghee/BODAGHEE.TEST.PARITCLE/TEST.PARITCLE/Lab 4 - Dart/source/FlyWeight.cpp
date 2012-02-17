#include "FlyWeight.h"

FlyWeight::FlyWeight()
{
	fSize = 0.0f;
	MaxLife  = 0.0f;
	MinVelX = 0.0f;
	MaxVelX = 0.0f;
	MinVelY = 0.0f;
	MaxVelY = 0.0f;
	SpwnAreaWidth = 0.0f;
	SpwnAreaHeight = 0.0f;
	MinSpwnRadius = 0.0f;
	MaxSpwnRadius = 0.0f;

	FadeEffect = 0;
	FadeValue = 0.0f;

	ScaleEffect = 0;
	ScaleValue = 0.0f;

	RotationEffect = 0;
	RotationValue = 0.0f;

	RedEffect = 0;
	RedValue = 0.0f;

	GreenEffect = 0;
	GreenValue = 0.0f;

	BlueEffect = 0;
	BlueValue = 0.0f;

	SpwnPattern = 0;
	Source = 0;
	Dest = 0;
	UseBlend = false;
	EmitterPosX = 0.0f;
	EmitterPosY = 0.0f;
	MaxParticles = 0;
	EmitterVelX = 0.0f;
	EmitterVelY = 0.0f;
}

FlyWeight::~FlyWeight()
{
}