////////////////////////////////////////////////////////////////////////
//    File Name    : "CParticleManager.h"
//
//    Author Name   : Ari Bodaghee
//    Creation Date   : 02/08/12 - 7:47 PM
//    Purpose    : Contains the CParticleManager
////////////////////////////////////////////////////////////////////////
#ifndef CPARTICLEMANAGER_H_
#define CPARTICLEMANAGER_H_

#include <vector>
#include "CParticleEmitter.h"

class CParticleManager
{
private:
	std::vector<CParticleEmitter> m_ListOfEmitters;

	CParticleManager(void){}
	CParticleManager( const CParticleManager& );
	CParticleManager& operator=( const CParticleManager& );
	~CParticleManager(void){}

public:
	//TODO: GETs and Sets
	static CParticleManager* GetInstance( void );

	void Draw(void);
	void Update( float fElapsedTime );
	void LoadEmitter( std::string sStringName );
	void UnLoadEmitter();

};

#endif