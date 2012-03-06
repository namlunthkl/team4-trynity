////////////////////////////////////////////////////////////////////////
//    File Name				:	"CArrow.cpp"
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	3/01/12
//    Purpose				:	Arrow
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CArrow.h"
#include "../Game Objects/CPlayer.h"
#include "../Game Objects/CObjectManager.h"
#include "../Weapons/CCrossBow.h"

CArrow::CArrow()
{

}
bool CArrow::CheckCollision(IBaseInterface* pObject)
{
	return true;
}