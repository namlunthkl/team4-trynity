#include "StdAfx.h"

#include "CFinalTorchPuzzleThatBernWantedButDanielMade.h"
#include "../Game Objects/CPlayer.h"
#include "../Light System/LightEngine.h"
#include "../Camera/CCameraControl.h"

void CFinalTorchPuzzleThatBernWantedButDanielMade::Create(unsigned int uiArgCount, char* szEventToFire, char* szEventToListenTo, bool bSequential)
{
	torchPositions[0].x = 1272;
	torchPositions[0].y = 1264;
	torchPositions[1].x = 1718;
	torchPositions[1].y = 1264;
	torchPositions[2].x = 1272;
	torchPositions[2].y = 1644;
	torchPositions[3].x = 1718;
	torchPositions[3].y = 1644;

	CTorchPuzzle::Create(uiArgCount, szEventToFire, szEventToListenTo, bSequential);
}

void CFinalTorchPuzzleThatBernWantedButDanielMade::EventReceived(int ArgumentNumber, void* EventData)
{
	IBasePuzzle::EventReceived(ArgumentNumber, EventData);

	double PosX = torchPositions[ArgumentNumber].x;
	double PosY = torchPositions[ArgumentNumber].y;

	if(m_vnArguments[ArgumentNumber] == 1)
	{
		m_vParticle[ArgumentNumber]->emitter.EmitterPosX = (float)PosX;
		m_vParticle[ArgumentNumber]->emitter.EmitterPosY = (float)PosY;

		m_vParticle[ArgumentNumber]->Fire();
	}
	switch(ArgumentNumber)
	{
	case 0:
		// This is hit when the first torch (top left) is lit or unlit
		LightEngine::GetInstance()->SetItem1PointPos(m_vParticle[0]->emitter.EmitterPosX, m_vParticle[ArgumentNumber]->emitter.EmitterPosY);
		LightEngine::GetInstance()->SetItem1PointLight(m_vnArguments[0] == 1 ? true : false);
		break;
	case 1:
		LightEngine::GetInstance()->SetItem2PointPos(m_vParticle[1]->emitter.EmitterPosX, m_vParticle[ArgumentNumber]->emitter.EmitterPosY);
		LightEngine::GetInstance()->SetItem2PointLight(m_vnArguments[1] == 1 ? true : false);
		break;
	case 2:
		LightEngine::GetInstance()->SetItem3PointPos(m_vParticle[2]->emitter.EmitterPosX, m_vParticle[ArgumentNumber]->emitter.EmitterPosY);
		LightEngine::GetInstance()->SetItem3PointLight(m_vnArguments[2] == 1 ? true : false);
		break;
	case 3:
		LightEngine::GetInstance()->SetItem4PointPos(m_vParticle[3]->emitter.EmitterPosX, m_vParticle[ArgumentNumber]->emitter.EmitterPosY);
		LightEngine::GetInstance()->SetItem4PointLight(m_vnArguments[3] == 1 ? true : false);
		break;
	};

	// Get the distance between this tile and the player
	if(GetNumberOfArgumentsOn() == 0)
		m_bPlaySound = false;
	else
		m_bPlaySound = true;
}