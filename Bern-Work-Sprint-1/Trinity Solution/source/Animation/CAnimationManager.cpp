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
	filepath.append("../Resource/");

	const char* pDir;
	if(pRoot->Attribute("FileName"))
	{
		pDir = pRoot->Attribute("FileName");
		char buffer[128] = {0};
		strcpy_s(buffer,_countof(buffer),pDir);
		filepath.append(pDir);
	}
	TEX_MNG->LoadTexture(filepath.c_str());

	TiXmlElement* pAnimation = pRoot->FirstChildElement("Animations");
	while(pAnimation)
	{
		CAnimation tempAnimation;
		int nTemp;
		float fTemp;
		const char* pDir;
		if(pAnimation->Attribute("Name"))
		{
			pDir = pRoot->Attribute("Name");
			char buffer[128] = {0};
			strcpy_s(buffer,_countof(buffer),pDir);
			tempAnimation.SetName(buffer);
		}

		if(pAnimation->QueryIntAttribute("islooping",&nTemp) != NULL)
		{

			tempAnimation.SetIsLooping((nTemp==1)?true:false);
		}

		if(pAnimation->QueryIntAttribute("isoslating",&nTemp) != NULL)
		{
			tempAnimation.SetIsOscillating((nTemp==1)?true:false);
		}
		if(pAnimation->QueryIntAttribute("isplaying",&nTemp) != NULL)
		{
			tempAnimation.SetIsPlaying((nTemp==1)?true:false);
		}
		if(pAnimation->QueryFloatAttribute("speed",&fTemp) != NULL)
		{
			tempAnimation.SetSpeed(fTemp);
		}
		if(pAnimation->QueryIntAttribute("speed",&nTemp) != NULL)
		{
			//tempAnimation.SetFrames(temp);
		}
		//const char* pType = pHighscore->GetText();
		//if(pType)
		//{
		//	char cBuffer[128] = {0};
		//	strcpy_s(cBuffer,_countof(cBuffer),pType);
		//	//printf("type: %s", buffer);
		//	//m_vMenuItems.push_back(cBuffer);
		//	scoreline += cBuffer;
		//}
		//if(pHighscore->Attribute("score",&score) != NULL)
		//{
		//	char cBuffer[128] = {0};
		//	sprintf_s(cBuffer,"score: %d ", score);
		//	//m_vMenuItems.push_back(cBuffer);
		//	scoreline+= cBuffer;
		//}
		//scoreline+= '\n';
		//m_vMenuItems.push_back(scoreline.c_str());
		pAnimation = pAnimation->NextSiblingElement("Animation");
	}
	return 0;
}

bool CAnimationManager::UnloadAll()
{
	return true;
}
