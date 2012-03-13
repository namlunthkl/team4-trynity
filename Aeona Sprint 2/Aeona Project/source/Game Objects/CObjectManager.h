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
	static CObjectManager* sm_pInstance;
	vector<IBaseInterface*> m_vpObjectList;
	bool update;
public:
	CObjectManager(void) {}
	~CObjectManager(void) {}

	void QuickSort(vector<IBaseInterface*>& arr, int left, int right);

	//	Instance
	static CObjectManager* GetInstance();
	static void DeleteInstance();

	void UpdateObjects(float fElapsedTime);
	void RenderObjects();
	void InputFromObjects();

	bool AddObject(IBaseInterface* pObject);
	bool RemoveObject(IBaseInterface* pObject);
	void RemoveAllObjects();
	void CheckCollisions();
};

#endif