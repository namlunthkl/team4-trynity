////////////////////////////////////////////////////////////////////////
//    File Name				:	"CChest.cpp"
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/09/12 - 3:57 AM
//    Purpose				:	CChest
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CChest.h"
#include "../Messaging/CMessageSystem.h"
#include "../Game Objects/CPlayer.h"
#include "../Input Manager/CInputManager.h"
CChest::CChest(const char* szName, bool bActiveTalk, double dRange, int sndNPC,double dPositionX, double dPositionY, unsigned int uiSpeed,
	int nImageID, unsigned int uiWidth, unsigned int uiHeight, bool bActive,unsigned int uiMaxHealth, unsigned int uiAttackDamage) 
	: CNPC(szName,bActiveTalk,dRange,sndNPC,dPositionX,dPositionY,uiSpeed,nImageID,uiWidth,uiHeight,bActive,uiMaxHealth,uiAttackDamage)
{
	m_bOpened = false;
}
void CChest::LoadAnimations(char const * const szFilename)
{
	CNPC::LoadAnimations(szFilename);
	GetAnimationPlayer(GetCurrentAnimation())->SetLooping(false);
	GetAnimationPlayer(GetCurrentAnimation())->Pause();
}
void CChest::Render(void)
{
	if(GetAnimationPlayer(GetCurrentAnimation())->GetFrameNumber() == 3 && m_bOpened == false )
	{
		m_bOpened = true;
		CPlayer::GetInstance()->SetNumPotions(CPlayer::GetInstance()->GetNumPotions()+1);
		GetAnimationPlayer(GetCurrentAnimation())->Pause();
	}
	CNPC::Render();
}
void CChest::Input(void)
{
	CBaseCharacter::Input();

	if(CInputManager::GetInstance()->GetPressedA() && m_bOpened == false)
	{
		OpenChest();
	}

}
CChest::~CChest()
{

}
void CChest::OpenChest(void)
{
	GetAnimationPlayer(GetCurrentAnimation())->Play();

	//TEMPORARY EFFECT TODO
	CPlayer::GetInstance()->SetNumPotions( CPlayer::GetInstance()->GetNumPotions() + 1 );
}