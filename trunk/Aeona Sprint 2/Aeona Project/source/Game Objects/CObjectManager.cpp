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
	for(unsigned int i=0; i < m_vpObjectList.size(); ++i)
	{
		CBaseObject* pObj = (CBaseObject*)m_vpObjectList[i];

		double left = GetScreenPosX(pObj->GetCollisionRect().left);
		double right = GetScreenPosX(pObj->GetCollisionRect().right);
		double top = GetScreenPosY(pObj->GetCollisionRect().top);
		double bottom = GetScreenPosY(pObj->GetCollisionRect().bottom);

		// If object is inside the screen, update it
		if(right > 0 &&	left < GAME->GetScreenWidth() &&
			bottom > 0 && top < GAME->GetScreenHeight())
			pObj->Update(fElapsedTime);
		else if(pObj->GetType() == CBaseObject::TYPE_WEAPON_ARROW)
			CMessageSystem::GetInstance()->SendMsg(new CDestroyObjectMessage(pObj));

	}
}

void CObjectManager::InputFromObjects()
{
	for(unsigned int i = 0; i < m_vpObjectList.size(); ++i)
	{
		m_vpObjectList[i]->Input();
	}
}

void CObjectManager::RenderObjects()
{
	// -- NOTE FROM DANIEL TO BERN -- //
	// Yes, Bryan, I know that QuickSort was your user story,
	// but I was changing a lot of things in this class and I
	// ended up doing it... However, it's not really good yet.
	// The problem in here is that I create a render list and just
	// copy everything from object list into it, then I sort it,
	// then I render what's on screen. This means that if there
	// are 100 objects in the game, which is really possible,
	// all of them will be sorted, which is not good >.<
	// The "render list" vector should have only the objects
	// that are inside the screen, before the quick sort being
	// applied to it. If you can do this and decrease the
	// frame rate, I will let you check off this user story =P

	vector<IBaseInterface*> m_vpRenderList /*= m_vpObjectList*/;

	for(unsigned int i = 0; i < m_vpObjectList.size(); ++i)
	{
		CBaseObject* pObj = (CBaseObject*)m_vpObjectList[i];

		double left = GetScreenPosX(pObj->GetCollisionRect().left);
		double right = GetScreenPosX(pObj->GetCollisionRect().right);
		double top = GetScreenPosY(pObj->GetCollisionRect().top);
		double bottom = GetScreenPosY(pObj->GetCollisionRect().bottom);

		// If object is inside the screen, render it
		if(right > 0 &&	left < GAME->GetScreenWidth() && bottom > 0 && top < GAME->GetScreenHeight())
			m_vpRenderList.push_back(pObj);
	}
	
	//if(update == true)
	//{
		QuickSort(m_vpRenderList, 0, m_vpRenderList.size() - 1);
	//}
	//
	//update = !update;
	
	
	for(unsigned int i = 0; i < m_vpRenderList.size(); ++i)
	{
		m_vpRenderList[i]->Render();
	}

	//for(unsigned int i = 0; i < m_vpObjectList.size(); ++i)
	//{
	//	CBaseObject* pObj = (CBaseObject*)m_vpObjectList[i];
	//
	//	double left = GetScreenPosX(pObj->GetCollisionRect().left);
	//	double right = GetScreenPosX(pObj->GetCollisionRect().right);
	//	double top = GetScreenPosY(pObj->GetCollisionRect().top);
	//	double bottom = GetScreenPosY(pObj->GetCollisionRect().bottom);
	//
	//	// If object is inside the screen, render it
	//	if(right > 0 &&	left < GAME->GetScreenWidth() &&
	//		bottom > 0 && top < GAME->GetScreenHeight())
	//		m_vpObjectList[i]->Render();
	//}

}

void CObjectManager::QuickSort(vector<IBaseInterface*>& arr, int left, int right)
{
	int i = left, j = right;
	CBaseObject* tmp;
	CBaseObject* pivot = (CBaseObject*)arr[(left + right) / 2];

	while (i <= j)
	{
		while (((CBaseObject*)arr[i])->GetPosY() < ((CBaseObject*)pivot)->GetPosY())
			i++;
		while (((CBaseObject*)arr[j])->GetPosY() > ((CBaseObject*)pivot)->GetPosY())
			j--;
		if (i <= j)
		{
			tmp = (CBaseObject*)arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	};

	if (left < j)
		QuickSort(arr, left, j);
	if (i < right)
		QuickSort(arr, i, right);
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
		CBaseObject* pObj = (CBaseObject*)m_vpObjectList[i];

		// If the object is not active, check another one..
		if(pObj->IsActive() == false) continue;

		double left = GetScreenPosX(pObj->GetCollisionRect().left);
		double right = GetScreenPosX(pObj->GetCollisionRect().right);
		double top = GetScreenPosY(pObj->GetCollisionRect().top);
		double bottom = GetScreenPosY(pObj->GetCollisionRect().bottom);

		// If object is inside the screen, check collisions for it
		if(right > 0 &&	left < GAME->GetScreenWidth() &&
			bottom > 0 && top < GAME->GetScreenHeight())
		{
			if(pObj->GetType() != CBaseObject::TYPE_WEAPON_ARROW)
				WORLD->CheckCollisions(pObj);

			for(unsigned int j = 0; j < m_vpObjectList.size(); j++)
			{
				if(i != j)
				{
					CBaseObject* pSecObj = (CBaseObject*)m_vpObjectList[j];

					// If the object is not active, check another one..
					if(pSecObj->IsActive() == false) continue;

					left = GetScreenPosX(pSecObj->GetCollisionRect().left);
					right = GetScreenPosX(pSecObj->GetCollisionRect().right);
					top = GetScreenPosY(pSecObj->GetCollisionRect().top);
					bottom = GetScreenPosY(pSecObj->GetCollisionRect().bottom);

					// If object is inside the screen, check collisions for it
					if(right > 0 &&	left < GAME->GetScreenWidth() &&
						bottom > 0 && top < GAME->GetScreenHeight())
					{
						// Check Collision between object i and j
						if(pObj->CheckCollision(pSecObj))
						{
							continue;
						}
					}
				}
			}
		}

	}
}