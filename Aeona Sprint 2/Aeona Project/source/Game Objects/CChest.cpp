////////////////////////////////////////////////////////////////////////
//    File Name				:	"CChest.cpp"
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/09/12 - 3:57 AM
//    Purpose				:	CChest
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CChest.h"
CChest::CChest(const char* szName, bool bActiveTalk, double dRange, int sndNPC,double dPositionX, double dPositionY, unsigned int uiSpeed,
	int nImageID, unsigned int uiWidth, unsigned int uiHeight, bool bActive,unsigned int uiMaxHealth, unsigned int uiAttackDamage) 
	: CNPC(szName,bActiveTalk,dPositionX,dPositionY,uiSpeed,nImageID,uiWidth,uiHeight,bActive,uiMaxHealth,uiAttackDamage)
{
}
CChest::~CChest()
{

}