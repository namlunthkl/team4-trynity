#include "SGD Wrappers\CSGD_TextureManager.h"
#include "AB_EmitterManager.h"
//#include "Enemy.h"
//#include "Factory.h"
#include <cstdlib>
#include "SGD Wrappers\CSGD_Direct3D.h"
#include <vector>
#include <d3dx9.h>

using namespace std;
EmitterManager* EmitterManager::instance = NULL;

EmitterManager::EmitterManager(void) {}

EmitterManager::~EmitterManager(void)
{
	int size = m_vEmitterList.size();
	for(int i = 0; i < size; i++)
	{
		m_vEmitterList[i]->Release();
	}
}

EmitterManager* EmitterManager::GetInstance(void)
{
	if(!instance)
	{
		instance = new EmitterManager();
	}

	return instance;
}

void EmitterManager::DeleteInstance(void)
{
	if(instance)
	{		
		delete instance;
		instance = NULL;
	}
}

void EmitterManager::UpdateEmitter(float fElapsedTime)
{
	for (unsigned int i = 0; i < m_vEmitterList.size(); i++)
	{
		m_vEmitterList[i]->Update(fElapsedTime);
	}
}

void EmitterManager::RenderEmitter()
{
	for (unsigned int j = 0; j < m_vEmitterList.size(); j++)
		m_vEmitterList[j]->Render();
}

void EmitterManager::AddEmitter(CEmitter* pEmitter)
{
	if(pEmitter == NULL)
		return;

	m_vEmitterList.push_back(pEmitter);

	pEmitter->AddRef();
}

void EmitterManager::RemoveEmitter( CEmitter* pEmitter)
{
	if(pEmitter == NULL)
		return;

	for(vector< CEmitter*>::iterator iter = m_vEmitterList.begin();
		iter != m_vEmitterList.end(); iter++)
	{
		if((*iter) == pEmitter)
		{
			(*iter)->Release();
			iter = m_vEmitterList.erase(iter);
			break;
		}
	}
}

void EmitterManager::RemoveAllEmitters(void)
{
	for(unsigned int i = 0; i < m_vEmitterList.size(); i++)
	{
		m_vEmitterList[i]->Release();
		delete (CEmitter*)(m_vEmitterList[i]);
		m_vEmitterList[i] = NULL;
	}

	m_vEmitterList.clear();
}

