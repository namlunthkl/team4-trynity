////////////////////////////////////////////////////////////////////////
//    File Name    : "CParticleManager.h"
//
//    Author Name   : Ari Bodaghee
//    Creation Date   : 02/08/12 - 7:47 PM
//    Purpose    : Contains the CParticleManager
////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CParticleManager.h"


CParticleManager* CParticleManager::GetInstance(void)
{
	static CParticleManager instance;
	return &instance;
}
void CParticleManager::Draw(void)
{

}
void CParticleManager::Update( float fElapsedTime )
{

}
void CParticleManager::LoadEmitter( std::string sStringName )
{
}
void CParticleManager::UnLoadEmitter()
{

}
