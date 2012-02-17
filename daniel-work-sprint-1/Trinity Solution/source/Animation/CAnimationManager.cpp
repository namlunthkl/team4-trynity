////////////////////////////////////////////////////////////////////////
//    File Name				:	"CAnimationManager.cpp"
//
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the Animation Manager
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CAnimationManager.h"
CAnimationManager* CAnimationManager::GetInstance()
{
	// Lazy instantiation
	static CAnimationManager instance;
	return &instance;
}

bool CAnimationManager::UnloadAnimation(int nAnimation)
{
	return true;
}

int CAnimationManager::LoadAnimation()
{
	return 0;
}

bool CAnimationManager::UnloadAll()
{
	return true;
}