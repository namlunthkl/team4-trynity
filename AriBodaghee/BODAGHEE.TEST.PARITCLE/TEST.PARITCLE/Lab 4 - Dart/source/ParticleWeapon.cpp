#include "ParticleWeapon.h"
#include "CGame.h"
#include "tinyxml\tinystr.h"
#include "tinyxml\tinyxml.h"

ParticleWeapon::ParticleWeapon(void)
{
	Fired = false;
}

ParticleWeapon::~ParticleWeapon(void)
{
	for(unsigned int i = 0; i < Emitters.size(); i++)
	{
		delete (Emitter*)(Emitters[i]);
		Emitters[i] = NULL;
		
	}
	Emitters.clear();
}

void ParticleWeapon::Fire(int PosX, int PosY)
{
	Fired = true;
	
	for(unsigned int i = 0; i < Emitters.size(); i++)
	{
		Emitters[i]->reAnimate = true;
		Emitters[i]->Data->EmitterPosX = (float)PosX;
		Emitters[i]->Data->EmitterPosY = (float)PosY;
	}
}

void ParticleWeapon::Update(float DT)
{
	if(Fired == false)
		for(unsigned int i = 0; i < Emitters.size(); i++)
		{
			Emitters[i]->Data->EmitterPosX = -1000;
			Emitters[i]->Data->EmitterPosY = -1000;
		}


	for(unsigned int i = 0; i < Emitters.size(); i++)
	{
		Emitters[i]->Update(DT);

		if(Emitters[i]->Data->EmitterPosY <= 0)
			Fired = false;
	}
}

