////////////////////////////////////////////////////////////////////////
//    File Name    : "CCameraControl.cpp"
//
//    Author Name   : Ari Bodaghee
//    Creation Date   : 02/08/12 - 7:47 PM
//    Purpose    : Contains the CCameraControl
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CCameraControl.h"

CCameraControl::CCameraControl(void)
{
	
}
CCameraControl* CCameraControl::GetInstance(void)
{
	static CCameraControl instance;
	return &instance;
}
CCameraControl::~CCameraControl(void)
{

}
void CCameraControl::InitializeCamera()
{

}
void CCameraControl::Update( float fTime )
{

}
void CCameraControl::KillCamSequence( float fAmountOfTimeToPause )
{
	
}
void CCameraControl::ChargeCamSequence( float fChargeTime )
{

}