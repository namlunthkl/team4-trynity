#pragma once

#include "CBase.h"
#include "Messaging\IListener.h"

class CPowerUp : public CBase, public IListener
{
	private:
		float	m_fRadius;
		int     m_nPowerUpType;

		int		m_nGoldSoundID;
		int		m_nLifeUpSoundID;

		CBase*	m_pOwner;

	public:
		CPowerUp(void);
		~CPowerUp(void);

		float GetRadius(void)	{ return m_fRadius; }
		int GetPowerUpType(void){ return m_nPowerUpType; }

		int GetGoldSoundID(void)	{ return m_nGoldSoundID; }
		int GetLifeUpSoundID(void)	{ return m_nLifeUpSoundID; }
		

		void SetRadius( float fRadius )				{ m_fRadius = fRadius; }
		void SetPowerUpType( int nPowerUpType )		{ m_nPowerUpType = nPowerUpType; }

		void SetGoldSoundID( int nGoldSoundID )		{ m_nGoldSoundID = nGoldSoundID; }
		void SetLifeUpSoundID( int nLifeUpSoundID )	{ m_nLifeUpSoundID = nLifeUpSoundID; }
		

		void Update( float fElapsedTime );
		void Render(void);
		bool CheckCollision( IBaseInterface * pBase );
		void HandleEvent( CEvent* pEvent );
		RECT GetRect();

		void SetPowerUpOwner( CBase* pOwner ) { m_pOwner = pOwner; }
};