void ParticleWeapon::Render()
{

	for(unsigned int i = 0; i < Emitters.size(); i++)
		Emitters[i]->Render();
}
bool ParticleWeapon::Load(const char* szXMLFileName)
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
			Emitter* tempE = new Emitter();
			string temp;

			TiXmlElement* D = E->FirstChildElement("Data");

			TiXmlElement* pSize = D->FirstChildElement("fSize");
			temp = pSize->GetText();
			tempE->Data->fSize = (float)atof(temp.c_str());


			TiXmlElement* pLife = D->FirstChildElement("MaxLife");
			temp = pLife->GetText();
			tempE->Data->MaxLife = (float)atof(temp.c_str());

			TiXmlElement* pMinVelX = D->FirstChildElement("MinVelX");
			temp = pMinVelX->GetText();
			tempE->Data->MinVelX = (float)atof(temp.c_str());

			TiXmlElement* pMaxVelX = D->FirstChildElement("MaxVelX");
			temp = pMaxVelX->GetText();
			tempE->Data->MaxVelX = (float)atof(temp.c_str());

			TiXmlElement* pMinVelY = D->FirstChildElement("MinVelY");
			temp = pMinVelY->GetText();
			tempE->Data->MinVelY = (float)atof(temp.c_str());

			TiXmlElement* pMaxVelY = D->FirstChildElement("MaxVelY");
			temp = pMaxVelY->GetText();
			tempE->Data->MaxVelY = (float)atof(temp.c_str());

			TiXmlElement* pSpawnAWid = D->FirstChildElement("SpwnAreaWidth");
			temp = pSpawnAWid->GetText();
			tempE->Data->SpwnAreaWidth = (float)atof(temp.c_str());

			TiXmlElement* pSpawnAHigh = D->FirstChildElement("SpwnAreaHeight");
			temp = pSpawnAHigh->GetText();
			tempE->Data->SpwnAreaHeight = (float)atof(temp.c_str());

			TiXmlElement* pMinSpwnRadius = D->FirstChildElement("MinSpwnRadius");
			temp = pMinSpwnRadius->GetText();
			tempE->Data->MinSpwnRadius = (float)atof(temp.c_str());

			TiXmlElement* pMaxSpwnRadius = D->FirstChildElement("MaxSpwnRadius");
			temp = pMaxSpwnRadius->GetText();
			tempE->Data->MaxSpwnRadius = (float)atof(temp.c_str());

			TiXmlElement* pFadeEffect = D->FirstChildElement("FadeEffect");
			temp = pFadeEffect->GetText();
			tempE->Data->FadeEffect = atoi(temp.c_str());

			TiXmlElement* pFadeValue = D->FirstChildElement("FadeValue");
			temp = pFadeValue->GetText();
			tempE->Data->FadeValue = (float)atof(temp.c_str());

			TiXmlElement* pScaleEffect = D->FirstChildElement("ScaleEffect");
			temp = pScaleEffect->GetText();
			tempE->Data->ScaleEffect = atoi(temp.c_str());

			TiXmlElement* pScaleValue = D->FirstChildElement("ScaleValue");
			temp = pScaleValue->GetText();
			tempE->Data->ScaleValue = (float)atof(temp.c_str());

			TiXmlElement* pRotationEffect = D->FirstChildElement("RotationEffect");
			temp = pRotationEffect->GetText();
			tempE->Data->RotationEffect = atoi(temp.c_str());

			TiXmlElement* pRotationValue = D->FirstChildElement("RotationValue");
			temp = pRotationValue->GetText();
			tempE->Data->RotationValue = (float)atof(temp.c_str());

			TiXmlElement* pRedEffect = D->FirstChildElement("RedEffect");
			temp = pRedEffect->GetText();
			tempE->Data->RedEffect = atoi(temp.c_str());

			TiXmlElement* pRedValue = D->FirstChildElement("RedValue");
			temp = pRedValue->GetText();
			tempE->Data->RedValue = (float)atof(temp.c_str());

			TiXmlElement* pGreenEffect = D->FirstChildElement("GreenEffect");
			temp = pGreenEffect->GetText();
			tempE->Data->GreenEffect = atoi(temp.c_str());

			TiXmlElement* pGreenValue = D->FirstChildElement("GreenValue");
			temp = pGreenValue->GetText();
			tempE->Data->GreenValue = (float)atof(temp.c_str());

			TiXmlElement* pBlueEffect = D->FirstChildElement("BlueEffect");
			temp = pBlueEffect->GetText();
			tempE->Data->BlueEffect = atoi(temp.c_str());

			TiXmlElement* pBlueValue = D->FirstChildElement("BlueValue");
			temp = pBlueValue->GetText();
			tempE->Data->BlueValue = (float)atof(temp.c_str());

			TiXmlElement* pPattern = D->FirstChildElement("SpwnPattern");
			temp = pPattern->GetText();
			tempE->Data->SpwnPattern = atoi(temp.c_str());

			TiXmlElement* pSource = D->FirstChildElement("Source");
			temp = pSource->GetText();
			tempE->Data->Source = atoi(temp.c_str());

			TiXmlElement* pDest = D->FirstChildElement("Dest");
			temp = pDest->GetText();
			tempE->Data->Dest = atoi(temp.c_str());

			TiXmlElement* pUseBlend = D->FirstChildElement("UseBlend");
			temp = pUseBlend->GetText();
			if(temp == "true")
				tempE->Data->UseBlend = true;
			else
				tempE->Data->UseBlend = false;

			TiXmlElement* pEmitterPosX = D->FirstChildElement("EmitterPosX");
			temp = pEmitterPosX->GetText();
			tempE->Data->EmitterPosX = (float)(atoi(temp.c_str()));

			TiXmlElement* pEmitterPosY = D->FirstChildElement("EmitterPosY");
			temp = pEmitterPosY->GetText();
			tempE->Data->EmitterPosY = (float)(atoi(temp.c_str()));

			TiXmlElement* pMaxParticles = D->FirstChildElement("MaxParticles");
			temp = pMaxParticles->GetText();
			tempE->Data->MaxParticles = atoi(temp.c_str());

			TiXmlElement* pEmitterVelX = D->FirstChildElement("EmitterVelX");
			temp = pEmitterVelX->GetText();
			tempE->Data->EmitterVelX = (float)(atoi(temp.c_str()));

			TiXmlElement* pEmitterVelY = D->FirstChildElement("EmitterVelY");
			temp = pEmitterVelY->GetText();
			tempE->Data->EmitterVelY = (float)(atoi(temp.c_str()));

			TiXmlElement* pContinuous = E->FirstChildElement("Continuous");
			temp = pContinuous->GetText();
			if(temp == "true")
				tempE->Continuous = true;
			else
				tempE->Continuous = false;


			TiXmlElement* pImageFile = E->FirstChildElement("ImageFile");
			temp = pImageFile->GetText();
			tempE->ImageFile = Folder + temp;

			tempE->Image = CSGD_TextureManager::GetInstance()->LoadTexture(tempE->ImageFile.c_str(), D3DCOLOR_XRGB(0,0,0));

			tempE->Init();
			Emitters.push_back(tempE);

			E = E->NextSiblingElement("Emitter");
		}
	}

	return true;
}