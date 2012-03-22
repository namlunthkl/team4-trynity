#ifndef WEATHERMANAGER_H_
#define WEATHERMANAGER_H_

#include "..\Particle Engine\Emitter.h"

enum WEATHER{ CLEAR, RAIN, FIREFLIES, LEAVES, SNOW, SAND, EMBER, FOG };
enum REGION { FOREST, MOUNTAIN, DESERT, VOLCANO, CAVE, LAKE, DUNGEON, DESERTMAZE, TOWN };

class CWeatherManager
{
private:
	Emitter weather;  
	bool m_bIsOn;
	float m_fTimeToWait;
	float m_fTime;
	short m_sTypeOfWeather;
	int m_nCurrRegion;

	// SOUND
	int m_nRainSound;
	int m_nEmberSound;
	int m_nSandStormSound;
	int m_nLeavesSound;
	int m_nSnowSound;

	// MUSIC
	int m_nTown;
	int m_nForest;
	int m_nMountain;
	int m_nLake;
	int m_nVolcano;
	int m_nDesert;

	CWeatherManager();
	CWeatherManager( const CWeatherManager& ){}
	CWeatherManager& operator=( const CWeatherManager& ){}
	~CWeatherManager();
public:
	static CWeatherManager* GetInstance(void);

	void SetIsOn( bool bOn )				{ m_bIsOn = bOn; }
	void SetTimeToWait( float fTimeToWait )	{ m_fTimeToWait = fTimeToWait; }
	void SetTime( float fTime )				{ m_fTime = fTime; }
	void SetTypeOfWeather( short sType )	{ m_sTypeOfWeather = sType; }
	
	Emitter* GetWeather(void)				{ return &weather; }
	bool GetIsOn(void)						{ return m_bIsOn; }
	float GetTimeToWait(void)				{ return m_fTimeToWait; }
	float GetTime(void)						{ return m_fTime; }
	short GetTypeOfWeather(void)			{ return m_sTypeOfWeather; }
	
	void CheckRegion(void);
	void LoadWeather(void);
	void SetWeatherPattern(void);

	void Update( float fTime );
	void Render();
	bool LoadXML(const char* szXMLFileName);
	void ShutDown(void);
	void StopAllSounds(void);
};
#endif