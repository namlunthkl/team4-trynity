////////////////////////////////////////////////////////////////////////
//    File Name				:	"CBaseObject.h"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/25 - 8:10 PM
//    Purpose				:	Class that inherits from IBaseInterface
//								and contains all the functionality that
//								is common to all game objects
////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef C_BASE_OBJECT_H_
#define C_BASE_OBJECT_H_

// Parent class
#include "IBaseInterface.h"
// For animations
#include "../Animation/CAnimationPlayer.h"
// For event handling
#include "../Messaging/IListener.h"

// CBaseObject
// All game objects will inherit from this class
class CBaseObject : public IBaseInterface
{
	// Reference count
	unsigned int	m_uiRefCount;
	// Should this object update and be rendered?
	bool			m_bActive;
	// Is debug mode on?
	bool			m_bDebugMode;

	// Every object should have a position in the world
	PointD			m_ptPosition;
	// Every object should have a velocity and speed
	unsigned int	m_uiSpeed;
	tVector2D		m_vecVelocity;
	// Every object should have a size
	unsigned int	m_uiWidth;
	unsigned int	m_uiHeight;
	// Every object should have an image
	int				m_nImageID;

	// Every object can have multiple animations
	vector<CAnimationPlayer*> m_vpAnimations;
	int				m_anmCurrent;

public:
	// Constructor
	CBaseObject(double dPositionX = 0, double dPositionY = 0, unsigned int uiSpeed = 0U,
		int nImageID = -1, unsigned int uiWidth = 0U, unsigned int uiHeight = 0, bool bActive = false);

	// Common routines
	virtual void Update(float fElapsedTime);
	virtual void Render(void);
	virtual RectD GetCollisionRect(void) const;
	virtual bool CheckCollision(IBaseInterface* pObject);

	virtual inline unsigned int GetType(void) const { return TYPE_OBJ_BASE; }

	// Add and release references
	virtual void AddRef(void);
	virtual void Release(void);

	// Destructor
	virtual ~CBaseObject(void);

	// Accessors
	inline unsigned int		GetRefCount			(void)	const	{ return m_uiRefCount; }
	inline bool				IsActive			(void)	const	{ return m_bActive; }
	inline PointD			GetPosition			(void)	const	{ return m_ptPosition; }
	inline double			GetPosX				(void)	const	{ return m_ptPosition.x; }
	inline double			GetPosY				(void)	const	{ return m_ptPosition.y; }
	inline unsigned int		GetSpeed			(void)	const	{ return m_uiSpeed; }
	inline tVector2D		GetVelocity			(void)	const	{ return m_vecVelocity; }
	inline float			GetVelX				(void)	const	{ return m_vecVelocity.fX; }
	inline float			GetVelY				(void)	const	{ return m_vecVelocity.fY; }
	inline int				GetImageID			(void)	const	{ return m_nImageID; }
	inline unsigned int		GetWidth			(void)	const	{ return m_uiWidth; }
	inline unsigned int		GetHeight			(void)	const	{ return m_uiHeight; }
	inline int				GetCurrentAnimation (void)	const	{ return m_anmCurrent; }
	CAnimationPlayer*	GetAnimationPlayer	(unsigned int uiAnmIndex ) const;

	// Mutators
	inline void Activate		(void)						{ m_bActive = true; }
	inline void Deactivate		(void)						{ m_bActive = false; }
	inline void SetPosX			(double lPosX)				{ m_ptPosition.x = lPosX; }
	inline void SetPosY			(double lPosY)				{ m_ptPosition.y = lPosY; }
	inline void SetSpeed		(unsigned int uiSpeed)		{ m_uiSpeed = uiSpeed; }
	inline void SetVelX			(float fVelX)				{ m_vecVelocity.fX = fVelX; }
	inline void SetVelY			(float fVelY)				{ m_vecVelocity.fY = fVelY; }
	inline void SetImageID		(int nImageID)				{ m_nImageID = nImageID; }
	inline void SetWidth		(unsigned int uiWidth)		{ m_uiWidth = uiWidth; }
	inline void SetHeight		(unsigned int uiHeight)		{ m_uiHeight = uiHeight; }

	void SetCurrentAnimation	(int anmCurrent);
	void PushAnimationPlayer	(CAnimationPlayer* pAnimation);
	bool PopAnimationPlayer		(void);
};

#endif // C_BASE_OBJECT_H_