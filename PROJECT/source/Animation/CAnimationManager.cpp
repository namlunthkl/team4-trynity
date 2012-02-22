////////////////////////////////////////////////////////////////////////
//    File Name				:	"CAnimationManager.cpp"
//
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the Animation Manager
////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "CAnimationManager.h"
CAnimationManager* CAnimationManager::GetInstance()
{
	// Lazy instantiation
	static CAnimationManager instance;
	return &instance;
}

bool CAnimationManager::UnloadAnimation(int nAnimation)
{
	return true;
}

int CAnimationManager::LoadAnimation(const char* szFileName)
{
	TiXmlDocument doc;
	if(doc.LoadFile(szFileName) == false)
		return false;

	TiXmlElement* pRoot = doc.RootElement();

	if(!pRoot)
		return false;
	string filepath;
	filepath.append("resource/");

	const char* pDir;
	if(pRoot->Attribute("FileName"))
	{
		pDir = pRoot->Attribute("FileName");
		char buffer[128] = {0};
		strcpy_s(buffer,_countof(buffer),pDir);
		filepath.append(pDir);
	}
	int nAnimationSheet = TEX_MNG->LoadTexture(filepath.c_str(),D3DCOLOR_XRGB(255,0,255));
	
	TiXmlElement* pAnimation = pRoot->FirstChildElement("Animation");
	while(pAnimation)
	{

		CAnimation* tempAnimation = new CAnimation;
		int nTemp = 0;
		double dTemp = 0.0;
		const char* pName;
		if(pAnimation->Attribute("name"))
		{
			pName = pAnimation->Attribute("name");
			char buffer[128] = {0};
			strcpy_s(buffer,_countof(buffer),pName);
			tempAnimation->SetName(buffer);
		}

		if(pAnimation->QueryIntAttribute("looping",&nTemp) != TIXML_NO_ATTRIBUTE)
		{
			tempAnimation->SetIsLooping((nTemp==1)?true:false);
		}

		if(pAnimation->QueryIntAttribute("oslating",&nTemp) != TIXML_NO_ATTRIBUTE)
		{
			tempAnimation->SetIsOscillating((nTemp==1)?true:false);
		}
		if(pAnimation->QueryIntAttribute("playing",&nTemp) != TIXML_NO_ATTRIBUTE)
		{
			tempAnimation->SetIsPlaying((nTemp==1)?true:false);
		}
		if(pAnimation->QueryDoubleAttribute("speed",&dTemp) != TIXML_NO_ATTRIBUTE)
		{
			tempAnimation->SetSpeed(dTemp);
		}
		//if(pAnimation->Attribute("NumFrames",&nTemp) != NULL)
		//{
		//	tempAnimation.SetSpeed(nTemp);
		//}
		TiXmlElement* pFrame = pAnimation->FirstChildElement("Frame");
		while (pFrame)
		{
			CFrame tempFrame;
			if(pAnimation->QueryDoubleAttribute("Duration",&dTemp) != NULL)
			{
				tempFrame.SetDuration(dTemp);
			}

			const char* pEvent;
			if(pFrame->Attribute("event"))
			{
				pEvent = pFrame->Attribute("event");
				tempFrame.SetEvent(pEvent);
			}

			//	Get the draw rect
			TiXmlElement* pDrawRect = pFrame->FirstChildElement("DrawRect");

			RECT tempDrawRect;
			if(pDrawRect->QueryIntAttribute("x",&nTemp) != TIXML_NO_ATTRIBUTE)
			{
				tempDrawRect.left = nTemp;
			}
			if(pDrawRect->QueryIntAttribute("y",&nTemp) != TIXML_NO_ATTRIBUTE)
			{
				tempDrawRect.top = nTemp;
			}
			if(pDrawRect->QueryIntAttribute("width",&nTemp) != TIXML_NO_ATTRIBUTE)
			{
				tempDrawRect.right = tempDrawRect.left + nTemp;
			}
			if(pDrawRect->QueryIntAttribute("height",&nTemp) != TIXML_NO_ATTRIBUTE)
			{
				tempDrawRect.bottom = tempDrawRect.top + nTemp;
			}
			//	Set the Draw Rect
			tempFrame.SetDrawRect(tempDrawRect);

			//	Get the collsion Rect
			TiXmlElement* pCollisionRect = pDrawRect->NextSiblingElement("CollisionRect");

			RECT tempCollisionRect;
			if(pCollisionRect->QueryIntAttribute("x",&nTemp) != TIXML_NO_ATTRIBUTE)
			{
				tempCollisionRect.left = nTemp;
			}
			if(pCollisionRect->QueryIntAttribute("y",&nTemp) != TIXML_NO_ATTRIBUTE)
			{
				tempCollisionRect.top = nTemp;
			}
			if(pCollisionRect->QueryIntAttribute("width",&nTemp) != TIXML_NO_ATTRIBUTE)
			{
				tempCollisionRect.right = tempCollisionRect.left + nTemp;
			}
			if(pCollisionRect->QueryIntAttribute("height",&nTemp) != TIXML_NO_ATTRIBUTE)
			{
				tempCollisionRect.bottom = tempCollisionRect.top + nTemp;
			}
			//	Set the collision Rect
			tempFrame.SetCollisionRect(tempCollisionRect);
			//	Get the anchor
			TiXmlElement* pAnchor = pDrawRect->NextSiblingElement("Anchor");

			POINT tempAnchor;

			if(pAnchor->QueryIntAttribute("x",&nTemp) != TIXML_NO_ATTRIBUTE)
			{
				tempAnchor.x = nTemp;
			}
			if(pAnchor->QueryIntAttribute("y",&nTemp) != TIXML_NO_ATTRIBUTE)
			{
				tempAnchor.y = nTemp;
			}
			//	Set the anchor
			tempFrame.SetAnchorPoint(tempAnchor);
			tempAnimation->GetFrames()->push_back(tempFrame);
			pFrame = pFrame->NextSiblingElement("Frame");
		}
		tempAnimation->SetImageId(nAnimationSheet);
		m_Animations.push_back(tempAnimation);
		pAnimation = pAnimation->NextSiblingElement("Animation");
		
	}
	return 0;
}

bool CAnimationManager::UnloadAll()
{
	m_Animations.clear();
	return true;
}
