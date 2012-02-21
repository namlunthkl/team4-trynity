////////////////////////////////////////////////////////////////////////
//    File Name				:	"CObjectManager.h"
//
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the ObjectManager
////////////////////////////////////////////////////////////////////////
#ifndef _COBJECTMANAGER_H_
#define _COBJECTMANAGER_H_

#include "IBaseInterface.h"

class CObjectManager
{
private:
	CObjectManager* m_pInstance;
	vector<IBaseInterface*> m_vpObjectList;

public:
	CObjectManager(void) {}
	~CObjectManager(void) {}

	//	Instance
	CObjectManager* GetInstance();
	void DeleteInstance();

	void UpdateObjects(float fElapsedTime);
	void RenderObjects();

	bool AddObject(IBaseInterface* pObject);
	bool RemoveObject(IBaseInterface* pObject);
	void RemoveAllObjects();
	void CheckCollisions();
};

#endif