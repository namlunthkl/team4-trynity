////////////////////////////////////////////////////////////////////////
//    File Name				:	"IBaseInterface.h"
//
//    Author Name			:	Bryan Schotanes
//    Creation Date			:	02/08/12 - 7:47 PM
//    Purpose				:	Contains the IBaseInterface
//
//    Last Updater Name		:   Daniel Lima
//    Last Update Date      :   02/25 - 8:00 PM
//    Last Update Notes     :   I cleaned up this interface so that
//								all the data members and more specific
//								functions are held by its child CBase
////////////////////////////////////////////////////////////////////////

// Standard header protection
#ifndef I_BASE_INTERFACE_H_
#define I_BASE_INTERFACE_H_

// Lean and Mean - Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN
// Windows.h - Has a lot of stuff we need for Windows applications
#include <Windows.h>

// IBaseInterface
// All game objects will inherit from this class
class IBaseInterface
{
public:
	enum Type { TYPE_OBJ_BASE, TYPE_CHAR_BASE, TYPE_CHAR_PLAYER, TYPE_CHAR_ENEMY, TYPE_CHAR_NPC, TYPE_CHAR_CHEST,
				TYPE_WEAPON_DAGGER, TYPE_WEAPON_SWORD, TYPE_WEAPON_HAMMER, TYPE_WEAPON_ARROW, TYPE_MAX };

	// Destructor
	virtual ~IBaseInterface(void) = 0 {}

	// Common routines
	virtual void Update(float fElapsedTime) = 0;
	virtual void Render(void) = 0;
	virtual void Input(void) = 0;
	virtual unsigned int GetType(void) const = 0;
	virtual RectD GetCollisionRect(void) = 0;
	virtual bool CheckCollision(IBaseInterface* pObject) = 0;

	// Add and release references
	virtual void AddRef(void) = 0;
	virtual void Release(void) = 0;
};

#endif // I_BASE_INTERFACE_H_