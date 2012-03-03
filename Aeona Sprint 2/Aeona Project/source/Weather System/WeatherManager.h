#ifndef WEATHERMANAGER_H_
#define WEATHERMANAGER_H_

#include "..\Particle Engine\Emitter.h"

enum WEATHER{ RAIN = 1, SNOW, LEAVES, SAND, EMBER, RAINSNOW };

class CWeatherManager
{
private:
	Emitter weather;  
	Emitter weather2;
	bool m_bIsOn;
	float m_fTimeToWait;
	float m_fTime;
	short m_usTypeOfWeather;

	CWeatherManager();
	CWeatherManager( const CWeatherManager& ){}
	CWeatherManager& operator=( const CWeatherManager& ){}
	~CWeatherManager();
public:
	static CWeatherManager* GetInstance(void);

	
	void SetIsOn( bool bOn )				{ m_bIsOn = bOn; }
	void SetTimeToWait( float fTimeToWait )	{ m_fTimeToWait = fTimeToWait; }
	void SetTime( float fTime )				{ m_fTime = fTime; }
	void SetTypeOfWeather( short sType )	{ m_usTypeOfWeather = sType; }
	
	Emitter* GetWeather(void)				{ return &weather; }
	Emitter* GetWeather2(void)				{ return &weather2; }
	bool GetIsOn(void)						{ return m_bIsOn; }
	float GetTimeToWait(void)				{ return m_fTimeToWait; }
	float GetTime(void)						{ return m_fTime; }
	short GetTypeOfWeather(void)			{ return m_usTypeOfWeather; }

	void LoadWeather( short TypeOfWeather);
	void Update( float fTime );
	void Render();
	bool LoadXML(const char* szXMLFileName);
	bool LoadXML2(const char* szXMLFileName);
	void ShutDown(void);
};
#endif