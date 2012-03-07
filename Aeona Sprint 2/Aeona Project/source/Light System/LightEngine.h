#ifndef LIGHTENGINE_H_
#define LIGHTENGINE_H_

class LightEngine
{
private:		
	// AMBIENT LIGHT
	float m_fAmbientAlpha;
	float m_fAmbientRed;
	float m_fAmbientGeen;
	float m_fAmbientBlue;
	
	// PLAYER POINT LIGHT
	bool  m_bPlayerPointLight;
	float m_fPlayerPointAlpha;
	float m_fPlayerPointRed;
	float m_fPlayerPointGeen;
	float m_fPlayerPointBlue;
	float m_fPlayerPointPosX;
	float m_fPlayerPointPosY;

	// ITEM 1 POINT LIGHT
	bool  m_bItem1PointLight;
	float m_fItem1PointAlpha;
	float m_fItem1PointRed;
	float m_fItem1PointGeen;
	float m_fItem1PointBlue;
	float m_fItem1PointPosX;
	float m_fItem1PointPosY;

	LightEngine(void);
	LightEngine(const LightEngine&){}
	LightEngine& operator=(const LightEngine&){}
	~LightEngine(void);

public:
	static LightEngine* GetInstance(void);

	//AMBIENT LIGHT
	void SetAmbientAlpha( float fAmbientAlpha )		{ m_fAmbientAlpha = fAmbientAlpha; }
	void SetAmbientRed( float fAmbientRed )			{ m_fAmbientRed = fAmbientRed; }
	void SetAmbientGreen( float fAmbientGreen )		{ m_fAmbientGeen = fAmbientGreen; }
	void SetAmbientBlue(float fAmbientBlue )		{ m_fAmbientBlue = fAmbientBlue; }
	float GetAmbientAlpha(void)						{ return m_fAmbientAlpha; }
	float GetAmbientRed(void)						{ return m_fAmbientRed; }
	float GetAmbientGreen(void)						{ return m_fAmbientGeen; }
	float GetAmbientBlue(void)						{ return m_fAmbientBlue; }

	//PLAYER POINT LIGHT
	void SetPlayerPointLight( bool bPlayerPoint)	{ m_bPlayerPointLight = bPlayerPoint; }
	void SetPlayerPointAlpha( float fPointAlpha )	{ m_fPlayerPointAlpha = fPointAlpha; }
	void SetPlayerPointRed( float fPointRed )		{ m_fPlayerPointRed = fPointRed; }
	void SetPlayerPointGreen( float fPointGreen )	{ m_fPlayerPointGeen = fPointGreen; }
	void SetPlayerPointBlue( float fPointBlue )		{ m_fPlayerPointBlue = fPointBlue; }
	void SetPlayerPointPosX( float fPlayerPosX )	{ m_fPlayerPointPosX = fPlayerPosX; }
	void SetPlayerPointPosY( float fPlayerPosY )	{ m_fPlayerPointPosY = fPlayerPosY; }
	bool  GetPlayerPointLight(void)					{ return m_bPlayerPointLight; }
	float GetPlayerPointAlpha(void)					{ return m_fPlayerPointAlpha; }
	float GetPlayerPointRed(void)					{ return m_fPlayerPointRed; }
	float GetPlayerPointGreen(void)					{ return m_fPlayerPointGeen; }
	float GetPlayerPointBlue(void)					{ return m_fPlayerPointBlue; }
	float GetPlayerPointPosX(void)					{ return m_fPlayerPointPosX; }
	float GetPlayerPointPosY(void)					{ return m_fPlayerPointPosY; }

	//ITEM1 POINT LIGHT
	void SetItem1PointLight( bool bItem1Point)		{ m_bItem1PointLight = bItem1Point; }
	void SetItem1PointAlpha( float fPointAlpha )	{ m_fItem1PointAlpha = fPointAlpha; }
	void SetItem1PointRed( float fPointRed )		{ m_fItem1PointRed = fPointRed; }
	void SetItem1PointGreen( float fPointGreen )	{ m_fItem1PointGeen = fPointGreen; }
	void SetItem1PointBlue( float fPointBlue )		{ m_fItem1PointBlue = fPointBlue; }
	void SetItem1PointPosX( float fItem1PosX )		{ m_fItem1PointPosX = fItem1PosX; }
	void SetItem1PointPosY( float fItem1PosY )		{ m_fItem1PointPosY = fItem1PosY; }
	bool  GetItem1PointLight(void)					{ return m_bItem1PointLight; }
	float GetItem1PointAlpha(void)					{ return m_fItem1PointAlpha; }
	float GetItem1PointRed(void)					{ return m_fItem1PointRed; }
	float GetItem1PointGreen(void)					{ return m_fItem1PointGeen; }
	float GetItem1PointBlue(void)					{ return m_fItem1PointBlue; }
	float GetItem1PointPosX(void)					{ return m_fItem1PointPosX; }
	float GetItem1PointPosY(void)					{ return m_fItem1PointPosY; }






	void Initialize( void );
	void Update( void );
	void Input( void );
	void ShutDown( void );

	void SetPlayerPointPos( float fPosX, float fPosY );
	void Morning( void );
	void Day( void );
	void Evening( void );
	void Night( void );

	void Rain( void );
	void Snow( void );
	void Leaves( void );
	void Sand( void );
	void Ember( void );
	void FireFlies( void );
};

#endif
