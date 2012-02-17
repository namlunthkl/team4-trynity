////////////////////////////////////////////////////////////////////////
//    File Name    : "CParticleEmitter.h"
//
//    Author Name   : Ari Bodaghee
//    Creation Date   : 02/08/12 - 7:47 PM
//    Purpose    : Contains the CParticleEmitter
////////////////////////////////////////////////////////////////////////
#ifndef CPARTICLEEMITTER_H_
#define CPARTICLEEMITTER_H_

#include <vector>
#include "CParticle.h"

class CParticleEmitter
{
private:
	int m_nImageID;
	int m_nMinDuration;
	int m_nMaxDuration;
	int m_nMaxParticles;
	int m_nStartColor;
	int m_nEndColor;
	int m_nStartScale;
	int m_nEndScale;
	int m_nSpawnRate;
	int m_nzValue;
	float m_fPositionX;
	float m_fPositionY;
	float m_fStartVelocity;
	float m_fEndVelocity;
	float m_fStartRotation;
	float m_fEndRotation;
	float m_fGravity;
	float m_fAcceleration;
	float m_fPointX;
	float m_fPointY;

	//D3DRenderState m_D3DSourceBlend;
	//D3DRenderState m_D3DDestinationBlend;

	std::vector<CParticle> m_LiveParticleList;
	std::vector<CParticle> m_DeadParticleList;
public:
	CParticleEmitter(void){}
	~CParticleEmitter(void){}
	//TODO: GETs and Sets
	void Reset();
	void Shape();
};

#endif