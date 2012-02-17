////////////////////////////////////////////////
//	File	:	"CSGD_ObjectManager.cpp"
//
//	Author	:	David Brown (DB)
//
//	Purpose	:	To contain and manage all of our game objects.
/////////////////////////////////////////////////
#include "CSGD_ObjectManager.h"

CSGD_ObjectManager* CSGD_ObjectManager::sm_Instance = NULL;

void CSGD_ObjectManager::UpdateObjects(float fElapsedTime)
{
	vector<IBaseInterface*>::iterator iter = m_vObjectList.begin();

	while(iter != m_vObjectList.end())
	{
		(*iter)->Update(fElapsedTime);
		iter++;
	}
}
void CSGD_ObjectManager::RenderObjects(void)
{
	for (unsigned int i=0; i < m_vObjectList.size(); i++)
		m_vObjectList[i]->Render();
}
void CSGD_ObjectManager::AddObject(IBaseInterface* pObject)
{
	//	Check for valid object pointer
	if (pObject == NULL)
		return;

	//	Add object to object list
	m_vObjectList.push_back(pObject);

	//	Add my reference to it.
	pObject->AddRef();
}
void CSGD_ObjectManager::RemoveObject(IBaseInterface* pObject)
{
	//	Check for valid object pointer
	if (pObject == NULL)
		return;

	for (vector<IBaseInterface*>::iterator iter = m_vObjectList.begin();
		iter != m_vObjectList.end();
		iter++)
	{
		// if this is the object we are looking for.
		if ((*iter) == pObject)
		{
			// Remove my reference to this object.
			(*iter)->Release();

			// Remove the object from the list
			iter = m_vObjectList.erase(iter);
			break;
		}
	}
}
void CSGD_ObjectManager::RemoveAllObjects(void)
{
	//	Call Release() on all objects.
	for (unsigned int i=0; i < m_vObjectList.size(); i++)
	{
		m_vObjectList[i]->Release();
	}

	//	Collapse the vector
	m_vObjectList.clear();
}
CSGD_ObjectManager* CSGD_ObjectManager::GetInstance( void )
{
	if(!sm_Instance)
	{
		sm_Instance = new CSGD_ObjectManager();
	}

	return sm_Instance;
}
void CSGD_ObjectManager::DeleteInstance( void )
{
	if( sm_Instance )
	{
		delete sm_Instance;
		sm_Instance = NULL;
	}
}
void CSGD_ObjectManager::CheckCollisions( void )
{
	for (unsigned int i=0; i < m_vObjectList.size(); i++)
	{
		for (unsigned int j = 0; j < m_vObjectList.size(); j++)
		{	
			if(m_vObjectList[i]->GetType() == m_vObjectList[j]->GetType())
			{
				continue;
			}

			if(m_vObjectList[i]->GetType() != m_vObjectList[j]->GetType())
			{
				if(m_vObjectList[i]->CheckCollision(m_vObjectList[j]))
				{
					break;
				}
			}
		}
	}
}