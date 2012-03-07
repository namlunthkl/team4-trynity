#include "StdAfx.h"
#include "CTorchPuzzle.h"
#include "../Game Objects/CPlayer.h"
#include "../Light System/LightEngine.h"

void CTorchPuzzle::Create(unsigned int uiArgCount, char* szEventToFire, char* szEventToListenTo, bool bSequential)
{
	IBasePuzzle::Create(uiArgCount, szEventToFire, szEventToListenTo, bSequential);

	for(unsigned int i=0; i < uiArgCount; ++i)
	{
		ParticleWeapon* p = new ParticleWeapon();
		p->Load("resource/data/FireFlicker.xml");
		m_vParticle.push_back(p);
	}

	m_sndFireSound = AUDIO->SFXLoadSound("resource/sound/Fire.wav");
	m_bPlaySound = false;
}

void CTorchPuzzle::Update(float fElapsedTime)
{
	for(unsigned int i=0; i < m_vParticle.size(); ++i)
		if(m_vnArguments[i] == 1)
			m_vParticle[i]->Update(fElapsedTime);

	double dDistance = CPlayer::GetInstance()->GetPosition().GetDistanceUntil(m_ptLastLitTorchPosition);
	if(m_bPlaySound)
	{
		if(dDistance < 400 && AUDIO->SFXIsSoundPlaying(m_sndFireSound) == false)
			AUDIO->SFXPlaySound(m_sndFireSound, true);
		else if(dDistance >= 400)
			AUDIO->SFXStopSound(m_sndFireSound);
	}
	else if(AUDIO->SFXIsSoundPlaying(m_sndFireSound))
	{
		AUDIO->SFXStopSound(m_sndFireSound);
	}

}

void CTorchPuzzle::EventReceived(int ArgumentNumber, void* EventData)
{
	IBasePuzzle::EventReceived(ArgumentNumber, EventData);

	CMap::TileInfo* eventInfo = (CMap::TileInfo*)EventData;
	unsigned char cTileWidth = eventInfo->Map->GetTileset()->GetTileWidth();
	unsigned char cTileHeight = eventInfo->Map->GetTileset()->GetTileHeight();

	double PosX = eventInfo->Map->GetPosX() + cTileWidth * eventInfo->sMapPosX - 5;//- cTileWidth/2;
	double PosY = eventInfo->Map->GetPosY() + cTileHeight * eventInfo->sMapPosY - cTileHeight/2;
	m_ptLastLitTorchPosition = PointD(PosX, PosY);

	if(m_vnArguments[ArgumentNumber] == 1)
	{
		m_vParticle[ArgumentNumber]->emitter.EmitterPosX = (float)PosX;
		m_vParticle[ArgumentNumber]->emitter.EmitterPosY = (float)PosY;

		m_vParticle[ArgumentNumber]->Fire();
	}

	// Get the distance between this tile and the player
	if(GetNumberOfArgumentsOn() == 0)
		m_bPlaySound = false;
	else
		m_bPlaySound = true;
}

void CTorchPuzzle::Render(void)
{
	for(unsigned int i=0; i < m_vParticle.size(); ++i)
		if(m_vnArguments[i] == 1)
			m_vParticle[i]->Render();
}

void CTorchPuzzle::Destroy(void)
{
	for(unsigned int i=0; i < m_vParticle.size(); ++i)
		delete m_vParticle[i];

	m_vParticle.clear();

	AUDIO->SFXStopSound(m_sndFireSound);
	AUDIO->SFXUnloadSound(m_sndFireSound);

	IBasePuzzle::Destroy();
}