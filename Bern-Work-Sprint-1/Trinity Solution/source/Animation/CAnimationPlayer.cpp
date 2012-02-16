////////////////////////////////////////////////////////////////////////
//    File Name				:	"CAnimationPlayer.cpp"
//
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the Animation Player
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CAnimationPlayer.h"

void CAnimationPlayer::Play()
{
	if(!CAnimationManager::GetInstance()->GetAnimation(m_nAnimationId)->GetIsPlaying())
	{
		Reset();
		CAnimationManager::GetInstance()->GetAnimation(m_nAnimationId)->SetIsPlaying(true);
	}
}
void CAnimationPlayer::Stop()
{
	CAnimationManager::GetInstance()->GetAnimation(m_nAnimationId)->SetIsPlaying(false);
}
void CAnimationPlayer::Reset()
{
	this->m_nFrameNumber = 0;
	this->m_fTimer = 0;
}
void CAnimationPlayer::Update(float fElapsedTime)
{
	if(!CAnimationManager::GetInstance()->GetAnimation(m_nAnimationId)->GetIsPlaying())
		return;
	m_fTimer += fElapsedTime*CAnimationManager::GetInstance()->GetAnimation(m_nAnimationId)->GetSpeed();
	if(m_fTimer > CAnimationManager::GetInstance()->GetAnimation(m_nAnimationId)->GetFrame(m_nFrameNumber)->GetDuration())
	{
		m_fTimer -= CAnimationManager::GetInstance()->GetAnimation(m_nAnimationId)->GetFrame(m_nFrameNumber)->GetDuration();
		m_nFrameNumber++;
		if(m_nFrameNumber >= CAnimationManager::GetInstance()->GetAnimation(m_nAnimationId)->GetFrames()->size())
		{
			if(CAnimationManager::GetInstance()->GetAnimation(m_nAnimationId)->GetIsLooping())
			{
				Reset();
			}
			else
			{
				Stop();
				m_nFrameNumber = CAnimationManager::GetInstance()->GetAnimation(m_nAnimationId)->GetFrames()->size()-1;
			}
		}
	}
}
void CAnimationPlayer::Render()
{
	RECT drawRect = CAnimationManager::GetInstance()->GetAnimation(m_nAnimationId)->GetFrame(m_nFrameNumber)->GetDrawRect();
	POINT anchor = CAnimationManager::GetInstance()->GetAnimation(m_nAnimationId)->GetFrame(m_nFrameNumber)->GetAnchorPoint();
	TEX_MNG->Draw(m_nAnimationId,anchor.x,anchor.y,1,1,&drawRect);
}