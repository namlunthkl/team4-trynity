////////////////////////////////////////////////////////////////////////
//    File Name				:	"CObjectManager.cpp"
//
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the ObjectManager
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CObjectManager.h"
void CObjectManager::DeleteInstance()
{

}
void CObjectManager::UpdateObjects(float fElapsedTime)
{

}
void CObjectManager::RenderObjects()
{

}
bool CObjectManager::AddObject(IBaseInterface* pObject)
{
	return true;
}
bool CObjectManager::RemoveObject(IBaseInterface* pObject)
{
	return true;
}
void CObjectManager::RemoveAllObjects()
{

}
void CObjectManager::CheckCollisions()
{

}
CObjectManager* CObjectManager::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new CObjectManager;
	}

	return this->m_pInstance;
}