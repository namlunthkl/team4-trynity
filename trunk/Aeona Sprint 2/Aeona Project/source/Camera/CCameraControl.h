#ifndef CCAMERACONTROL_H_
#define CCAMERACONTROL_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

class CCameraControl
{
private:
	D3DXMATRIX	m_D3DCamera;
	D3DXMATRIX	m_D3DProjection;
	D3DXVECTOR3	m_D3DPosition;
	float		m_D3DScale;

	int			m_nScreenWidth;
	int			m_nScreenHeight;

	float		m_fTime;
	float		m_fTimeToWait;
	
	bool		m_bKillCam;
	bool		m_bChargeCam;
	bool		m_bChange;
	bool		m_bStop;

	bool		m_bReleaseButton;
	
	CCameraControl(void);
	CCameraControl( const CCameraControl& ){}
	CCameraControl& operator=( const CCameraControl& ){}
	~CCameraControl(void);
public:
	static CCameraControl* GetInstance(void);
	D3DXMATRIX GetCamera(void)						{ return m_D3DCamera; }
	D3DXMATRIX GetProjection(void)					{ return m_D3DProjection; }
	float GetPositionX(void)						{ return m_D3DPosition.x; }
	float GetPositionY(void)						{ return m_D3DPosition.y; }
	float GetPositionZ(void)						{ return m_D3DPosition.z; }
	float GetScale(void)							{ return m_D3DScale; }
	float GetTime(void )							{ return m_fTime; }
	float GetTimeToWait(void )						{ return m_fTimeToWait; }
	bool GetKillCam(void)							{ return m_bKillCam; }
	bool GetChargeCam(void)							{ return m_bChargeCam; }
	bool GetChange(void)							{ return m_bChange; }
	bool GetStop(void )								{ return m_bStop; }
	bool GetReleaseButton(void)						{ return m_bReleaseButton; }


	void SetCamera( D3DXMATRIX D3DCamera )			{ m_D3DCamera = D3DCamera; }
	void SetProjection( D3DXMATRIX D3DProjection )	{ m_D3DProjection = D3DProjection; }
	void SetScale( float fScale )					{ m_D3DScale = fScale; }
	void SetPositionX( float x )					{ m_D3DPosition.x = x; }
	void SetPositionY( float y )					{ m_D3DPosition.y = y; }
	void SetPositionZ( float z )					{ m_D3DPosition.z = z; }
	void SetTime( float fTime )						{ m_fTime = fTime; }
	void SetTimeToWait( float fTimeToWait )			{ m_fTimeToWait = fTimeToWait; }
	void SetKillCam( bool bKillCam )				{ m_bKillCam = bKillCam; }
	void SetChargeCam( bool bChargeCam )			{ m_bChargeCam = bChargeCam; }
	void SetChange( bool bChange )					{ m_bChange = bChange; }
	void SetStop( bool bStop )						{ m_bStop = bStop; }
	void SetReleaseButton( bool bReleaseButton)		{ m_bReleaseButton = bReleaseButton; }

	void InitializeCamera( int nSreenWidth, int nScreenHeight, float StartX, float StartY );
	void Update( float fTime );
	void KillCamSequence( float fAmountOfTimeToPause );
	void ChargeCamSequence( float fChargeTime );
	D3DXMATRIX GetView(void);	
	void SetSpriteProjection( void );
	D3DXMATRIX GetOffset(void);
};
#endif