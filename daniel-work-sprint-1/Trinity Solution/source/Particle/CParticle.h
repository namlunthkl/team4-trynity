////////////////////////////////////////////////////////////////////////
//    File Name    : "CParticle.h"
//
//    Author Name   : Ari Bodaghee
//    Creation Date   : 02/08/12 - 7:47 PM
//    Purpose    : Contains the CParticle
////////////////////////////////////////////////////////////////////////


#ifndef CPARTICLE_H_
#define CPARTICLE_H_

class CParticle
{
private:
	int m_nCurrentColor;
	int m_nCurrentScale;
	int m_nDuration;
	float m_fPositionX;
	float m_fPositionY;
	float m_fVelocity;
	float m_fRotation;
public:
	CParticle(void){}
	~CParticle(void){}

	//TODO: GETs and Sets
};
#endif