bool EmitterManager::Load(const char* szXMLFileName)
{
	string Folder = "Resource/Particles/";



	TiXmlDocument doc;

	if(doc.LoadFile(szXMLFileName) == false)
		return false;

	TiXmlElement* pRoot = doc.RootElement();

	if(pRoot == NULL)
		return false;

	TiXmlElement* L = pRoot->FirstChildElement("List");

	if(L)
	{
		TiXmlElement* E = L->FirstChildElement("Emitter");

		while(E)
		{
			CEmitter* tempE = new CEmitter();

			string temp;

			TiXmlElement* D = E->FirstChildElement("Data");

			TiXmlElement* pSize = D->FirstChildElement("fSize");
			temp = pSize->GetText();
			//tempE->Data->fSize = (float)atof(temp.c_str());
			tempE->m_pData->SetSize( (float)atof(temp.c_str()) );

			TiXmlElement* pLife = D->FirstChildElement("MaxLife");
			temp = pLife->GetText();
			//tempE->Data->MaxLife = (float)atof(temp.c_str());
			tempE->m_pData->SetMaxLife( (float)atof(temp.c_str()) );

			TiXmlElement* pMinVelX = D->FirstChildElement("MinVelX");
			temp = pMinVelX->GetText();
			//tempE->Data->MinVelX = (float)atof(temp.c_str());
			tempE->m_pData->SetMinVelocityX( (float)atof(temp.c_str()) );

			TiXmlElement* pMaxVelX = D->FirstChildElement("MaxVelX");
			temp = pMaxVelX->GetText();
			//tempE->Data->MaxVelX = (float)atof(temp.c_str());
			tempE->m_pData->SetMaxVelocityX( (float)atof(temp.c_str()) );

			TiXmlElement* pMinVelY = D->FirstChildElement("MinVelY");
			temp = pMinVelY->GetText();
			//tempE->Data->MinVelY = (float)atof(temp.c_str());
			tempE->m_pData->SetMinVelocityX( (float)atof(temp.c_str()) );

			TiXmlElement* pMaxVelY = D->FirstChildElement("MaxVelY");
			temp = pMaxVelY->GetText();
			//tempE->Data->MaxVelY = (float)atof(temp.c_str());
			tempE->m_pData->SetMaxVelocityY( (float)atof(temp.c_str()) );

			TiXmlElement* pSpawnAWid = D->FirstChildElement("SpwnAreaWidth");
			temp = pSpawnAWid->GetText();
			//tempE->Data->SpwnAreaWidth = (float)atof(temp.c_str());
			tempE->m_pData->SetSpawnAreaWidth( (float)atof(temp.c_str()) );

			TiXmlElement* pSpawnAHigh = D->FirstChildElement("SpwnAreaHeight");
			temp = pSpawnAHigh->GetText();
			//tempE->Data->SpwnAreaHeight = (float)atof(temp.c_str());
			tempE->m_pData->SetSpawnAreaHeight( (float)atof(temp.c_str()) );

			TiXmlElement* pMinSpwnRadius = D->FirstChildElement("MinSpwnRadius");
			temp = pMinSpwnRadius->GetText();
			//tempE->Data->MinSpwnRadius = (float)atof(temp.c_str());
			tempE->m_pData->SetMinSpawnRadius( (float)atof(temp.c_str()) );

			TiXmlElement* pMaxSpwnRadius = D->FirstChildElement("MaxSpwnRadius");
			temp = pMaxSpwnRadius->GetText();
			//tempE->Data->MaxSpwnRadius = (float)atof(temp.c_str());
			tempE->m_pData->SetMaxSpawnRadius( (float)atof(temp.c_str()) );

			TiXmlElement* pFadeEffect = D->FirstChildElement("FadeEffect");
			temp = pFadeEffect->GetText();
			//tempE->Data->FadeEffect = atoi(temp.c_str());
			tempE->m_pData->SetFadeEffect( atoi(temp.c_str()) );

			TiXmlElement* pFadeValue = D->FirstChildElement("FadeValue");
			temp = pFadeValue->GetText();
			//tempE->Data->FadeValue = (float)atof(temp.c_str());
			tempE->m_pData->SetFadeValue( (float)atof(temp.c_str()) );

			TiXmlElement* pScaleEffect = D->FirstChildElement("ScaleEffect");
			temp = pScaleEffect->GetText();
			//tempE->Data->ScaleEffect = atoi(temp.c_str());
			tempE->m_pData->SetScaleEffect( atoi(temp.c_str()) );

			TiXmlElement* pScaleValue = D->FirstChildElement("ScaleValue");
			temp = pScaleValue->GetText();
			//tempE->Data->ScaleValue = (float)atof(temp.c_str());
			tempE->m_pData->SetScaleValue( (float)atof(temp.c_str()) );

			TiXmlElement* pRotationEffect = D->FirstChildElement("RotationEffect");
			temp = pRotationEffect->GetText();
			//tempE->Data->RotationEffect = atoi(temp.c_str());
			tempE->m_pData->SetRotationEffect( atoi(temp.c_str()) );

			TiXmlElement* pRotationValue = D->FirstChildElement("RotationValue");
			temp = pRotationValue->GetText();
			//tempE->Data->RotationValue = (float)atof(temp.c_str());
			tempE->m_pData->SetRotationValue( (float)atof(temp.c_str()) );

			TiXmlElement* pRedEffect = D->FirstChildElement("RedEffect");
			temp = pRedEffect->GetText();
			//tempE->Data->RedEffect = atoi(temp.c_str());
			tempE->m_pData->SetRedEffect( atoi(temp.c_str()) );

			TiXmlElement* pRedValue = D->FirstChildElement("RedValue");
			temp = pRedValue->GetText();
			//tempE->Data->RedValue = (float)atof(temp.c_str());
			tempE->m_pData->SetRedValue( (float)atof(temp.c_str()) );

			TiXmlElement* pGreenEffect = D->FirstChildElement("GreenEffect");
			temp = pGreenEffect->GetText();
			//tempE->Data->GreenEffect = atoi(temp.c_str());
			tempE->m_pData->SetGreenEffect( atoi(temp.c_str()) );

			TiXmlElement* pGreenValue = D->FirstChildElement("GreenValue");
			temp = pGreenValue->GetText();
			//tempE->Data->GreenValue = (float)atof(temp.c_str());
			tempE->m_pData->SetGreenValue( (float)atof(temp.c_str()) );

			TiXmlElement* pBlueEffect = D->FirstChildElement("BlueEffect");
			temp = pBlueEffect->GetText();
			//tempE->Data->BlueEffect = atoi(temp.c_str());
			tempE->m_pData->SetBlueEffect( atoi(temp.c_str()) );

			TiXmlElement* pBlueValue = D->FirstChildElement("BlueValue");
			temp = pBlueValue->GetText();
			//tempE->Data->BlueValue = (float)atof(temp.c_str());
			tempE->m_pData->SetBlueValue( (float)atof(temp.c_str()) );

			TiXmlElement* pPattern = D->FirstChildElement("SpwnPattern");
			temp = pPattern->GetText();
			//tempE->Data->SpwnPattern = atoi(temp.c_str());
			tempE->m_pData->SetSpawnPattern( atoi(temp.c_str()) );

			TiXmlElement* pSource = D->FirstChildElement("Source");
			temp = pSource->GetText();
			//tempE->Data->Source = atoi(temp.c_str());
			tempE->m_pData->SetSource( atoi(temp.c_str()) );

			TiXmlElement* pDest = D->FirstChildElement("Dest");
			temp = pDest->GetText();
			//tempE->Data->Dest = atoi(temp.c_str());
			tempE->m_pData->SetDestination( atoi(temp.c_str()) );

			TiXmlElement* pUseBlend = D->FirstChildElement("UseBlend");
			temp = pUseBlend->GetText();
			if(temp == "true")
				//tempE->Data->UseBlend = true;
				tempE->m_pData->SetUseBlend( true );
			else
				//tempE->Data->UseBlend = false;
				tempE->m_pData->SetUseBlend( false );

			TiXmlElement* pEmitterPosX = D->FirstChildElement("EmitterPosX");
			temp = pEmitterPosX->GetText();
			//tempE->Data->EmitterPosX = (float)(atoi(temp.c_str()));
			tempE->m_pData->SetEmitterPositionX( (float)(atoi(temp.c_str())) );

			TiXmlElement* pEmitterPosY = D->FirstChildElement("EmitterPosY");
			temp = pEmitterPosY->GetText();
			//tempE->Data->EmitterPosY = (float)(atoi(temp.c_str()));
			tempE->m_pData->SetEmitterPositionY( (float)(atoi(temp.c_str())) );

			TiXmlElement* pMaxParticles = D->FirstChildElement("MaxParticles");
			temp = pMaxParticles->GetText();
			//tempE->Data->MaxParticles = atoi(temp.c_str());
			tempE->m_pData->SetMaxParticles( atoi(temp.c_str()) );

			TiXmlElement* pEmitterVelX = D->FirstChildElement("EmitterVelX");
			temp = pEmitterVelX->GetText();
			//tempE->Data->EmitterVelX = (float)(atoi(temp.c_str()));
			tempE->m_pData->SetEmitterVelocityX( (float)(atoi(temp.c_str())) );

			TiXmlElement* pEmitterVelY = D->FirstChildElement("EmitterVelY");
			temp = pEmitterVelY->GetText();
			//tempE->Data->EmitterVelY = (float)(atoi(temp.c_str()));
			tempE->m_pData->SetEmitterVelocityY( (float)(atoi(temp.c_str())) );

			TiXmlElement* pContinuous = E->FirstChildElement("Continuous");
			temp = pContinuous->GetText();
			if(temp == "true")
				//tempE->Continuous = true;
				tempE->m_bContinuous = true;
			else
				//tempE->Continuous = false;
				tempE->m_bContinuous = false;


			TiXmlElement* pImageFile = E->FirstChildElement("ImageFile");
			temp = pImageFile->GetText();
			//tempE->ImageFile = Folder + temp;
			tempE->m_sImageFile = Folder + temp;

			tempE->m_nImage = CSGD_TextureManager::GetInstance()->LoadTexture(tempE->m_sImageFile.c_str(), D3DCOLOR_XRGB(0,0,0));

			tempE->Init();
			AddEmitter(tempE);

			//tempE->Release();
			E = E->NextSiblingElement("Emitter");
		}
	}

	return true;
}