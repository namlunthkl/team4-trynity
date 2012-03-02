#include "StdAfx.h"
#include "ParticleWeapon.h"
#include "..\CGame.h"
#include "..\tinyxml\tinystr.h"
#include "..\tinyxml\tinyxml.h"

ParticleWeapon::ParticleWeapon(void)
{
	Fired = false;
}
ParticleWeapon::~ParticleWeapon(void)
{
	//for(unsigned int i = 0; i < Emitters.size(); i++)
	//{
	//	delete (Emitter*)(Emitters[i]);
	//	Emitters[i] = NULL;	
	//}
	//Emitters.clear();
}
void ParticleWeapon::Fire()
{
	Fired = true;
	emitter.reAnimate = true;
}
void ParticleWeapon::Update(float DT)
{
	emitter.Update(DT);
}
void ParticleWeapon::Render()
{
	emitter.Render();
}
bool ParticleWeapon::Load(const char* szXMLFileName)
{
	string Folder = "Resource/Particles/";

	TiXmlDocument doc;

	if( !doc.LoadFile(szXMLFileName) ) { return false; }

	TiXmlElement* pRoot = doc.RootElement();

	if( !pRoot ){ return false; }

	if(pRoot)
	{
		string temp;

		TiXmlElement* pImageFile = pRoot->FirstChildElement("ImageFile");
		temp = pImageFile->GetText();
		emitter.ImageFile = Folder + temp;
		
		emitter.Image = CSGD_TextureManager::GetInstance()->LoadTexture(emitter.ImageFile.c_str(), D3DCOLOR_XRGB(0,0,0));

		TiXmlElement* pContinuous = pRoot->FirstChildElement("Continuous");
		temp = pContinuous->GetText();
		if(temp == "1"){ emitter.Continuous = true; } 
		else{ emitter.Continuous = false; }

		TiXmlElement* pReAnimate = pRoot->FirstChildElement("Reanimate");
		temp = pReAnimate->GetText();
		if(temp == "1"){ emitter.reAnimate = true; } 
		else{ emitter.reAnimate = false; }

		TiXmlElement* pEmitterPosX = pRoot->FirstChildElement("EmitterPosX");
		temp = pEmitterPosX->GetText();
		emitter.EmitterPosX = (float)(atoi(temp.c_str()));

		TiXmlElement* pEmitterPosY = pRoot->FirstChildElement("EmitterPosY");
		temp = pEmitterPosY->GetText();
		emitter.EmitterPosY = (float)(atoi(temp.c_str()));

		TiXmlElement* pMaxParticles = pRoot->FirstChildElement("MaxParticles");
		temp = pMaxParticles->GetText();
		emitter.MaxParticles = atoi(temp.c_str());

		TiXmlElement* pSize = pRoot->FirstChildElement("Size");
		temp = pSize->GetText();
		emitter.fSize = (float)atof(temp.c_str());

		TiXmlElement* pLife = pRoot->FirstChildElement("MaxLife");
		temp = pLife->GetText();
		emitter.MaxLife = (float)atof(temp.c_str());

		TiXmlElement* pSpawnWidth = pRoot->FirstChildElement("SpawnWidth");
		temp = pSpawnWidth->GetText();
		emitter.SpawnWidth = (float)atof(temp.c_str());

		TiXmlElement* pSpawnHeight = pRoot->FirstChildElement("SpawnHeight");
		temp = pSpawnHeight->GetText();
		emitter.SpawnHeight = (float)atof(temp.c_str());

		TiXmlElement* pScaleStart = pRoot->FirstChildElement("ScaleStart");
		temp = pScaleStart->GetText();
		emitter.ScaleStart = (float)atof(temp.c_str());

		TiXmlElement* pScaleEnd = pRoot->FirstChildElement("ScaleEnd");
		temp = pScaleEnd->GetText();
		emitter.ScaleEnd = (float)atof(temp.c_str());

		TiXmlElement* pRotation = pRoot->FirstChildElement("Rotation");
		temp = pRotation->GetText();
		emitter.Rotation = (float)atof(temp.c_str());

		TiXmlElement* pMinVelX = pRoot->FirstChildElement("MinVelX");
		temp = pMinVelX->GetText();
		emitter.MinVelX = (float)atof(temp.c_str());

		TiXmlElement* pMaxVelX = pRoot->FirstChildElement("MaxVelX");
		temp = pMaxVelX->GetText();
		emitter.MaxVelX = (float)atof(temp.c_str());

		TiXmlElement* pMinVelY = pRoot->FirstChildElement("MinVelY");
		temp = pMinVelY->GetText();
		emitter.MinVelY = (float)atof(temp.c_str());

		TiXmlElement* pMaxVelY = pRoot->FirstChildElement("MaxVelY");
		temp = pMaxVelY->GetText();
		emitter.MaxVelY = (float)atof(temp.c_str());




		TiXmlElement* pStartColorA = pRoot->FirstChildElement("StartColorA");
		temp = pStartColorA->GetText();
		emitter.ColorStartA = (int)atof(temp.c_str());

		TiXmlElement* pStartColorR = pRoot->FirstChildElement("StartColorR");
		temp = pStartColorR->GetText();
		emitter.ColorStartR = (int)atof(temp.c_str());

		TiXmlElement* pStartColorG = pRoot->FirstChildElement("StartColorG");
		temp = pStartColorG->GetText();
		emitter.ColorStartG = (int)atof(temp.c_str());

		TiXmlElement* pStartColorB = pRoot->FirstChildElement("StartColorB");
		temp = pStartColorB->GetText();
		emitter.ColorStartB = (int)atof(temp.c_str());



		TiXmlElement* pEndColorA = pRoot->FirstChildElement("EndColorA");
		temp = pEndColorA->GetText();
		emitter.ColorEndA = (int)atof(temp.c_str());

		TiXmlElement* pEndColorR = pRoot->FirstChildElement("EndColorR");
		temp = pEndColorR->GetText();
		emitter.ColorEndR = (int)atof(temp.c_str());

		TiXmlElement* pEndColorG = pRoot->FirstChildElement("EndColorG");
		temp = pEndColorG->GetText();
		emitter.ColorEndG = (int)atof(temp.c_str());

		TiXmlElement* pEndColorB = pRoot->FirstChildElement("EndColorB");
		temp = pEndColorB->GetText();
		emitter.ColorEndB = (int)atof(temp.c_str());

		TiXmlElement* pSource = pRoot->FirstChildElement("Source");
		temp = pSource->GetText();
		emitter.Source = atoi(temp.c_str());

		TiXmlElement* pDest = pRoot->FirstChildElement("Dest");
		temp = pDest->GetText();
		emitter.Destination = atoi(temp.c_str());

		TiXmlElement* pGravPosX = pRoot->FirstChildElement("GravPosX");
		temp = pGravPosX->GetText();
		emitter.GravityPosX = (float)atoi(temp.c_str());

		TiXmlElement* pGravPosY = pRoot->FirstChildElement("GravPosY");
		temp = pGravPosY->GetText();
		emitter.GravityPosY = (float)atoi(temp.c_str());

		TiXmlElement* pGravPower = pRoot->FirstChildElement("GravPower");
		temp = pGravPower->GetText();
		emitter.GravityPower = (float)atoi(temp.c_str());
		
		TiXmlElement* pGravDistX = pRoot->FirstChildElement("GravDistX");
		temp = pGravDistX->GetText();
		emitter.GravityDistX = (float)atoi(temp.c_str());

		TiXmlElement* pGravDistY = pRoot->FirstChildElement("GravDistY");
		temp = pGravDistY->GetText();
		emitter.GravityDistY = (float)atoi(temp.c_str());

		emitter.Init();
	}

	return true;
}