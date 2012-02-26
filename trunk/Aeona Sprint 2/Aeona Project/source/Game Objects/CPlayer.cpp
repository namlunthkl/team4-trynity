////////////////////////////////////////////////////////////////////////
//    File Name				:	"CPlayer.cpp"
//    Author Name			:	Phil Sullivan
//    Creation Date			:	02/09/12 - 3:57 AM
//    Purpose				:	Game player character class definitions
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CPlayer.h"

CPlayer::CPlayer()
{
	SetImageID( -1 );
	m_cWeapons = 0;
	m_cMasks = 0;
	m_bHasHeartPiece = false;
	m_sBaseDamage = 10;
	m_cCurrentWeapon = 0;
	m_sndPlayer = -1;
}

CPlayer::~CPlayer()
{
}

void CPlayer::Attack()
{
}

void CPlayer::ChargedBlast()
{
}

void CPlayer::GetHurt()
{
}

void CPlayer::Die()
{
}

void CPlayer::CallOut()
{
}

void CPlayer::LevelUp()
{
}

bool CPlayer::Initialize(short sPosX, short sPosY, unsigned char ucCharType, unsigned int uiSpeed, unsigned char ucMaxHP, CAnimation* panmMove, CAnimation* panmDestruction)
{
	SetImageID( TEX_MNG->LoadTexture("resource/TempAsset1.png") );
	return true;
}

RECT CPlayer::GetCollisionRect()
{
	RECT temp = {32,32,32,32};
	return temp;
}

bool CPlayer::CheckCollision(IBaseInterface* pBase)
{
	return true;
}

void CPlayer::HandleEvent(CEvent* pEvent)
{
}

void CPlayer::Update(float fElapsedTime)
{
}

void CPlayer::Render()
{
	RECT rPlayer;
	rPlayer.left = 0;
	rPlayer.top = 0;
	rPlayer.right = 96;
	rPlayer.bottom = 96;
	TEX_MNG->Draw( GetImageID(), GetPosX(), GetPosY(), 1.0f, 1.0f, &rPlayer);
}

void CPlayer::Shutdown()
{
}
