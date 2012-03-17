#include "StdAfx.h"
#include "WeatherManager.h"
#include "..\CGame.h"
#include "..\tinyxml\tinystr.h"
#include "..\tinyxml\tinyxml.h"
#include "..\Wrappers\SGD_Math.h"
#include "..\Light System\LightEngine.h"
#include "..\Game Objects\CPlayer.h"
#include "..\Post Process\CPostProcess.h"

CWeatherManager::CWeatherManager()
{
	SetTypeOfWeather( 0 );
	SetTimeToWait( 0.0f );
	SetIsOn( false );
	SetTime( 0.0f );

	m_nRainSound = AUDIO->SFXLoadSound("resource/sound/LightRain_Loop.wav");
	//m_nFireFliesSound = AUDIO->SFXLoadSound("resource/sound/FireFlies.wav");
	//m_nLeavesSound = AUDIO->SFXLoadSound("resource/sound/Leaves.wav");
	//m_nSnowSound = AUDIO->SFXLoadSound("resource/sound/Snow.wav");
	//m_nSandStormSound = AUDIO->SFXLoadSound("resource/sound/Sand_Storm.wav");
	//m_nEmberSound = AUDIO->SFXLoadSound("resource/sound/Ember.wav");
	//m_nFogSound = AUDIO->SFXLoadSound("resource/sound/Fog.wav");
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

void CWeatherManager::CheckRegion(void)
{
	const char* m_szRegion = CPlayer::GetInstance()->GetRegion();

	if( m_szRegion != NULL)
	{		
		if( strcmp(CPlayer::GetInstance()->GetRegion() ,"Forest" ) == 0 )
		{
			m_nCurrRegion = 0;
		}
		if( strcmp(CPlayer::GetInstance()->GetRegion(), "Snow" ) == 0 )
		{
			m_nCurrRegion = 1;
		}
		if( strcmp(CPlayer::GetInstance()->GetRegion(), "Desert" ) == 0 )
		{
			m_nCurrRegion = 2;
		}
		if( strcmp(CPlayer::GetInstance()->GetRegion(), "Volcano" ) == 0 )
		{
			m_nCurrRegion = 3;
		}
		if( strcmp(CPlayer::GetInstance()->GetRegion(), "Cave" ) == 0 )
		{
			m_nCurrRegion = 4;
		}
		if( strcmp(CPlayer::GetInstance()->GetRegion(), "Lake" ) == 0 )
		{
			m_nCurrRegion = 5;
		}
		if( strcmp(CPlayer::GetInstance()->GetRegion(), "Dungeon" ) == 0 )
		{
			m_nCurrRegion = 6;
		}
		if( strcmp(CPlayer::GetInstance()->GetRegion(), "DesertMaze" ) == 0 )
		{
			m_nCurrRegion = 7;
		}
	}
}
void CWeatherManager::LoadWeather(void)
{
	switch( GetTypeOfWeather() )
	{
	case CLEAR:
		{
			ShutDown();
		}
		break;	
	case RAIN:
		{
			ShutDown();
			LoadXML("Resource/data/Rain.xml");
			//AUDIO->SFXPlaySound( m_nRainSound, true );
			SetIsOn( true );
		}
		break;
	case FIREFLIES:
		{
			ShutDown();
			LoadXML("Resource/data/FireFlies.xml");
			//AUDIO->SFXPlaySound( m_nFireFliesSound, true );
			SetIsOn( true );
		}
		break;	
	case LEAVES:
		{
			ShutDown();
			LoadXML("Resource/data/FallingLeaves.xml");
			//AUDIO->SFXPlaySound( m_nLeavesSound, true );
			SetIsOn( true );
		}
		break;
	case SNOW:
		{
			ShutDown();
			LoadXML("Resource/data/Snow.xml");
			//AUDIO->SFXPlaySound( m_nSnowSound, true );
			SetIsOn( true );
		}
		break;
	case SAND:
		{
			ShutDown();
			LoadXML("Resource/data/SandStorm.xml");
			//AUDIO->SFXPlaySound( m_nSandStormSound, true );
			SetIsOn( true );
		}
		break;
	case EMBER:
		{
			ShutDown();
			LoadXML("Resource/data/Embers.xml");
			//AUDIO->SFXPlaySound( m_nEmberSound, true );
			SetIsOn( true );
		}
		break;
		//case FOG:
		//	{
		//		ShutDown();
		//		LoadXML("Resource/data/Fog.xml");
		//		AUDIO->SFXPlaySound( m_nFogSound, true );
		//		SetIsOn( true );
		//	}
		//	break;
	}
}
void CWeatherManager::SetWeatherPattern(void)
{
	if( GetTime() > GetTimeToWait())
	{
		switch( m_nCurrRegion )
		{
		case FOREST:
			{
				CPostProcess::GetInstance()->index = 5;
				int nForest = RandomInt( 1, 5 );
				switch( nForest )
				{
				case 1:
					{
						SetTypeOfWeather( CLEAR );
						SetTimeToWait( 10.0f );
						LoadWeather();
						SetTime( 0.0f );
					}
					break;
				case 2:
					{
						SetTypeOfWeather( RAIN );
						SetTimeToWait( 10.0f );
						LoadWeather();
						SetTime( 0.0f );
					}
					break;
				case 3:
					{
						SetTypeOfWeather( FIREFLIES );
						SetTimeToWait( 10.0f );
						LoadWeather();
						SetTime( 0.0f );
					}
					break;
				case 4:
					{
						SetTypeOfWeather( LEAVES );
						SetTimeToWait( 10.0f );
						LoadWeather();
						SetTime( 0.0f );
					}
					break;
				case 5:
					{
						SetTypeOfWeather( FOG );
						SetTimeToWait( 10.0f );
						LoadWeather();
						SetTime( 0.0f );
					}
					break;
				}
				break;
			}
		case MOUNTAIN:
			{
				CPostProcess::GetInstance()->index = 5;
				int nMountain = RandomInt( 1, 3 );
				switch( nMountain )
				{
				case 1:
					{
						SetTypeOfWeather( CLEAR );
						SetTimeToWait( 10.0f );
						LoadWeather();
						SetTime( 0.0f );
					}
					break;
				case 2:
					{
						SetTypeOfWeather( SNOW );
						SetTimeToWait( 10.0f );
						LoadWeather();
						SetTime( 0.0f );
					}
					break;
				case 3:
					{
						SetTypeOfWeather( FOG );
						SetTimeToWait( 10.0f );
						LoadWeather();
						SetTime( 0.0f );
					}
					break;
				}
			}
			break;
		case DESERT:
			{
				CPostProcess::GetInstance()->index = 5;
				SetTypeOfWeather( CLEAR );
				SetTimeToWait( 10.0f );
				LoadWeather();
				SetTime( 0.0f );
			}
			break;
		case DESERTMAZE:
			{
				CPostProcess::GetInstance()->index = 5;
				SetTypeOfWeather( SAND );
				SetTimeToWait( 10.0f );
				LoadWeather();
				SetTime( 0.0f );
			}
			break;
		case VOLCANO:
			{
				CPostProcess::GetInstance()->index = 4;
				SetTypeOfWeather( EMBER );
				SetTimeToWait( 10.0f );
				LoadWeather();
				SetTime( 0.0f );

			}
			break;
		case DUNGEON:
			{
				CPostProcess::GetInstance()->index = 4;
				SetTypeOfWeather( EMBER );
				SetTimeToWait( 10.0f );
				LoadWeather();
				SetTime( 0.0f );
			}
			break;
		case CAVE:
			{
				CPostProcess::GetInstance()->index = 2;
				int nCave = RandomInt( 1, 2 );
				switch( nCave )
				{
				case 1:
					{
						SetTypeOfWeather( FIREFLIES );
						SetTimeToWait( 10.0f );
						LoadWeather();
						SetTime( 0.0f );
					}
					break;
				case 2:
					{
						SetTypeOfWeather( FOG );
						SetTimeToWait( 10.0f );
						LoadWeather();
						SetTime( 0.0f );
					}
					break;
				}
			}
			break;
		case LAKE:
			{
				CPostProcess::GetInstance()->index = 5;
				int nLake = RandomInt( 1, 4 );
				switch( nLake )
				{
				case 1:
					{
						SetTypeOfWeather( CLEAR );
						SetTimeToWait( 10.0f );
						LoadWeather();
						SetTime( 0.0f );
					}
					break;
				case 2:
					{
						SetTypeOfWeather( RAIN );
						SetTimeToWait( 10.0f );
						LoadWeather();
						SetTime( 0.0f );
					}
					break;
				case 3:
					{
						SetTypeOfWeather( FIREFLIES );
						SetTimeToWait( 10.0f );
						LoadWeather();
						SetTime( 0.0f );
					}
					break;
				case 4:
					{
						SetTypeOfWeather( FOG );
						SetTimeToWait( 10.0f );
						LoadWeather();
						SetTime( 0.0f );
					}
					break;
				}
			}
			break;
		}
	}
}

void CWeatherManager::Update( float fTime )
{
	SetTime( GetTime() + fTime );

	CheckRegion();
	SetWeatherPattern();

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

	AUDIO->SFXStopSound( m_nRainSound );
	//AUDIO->SFXStopSound( m_nFireFliesSound );
	//AUDIO->SFXStopSound( m_nLeavesSound );
	//AUDIO->SFXStopSound( m_nSnowSound );
	//AUDIO->SFXStopSound( m_nSandStormSound );
	//AUDIO->SFXStopSound( m_nEmberSound );
	//AUDIO->SFXStopSound( m_nFogSound );

	SetIsOn( false );

}