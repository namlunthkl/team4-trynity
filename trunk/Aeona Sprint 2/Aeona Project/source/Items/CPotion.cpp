////////////////////////////////////////////////////////////////////////
//    File Name				:	"CPotion.cpp"
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	3/01/12
//    Purpose				:	CPotion
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CPotion.h"
#include "../Game Objects/CPlayer.h"
CPotion::CPotion()
{

}
void CPotion::Heal(void)
{
	CPlayer::GetInstance()->SetCurHealth(CPlayer::GetInstance()->GetCurHealth()+1);
}