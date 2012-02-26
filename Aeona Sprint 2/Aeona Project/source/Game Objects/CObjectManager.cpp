////////////////////////////////////////////////////////////////////////
//    File Name				:	"CObjectManager.cpp"
//
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the ObjectManager
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CObjectManager.h"

CObjectManager* CObjectManager::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new CObjectManager;
	}
	return m_pInstance;
}

void CObjectManager::DeleteInstance()
{
	if(m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
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
}