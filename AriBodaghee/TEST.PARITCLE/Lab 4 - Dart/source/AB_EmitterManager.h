#ifndef EMITTERMANAGER_H_
#define EMITTERMANAGER_H_

#include <vector>
#include <string>
#include "tinyxml\tinystr.h"
#include "tinyxml\tinyxml.h"
#include "AB_Emitter.h"

class EmitterManager
{
private:
	vector<CEmitter*> m_vEmitterList;

	static EmitterManager* instance;

	EmitterManager(void);
	~EmitterManager(void);
public:
	static EmitterManager* GetInstance(void);
	void DeleteInstance(void);

	void UpdateEmitter(float fElapsedTime);
	void RenderEmitter();

	void AddEmitter(CEmitter* pEmitter);

	CEmitter* GetEmitter(int i)
	{
		if(i < (int)m_vEmitterList.size())
			return m_vEmitterList[i];
	}

	void RemoveEmitter(CEmitter* pEmitter);
	void RemoveAllEmitters(void);

	bool Load(const char* szXMLFileName);
};

#endif