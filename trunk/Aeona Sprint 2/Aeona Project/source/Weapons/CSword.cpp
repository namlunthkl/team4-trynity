////////////////////////////////////////////////////////////////////////
//    File Name				:	"CSword.cpp"
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	3/01/12
//    Purpose				:	CSword
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CSword.h"
#include "../Game Objects/CPlayer.h"
CSword::CSword()
{
	
	//Load the Animation
	CBaseCharacter::LoadAnimations("resource/PlayerWSword.xml");
	SetAttacking(false);
}
void CSword::Render(PointD nPos)
{
	SetPosX(nPos.x);
	SetPosY(nPos.y);
	
	CBaseCharacter::Render();
}

void CSword::Update(float fElapsedTime)
{
	CBaseCharacter::Update(fElapsedTime);
	
}
void CSword::Attack(void)
{
	SetAttacking(true);

}
void CSword::ChargedAttack(void)
{
	
}
