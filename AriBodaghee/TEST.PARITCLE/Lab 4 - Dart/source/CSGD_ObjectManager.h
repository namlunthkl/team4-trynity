////////////////////////////////////////////////
//	File	:	"CSGD_ObjectManager.h"
//
//	Author	:	David Brown (DB)
//
//	Purpose	:	To contain and manage all of our game objects.
/////////////////////////////////////////////////
#pragma once
#include <vector>
using std::vector;

#include "IBaseInterface.h"

class CSGD_ObjectManager
{
private:
	vector<IBaseInterface*> m_vObjectList;
	
	static CSGD_ObjectManager* sm_Instance;
	
	CSGD_ObjectManager(void) {}
	~CSGD_ObjectManager(void) {}
	CSGD_ObjectManager(const CSGD_ObjectManager&);
	CSGD_ObjectManager& operator=(const CSGD_ObjectManager&);

public:
	
	static CSGD_ObjectManager* GetInstance(void);
	static void DeleteInstance(void);

	void UpdateObjects(float fElapsedTime);
	void RenderObjects(void);

	void AddObject(IBaseInterface* pObject);
	void RemoveObject(IBaseInterface* pObject);

	void RemoveAllObjects(void);

	void CheckCollisions(void);

};