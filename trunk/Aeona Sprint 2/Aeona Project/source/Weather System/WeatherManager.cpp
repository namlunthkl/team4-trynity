#include "StdAfx.h"
#include "WeatherManager.h"
#include "..\CGame.h"
#include "..\tinyxml\tinystr.h"
#include "..\tinyxml\tinyxml.h"
#include "..\Wrappers\SGD_Math.h"
#include "..\Light System\LightEngine.h"

CWeatherManager::CWeatherManager()
{
	SetTypeOfWeather( 0.0f );
	SetTimeToWait( 5.0f );
	SetIsOn( false );
	SetTime( 0.0f );
}
CWeatherManager::~CWeatherManager()
{
	SetTimeToWait( 0.0f );
	SetIsOn( false );
}
CWeatherManager* CWeatherManager::GetInstance(void)
{
	static CWeatherManager instance;
	return &instance;
}
void CWeatherManager::LoadWeather( short TypeOfWeather )
{
	SetTypeOfWeather( TypeOfWeather );
	switch( GetTypeOfWeather() )
	{
	case 0:
		{
			weather.ShutDown();CWeatherManager::GetInstance()->SetIsOn( false );
			SetTimeToWait( RandomFloat( 5.0, 50.0f ) );
		}
		break;
	case RAIN:
		{
			weather.ShutDown();
			LoadXML("Resource/data/Rain.xml");
			CWeatherManager::GetInstance()->SetIsOn( true );
			SetTimeToWait( RandomFloat( 5.0, 50.0f ) );
		}
		break;
	case SNOW:
		{
			weather.ShutDown();
			LoadXML("Resource/data/Snow.xml");
			CWeatherManager::GetInstance()->SetIsOn( true );
			SetTimeToWait( RandomFloat( 5.0, 50.0f ) );
		}
		break;
	case LEAVES:
		{
			weather.ShutDown();
			LoadXML("Resource/data/FallingLeaves.xml");
			CWeatherManager::GetInstance()->SetIsOn( true );
			SetTimeToWait( RandomFloat( 5.0, 50.0f ) );
		}
		break;
	case SAND:
		{
			weather.ShutDown();
			LoadXML("Resource/data/SandStorm.xml");
			CWeatherManager::GetInstance()->SetIsOn( true );
			SetTimeToWait( RandomFloat( 5.0, 50.0f ) );
		}
		break;
	case EMBER:
		{
			weather.ShutDown();
			LoadXML("Resource/data/Embers.xml");
			CWeatherManager::GetInstance()->SetIsOn( true );
			SetTimeToWait( RandomFloat( 5.0, 50.0f ) );
		}
		break;
	case FIREFLIES:
		{
			weather.ShutDown();
			LoadXML("Resource/data/FireFlies.xml");
			CWeatherManager::GetInstance()->SetIsOn( true );
			SetTimeToWait( RandomFloat( 5.0, 50.0f ) );
		}
		break;
	}
}
void CWeatherManager::Update( float fTime )
{
	SetTime( GetTime() + fTime );

	if( GetTime() > GetTimeToWait() )
	{
		LoadWeather( (short)RandomInt( 0, 7 ) );
		SetTime( 0.0f );
	}

	if( GetIsOn() ) 
	{ 
		weather.Update( fTime );
	}
}
void CWeatherManager::Render()
{
	if( GetIsOn() ) 
	{ 
		weather.Render(); 
	}
}
bool CWeatherManager::LoadXML(const char* szXMLFileName)
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
		weather.ImageFile = Folder + temp;

		weather.Image = CSGD_TextureManager::GetInstance()->LoadTexture(weather.ImageFile.c_str(), D3DCOLOR_XRGB(0,0,0));

		TiXmlElement* pContinuous = pRoot->FirstChildElement("Continuous");
		temp = pContinuous->GetText();
		if(temp == "1"){ weather.Continuous = true; } 
		else{ weather.Continuous = false; }

		TiXmlElement* pReAnimate = pRoot->FirstChildElement("Reanimate");
		temp = pReAnimate->GetText();
		if(temp == "1"){ weather.reAnimate = true; } 
		else{ weather.reAnimate = false; }

		TiXmlElement* pEmitterPosX = pRoot->FirstChildElement("EmitterPosX");
		temp = pEmitterPosX->GetText();
		weather.EmitterPosX = (float)(atoi(temp.c_str()));

		TiXmlElement* pEmitterPosY = pRoot->FirstChildElement("EmitterPosY");
		temp = pEmitterPosY->GetText();
		weather.EmitterPosY = (float)(atoi(temp.c_str()));

		TiXmlElement* pMaxParticles = pRoot->FirstChildElement("MaxParticles");
		temp = pMaxParticles->GetText();
		weather.MaxParticles = atoi(temp.c_str());

		TiXmlElement* pSize = pRoot->FirstChildElement("Size");
		temp = pSize->GetText();
		weather.fSize = (float)atof(temp.c_str());

		TiXmlElement* pLife = pRoot->FirstChildElement("MaxLife");
		temp = pLife->GetText();
		weather.MaxLife = (float)atof(temp.c_str());

		TiXmlElement* pSpawnWidth = pRoot->FirstChildElement("SpawnWidth");
		temp = pSpawnWidth->GetText();
		weather.SpawnWidth = (float)atof(temp.c_str());

		TiXmlElement* pSpawnHeight = pRoot->FirstChildElement("SpawnHeight");
		temp = pSpawnHeight->GetText();
		weather.SpawnHeight = (float)atof(temp.c_str());

		TiXmlElement* pScaleStart = pRoot->FirstChildElement("ScaleStart");
		temp = pScaleStart->GetText();
		weather.ScaleStart = (float)atof(temp.c_str());

		TiXmlElement* pScaleEnd = pRoot->FirstChildElement("ScaleEnd");
		temp = pScaleEnd->GetText();
		weather.ScaleEnd = (float)atof(temp.c_str());

		TiXmlElement* pRotation = pRoot->FirstChildElement("Rotation");
		temp = pRotation->GetText();
		weather.Rotation = (float)atof(temp.c_str());

		TiXmlElement* pMinVelX = pRoot->FirstChildElement("MinVelX");
		temp = pMinVelX->GetText();
		weather.MinVelX = (float)atof(temp.c_str());

		TiXmlElement* pMaxVelX = pRoot->FirstChildElement("MaxVelX");
		temp = pMaxVelX->GetText();
		weather.MaxVelX = (float)atof(temp.c_str());

		TiXmlElement* pMinVelY = pRoot->FirstChildElement("MinVelY");
		temp = pMinVelY->GetText();
		weather.MinVelY = (float)atof(temp.c_str());

		TiXmlElement* pMaxVelY = pRoot->FirstChildElement("MaxVelY");
		temp = pMaxVelY->GetText();
		weather.MaxVelY = (float)atof(temp.c_str());




		TiXmlElement* pStartColorA = pRoot->FirstChildElement("StartColorA");
		temp = pStartColorA->GetText();
		weather.ColorStartA = (int)atof(temp.c_str());

		TiXmlElement* pStartColorR = pRoot->FirstChildElement("StartColorR");
		temp = pStartColorR->GetText();
		weather.ColorStartR = (int)atof(temp.c_str());

		TiXmlElement* pStartColorG = pRoot->FirstChildElement("StartColorG");
		temp = pStartColorG->GetText();
		weather.ColorStartG = (int)atof(temp.c_str());

		TiXmlElement* pStartColorB = pRoot->FirstChildElement("StartColorB");
		temp = pStartColorB->GetText();
		weather.ColorStartB = (int)atof(temp.c_str());



		TiXmlElement* pEndColorA = pRoot->FirstChildElement("EndColorA");
		temp = pEndColorA->GetText();
		weather.ColorEndA = (int)atof(temp.c_str());

		TiXmlElement* pEndColorR = pRoot->FirstChildElement("EndColorR");
		temp = pEndColorR->GetText();
		weather.ColorEndR = (int)atof(temp.c_str());

		TiXmlElement* pEndColorG = pRoot->FirstChildElement("EndColorG");
		temp = pEndColorG->GetText();
		weather.ColorEndG = (int)atof(temp.c_str());

		TiXmlElement* pEndColorB = pRoot->FirstChildElement("EndColorB");
		temp = pEndColorB->GetText();
		weather.ColorEndB = (int)atof(temp.c_str());

		TiXmlElement* pSource = pRoot->FirstChildElement("Source");
		temp = pSource->GetText();
		weather.Source = atoi(temp.c_str());

		TiXmlElement* pDest = pRoot->FirstChildElement("Dest");
		temp = pDest->GetText();
		weather.Destination = atoi(temp.c_str());

		TiXmlElement* pGravPosX = pRoot->FirstChildElement("GravPosX");
		temp = pGravPosX->GetText();
		weather.GravityPosX = (float)atoi(temp.c_str());

		TiXmlElement* pGravPosY = pRoot->FirstChildElement("GravPosY");
		temp = pGravPosY->GetText();
		weather.GravityPosY = (float)atoi(temp.c_str());

		TiXmlElement* pGravPower = pRoot->FirstChildElement("GravPower");
		temp = pGravPower->GetText();
		weather.GravityPower = (float)atoi(temp.c_str());

		TiXmlElement* pGravDistX = pRoot->FirstChildElement("GravDistX");
		temp = pGravDistX->GetText();
		weather.GravityDistX = (float)atoi(temp.c_str());

		TiXmlElement* pGravDistY = pRoot->FirstChildElement("GravDistY");
		temp = pGravDistY->GetText();
		weather.GravityDistY = (float)atoi(temp.c_str());

		weather.Init();
	}

	return true;
}
void CWeatherManager::ShutDown(void)
{
	weather.ShutDown();

	SetTypeOfWeather( 0 );
	SetTimeToWait( 0.0f );
	SetIsOn( false );
	SetTime( 0.0f );
}