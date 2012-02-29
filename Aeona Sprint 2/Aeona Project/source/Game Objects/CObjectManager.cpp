////////////////////////////////////////////////////////////////////////
//    File Name				:	"CObjectManager.cpp"
//
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the ObjectManager
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CObjectManager.h"

#include "CBaseObject.h"
#include "../Tile Mapping/CWorldEngine.h"
#include "../States/CGameplayState.h"

CObjectManager* CObjectManager::sm_pInstance = nullptr;

CObjectManager* CObjectManager::GetInstance()
{
	if(sm_pInstance == NULL)
	{
		sm_pInstance = new CObjectManager;
	}
	return sm_pInstance;
}

void CObjectManager::DeleteInstance()
{
	if(sm_pInstance)
	{
		delete sm_pInstance;
		sm_pInstance = NULL;
	}
}

void CObjectManager::UpdateObjects(float fElapsedTime)
{
	vector<IBaseInterface*>::iterator iter = m_vpObjectList.begin();

	while(iter != m_vpObjectList.end())
	{
		(*iter)->Update(fElapsedTime);
		iter++;
	}
}

void CObjectManager::RenderObjects()
{
	for(unsigned int i = 0; i < m_vpObjectList.size(); ++i)
	{
		m_vpObjectList[i]->Render();
	}
}

bool CObjectManager::AddObject(IBaseInterface* pObject)
{
	//	Check for valid object pointer
	if(pObject == NULL)
	{
		return false;
	}
	//	Add object to the object list
	m_vpObjectList.push_back(pObject);
	//	Add my reference to it.
	pObject->AddRef();

	return true;
}

bool CObjectManager::RemoveObject(IBaseInterface* pObject)
{
	//	Check for valid object pointer
	if(pObject == NULL)
	{
		return false;
	}

	for (vector<IBaseInterface*>::iterator iter = m_vpObjectList.begin(); iter != m_vpObjectList.end(); ++iter)
	{
		//	Check if this is the right object
		if((*iter) == pObject)
		{
			//	Remove this object's reference
			(*iter)->Release();

			//	And then remove it from the list
			iter = m_vpObjectList.erase(iter);
			break;
		}
	}
	return true;
}

void CObjectManager::RemoveAllObjects()
{
	//	Call Release() on all objects
	for(unsigned int i = 0; i < m_vpObjectList.size(); ++i)
	{
		m_vpObjectList[i]->Release();
	}
	//	Collapse the vector
	m_vpObjectList.clear();
}

void CObjectManager::CheckCollisions()
{
	// Loop through all the objects and check collisions in all of them
	for(unsigned int i = 0; i < m_vpObjectList.size(); i++)
	 {
		 for(unsigned int j = 0; j < m_vpObjectList.size(); j++)
		 {
			 if(i != j)
			 {
				 // Check Collision between object i and j
				 if(((CBaseObject*)m_vpObjectList[i])->IsActive() && ((CBaseObject*)m_vpObjectList[j])->IsActive())
				 {
					 if(m_vpObjectList[i]->CheckCollision(m_vpObjectList[j]))
					 {
						 // If object i collided with object j stop checking
						 // object i and go on to the next object i
						 continue;
					 }
				 }
			 }
		 }

		 WORLD->CheckCollisions(m_vpObjectList[i]);

	 }

}