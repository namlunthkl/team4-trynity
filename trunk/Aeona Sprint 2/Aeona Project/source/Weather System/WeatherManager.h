#ifndef WEATHERMANAGER_H_
#define WEATHERMANAGER_H_

#include "..\Particle Engine\Emitter.h"

enum WEATHER{ RAIN = 1, SNOW, LEAVES, SAND, EMBER, FIREFLIES };

class CWeatherManager
{
private:
	Emitter weather;  
	bool m_bIsOn;
	float m_fTimeToWait;
	float m_fTime;
	short m_sTypeOfWeather;

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

	void LoadWeather( short TypeOfWeather);
	void Update( float fTime );
	void Render();
	bool LoadXML(const char* szXMLFileName);
	void ShutDown(void);
};
#endif