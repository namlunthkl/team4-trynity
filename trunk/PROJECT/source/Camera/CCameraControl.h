////////////////////////////////////////////////////////////////////////
//    File Name    : "CCameraControl.h"
//
//    Author Name   : Ari Bodaghee
//    Creation Date   : 02/08/12 - 7:47 PM
//    Purpose    : Contains the CCameraControl
////////////////////////////////////////////////////////////////////////
#ifndef CCAMERACONTROL_H_
#define CCAMERACONTROL_H_

class CCameraControl
{
private:
	float		m_fTime;
	float		m_fYMod;
	float		m_fTimeToWait;
	
	bool		m_bKillCam;
	bool		m_bChargeCam;
	bool		m_bChange;
	bool		m_bStop;
	
	D3DXMATRIX	m_D3DCamera;
	D3DXMATRIX	m_D3DProjection;
	
	CCameraControl(void);
	CCameraControl( const CCameraControl& );
	CCameraControl& operator=( const CCameraControl& );
	~CCameraControl(void);

public:
	static CCameraControl* GetInstance( void );
	
	float GetTime(void )							{ return m_fTime; }
	float GetTimeToWait(void )						{ return m_fTimeToWait; }
	float GetYMod(void)								{ return m_fYMod; }
	bool GetKillCam(void)							{ return m_bKillCam; }
	bool GetChargeCam(void)							{ return m_bChargeCam; }
	bool GetChange(void)							{ return m_bChange; }
	bool GetStop(void )								{ return m_bStop; }
	D3DXMATRIX GetCamera(void)						{ return m_D3DCamera; }
	D3DXMATRIX GetProjection(void)					{ return m_D3DProjection; }

	void SetTime( float fTime )						{ m_fTime = fTime; }
	void SetTimeToWait( float fTimeToWait )			{ m_fTimeToWait = fTimeToWait; }
	void SetYMod( float fYMod )						{ m_fYMod = fYMod; }
	void SetKillCam( bool bKillCam )				{ m_bKillCam = bKillCam; }
	void SetChargeCam( bool bChargeCam )			{ m_bChargeCam = bChargeCam; }
	void SetChange( bool bChange )					{ m_bChange = bChange; }
	void SetStop( bool bStop )						{ m_bStop = bStop; }
	void SetCamera( D3DXMATRIX D3DCamera )			{ m_D3DCamera = D3DCamera; }
	void SetProjection( D3DXMATRIX D3DProjection )	{ m_D3DProjection = D3DProjection; }

	void SetCameraPositionX( float x )				{ m_D3DCamera._41 = x; }
	void SetCameraPositionY( float y )				{ m_D3DCamera._42 = y; }
	void SetCameraPositionZ( float z )				{ m_D3DCamera._43 = z; }

	void InitializeCamera();
	void Update( float fTime );
	void KillCamSequence( float fAmountOfTimeToPause );
	void ChargeCamSequence( float fChargeTime );
};
#endif