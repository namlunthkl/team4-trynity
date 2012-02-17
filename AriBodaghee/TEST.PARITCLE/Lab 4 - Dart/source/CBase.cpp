///////////////////////////////////////////////////////////////////
//	File Name	:	"CBase.h"
//
//	Author Name	:	David Brown
//
//	Purpose		:	To contain all related data and functionality
//					for our game objects.
///////////////////////////////////////////////////////////////////
#include "CBase.h"
#include "SGD Wrappers\CSGD_TextureManager.h"	// included where it is used

CBase::CBase(void)
{
	m_uiRefCount = 1; // start with a ref to yourself!
	SetPosX(0);
	SetPosY(0);
	SetVelX(0);
	SetVelY(0);
	SetImageID(-1);
}
CBase::~CBase(void){}
void CBase::Update(float fElapsedTime)
{
	SetPosX( GetPosX() + GetVelX() * fElapsedTime );
	SetPosY( GetPosY() + GetVelY() * fElapsedTime );
}
void CBase::Render(void){}
RECT CBase::GetRect()
{
	RECT rRect = { (long)GetPosX(), (long)GetPosY(), (long)(GetPosX() + GetWidth()), (long)(GetPosY() + GetHeight()) };
	return rRect;
}
bool CBase::CheckCollision( IBaseInterface * pBase )
{
	RECT ColRect;
	bool toReturn = (IntersectRect(&ColRect, &GetRect(), &pBase->GetRect()) == TRUE ) ? true : false ;

	return toReturn;
}