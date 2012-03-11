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
	Point			m_ptAnchor;
	// Every object should have a velocity and speed
	unsigned int	m_uiSpeed;
	tVector2D		m_vecVelocity;

	//Bern Added This
	tVector2D		m_vecPrevVelocity;
	//
	
	// Every object should have a size
	unsigned int	m_uiWidth;
	unsigned int	m_uiHeight;
	// Every object should have an image
	int				m_nImageID;

	// Every object can have multiple animations
	vector<CAnimationPlayer*> m_vpAnimations;
	int				m_anmCurrent;

	//Bern Added This
	int				m_anmPrevious;
	//

public:

	//	Phil's derp Bestiary - this actually relates to the Y-offset in Phil's sprite sheet.
	//	For example, the Larva is the first sprite, so simply set my enemy's frames at 0*192
	//	offsetted downward.
	//	The second enemy, will be offsetted on the Y by 1*192.  The third enemy would be
	//	offsetted by 2*192 down on the spritesheet.  I suck and only understand simple things!
	enum { BEVAIOR_0_NULL = 0, BEHAVIOR_LARVA = 1 };
	unsigned int m_uiEnemyBehavior;	//	to get Phil's AI and rendering work properly, because he's a stoopid, derpf!1
	unsigned int m_uiMiniState;		//	Phil's mini-state machine
	unsigned int m_uiPhilDirection;	//	Phil's object direction...only matters on enemies.
	DWORD philEnemyColor;			//	Phil's color so we can change da coluh' n shiiiet.
	bool		m_bWalkCycle;
	bool        m_bDying;
	bool		m_bTrulyDead;
	float       m_fDeathAnim;



	// Constructor
	CBaseObject(double dPositionX = 0, double dPositionY = 0, unsigned int uiSpeed = 0U,
		int nImageID = -1, unsigned int uiWidth = 0U, unsigned int uiHeight = 0, bool bActive = false);

	// Common routines
	virtual void Update(float fElapsedTime);
	virtual void Render(void);
	virtual void Input(void);
	virtual RectD GetCollisionRect(void);
	virtual bool CheckCollision(IBaseInterface* pObject);

	virtual inline unsigned int GetType(void) const { return TYPE_OBJ_BASE; }
	virtual Point	GetAnchorPoint(void);
	
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
	//Bern added this
	inline float			GetPrevVelX				(void)	const	{ return m_vecPrevVelocity.fX; }
	inline float			GetPrevVelY				(void)	const	{ return m_vecPrevVelocity.fY; }
	// to here.
	inline int				GetImageID			(void)	const	{ return m_nImageID; }
	inline unsigned int		GetWidth			(void)	const	{ return m_uiWidth; }
	inline unsigned int		GetHeight			(void)	const	{ return m_uiHeight; }
	inline int				GetCurrentAnimation (void)	const	{ return m_anmCurrent; }
	//Bern added this
	inline int				GetPreviousAnimation (void)	const	{ return m_anmPrevious; }
	// to here.
	CAnimationPlayer*		GetAnimationPlayer	(unsigned int uiAnmIndex ) const;

	// Mutators
	inline void Activate		(void)						{ m_bActive = true; }
	inline void Deactivate		(void)						{ m_bActive = false; }
	inline void SetPosX			(double dPosX)				{ m_ptPosition.x = dPosX; }
	inline void SetPosY			(double dPosY)				{ m_ptPosition.y = dPosY; }
	inline void SetSpeed		(unsigned int uiSpeed)		{ m_uiSpeed = uiSpeed; }
	inline void SetVelX			(float fVelX)				{ m_vecVelocity.fX = fVelX; }
	inline void SetVelY			(float fVelY)				{ m_vecVelocity.fY = fVelY; }
	//Bern added this
	inline void SetPrevVelX			(float fVelX)				{ m_vecPrevVelocity.fX = fVelX; }
	inline void SetPrevVelY			(float fVelY)				{ m_vecPrevVelocity.fY = fVelY; }
	// to here.
	inline void SetImageID		(int nImageID)				{ m_nImageID = nImageID; }
	inline void SetWidth		(unsigned int uiWidth)		{ m_uiWidth = uiWidth; }
	inline void SetHeight		(unsigned int uiHeight)		{ m_uiHeight = uiHeight; }
	inline void SetDebugMode	(bool bDebugMode)			{ m_bDebugMode = bDebugMode; }

	void SetCurrentAnimation	(int anmCurrent);
	//	Bern added this
	void SetPreviousAnimation	(int anmPrevious);
	// to here.
	void PushAnimationPlayer	(CAnimationPlayer* pAnimation);
	bool PopAnimationPlayer		(void);
};

#endif // C_BASE_OBJECT_H_