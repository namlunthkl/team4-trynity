#include "StdAfx.h"
#include "CTorchPuzzle.h"

void CTorchPuzzle::Create(unsigned int uiArgCount, char* szEventToFire, char* szEventToListenTo, bool bSequential)
{
	IBasePuzzle::Create(uiArgCount, szEventToFire, szEventToListenTo, bSequential);

	for(unsigned int i=0; i < uiArgCount; ++i)
	{
		ParticleWeapon* p = new ParticleWeapon();
		p->Load("resource/data/FireFlicker.xml");
		m_vParticle.push_back(p);
	}
}

void CTorchPuzzle::Update(float fElapsedTime)
{
	for(unsigned int i=0; i < m_vParticle.size(); ++i)
		if(m_vnArguments[i] == 1)
			m_vParticle[i]->Update(fElapsedTime);
}

void CTorchPuzzle::EventReceived(int ArgumentNumber, void* EventData)
{
	IBasePuzzle::EventReceived(ArgumentNumber, EventData);

	if(m_vnArguments[ArgumentNumber] == 1)
	{
		CMap::TileInfo* eventInfo = (CMap::TileInfo*)EventData;
		int PosX = eventInfo->Map->GetPosX() + eventInfo->Map->GetTileset()->GetTileWidth() * eventInfo->sMapPosX;
		int PosY = eventInfo->Map->GetPosY() + eventInfo->Map->GetTileset()->GetTileHeight() * eventInfo->sMapPosY;

		m_vParticle[ArgumentNumber]->emitter.EmitterPosX = (float)PosX - 6;
		m_vParticle[ArgumentNumber]->emitter.EmitterPosY = (float)PosY - 36;

		m_vParticle[ArgumentNumber]->Fire();
	}
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

	IBasePuzzle::Destroy();
}