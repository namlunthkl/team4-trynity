#ifndef EMITTER_H_
#define EMITTER_H_

#include <vector>
#include <string>
#include "CBase.h"
using namespace std;

#include "AB_Particle.h"
#include "AB_FlyWeight.h"

class CEmitter  : public CBase
{
public:
	vector< CParticle* >	m_pParticle_List;
	CFlyWeight*				m_pData;
	bool					m_bContinuous;
	bool					m_bLocked;
	CBase*					m_pTarget;
	int						m_nImage;
	string					m_sImageFile;

	CEmitter();
	CEmitter( const CEmitter& e );
	CEmitter& operator=( const CEmitter& e );
	~CEmitter();

	void Init( void );
	void Update( float deltaTime );
	void Render( void );
	void ReSpawn( CParticle* p );
	void LockonOBJ(CBase* OBJ);
};
#endif