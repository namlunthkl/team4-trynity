///////////////////////////////////////////////////////////////////
//	File Name	:	"CBase.h"
//
//	Author Name	:	David Brown
//
//	Purpose		:	To contain all related data and functionality
//					for our game objects.
///////////////////////////////////////////////////////////////////
#pragma once
#include "IBaseInterface.h"

class CBase : public IBaseInterface
{
private:
	unsigned int m_uiRefCount; // how many objs have a ptr to me?

	//	Position
	float m_nPosX;
	float m_nPosY;

	//	Velocity
	float	m_nVelX;
	float	m_nVelY;

	//	Image ID
	int	m_nImageID;

	// Width / Height
	int m_nWidth;
	int m_nHeight;

protected:
	enum ObjectType{OBJECT_BALL = 0, OBJECT_ASTEROID, OBJECT_PADDLE, OBJECT_POWERUP };
	int m_nType;

public:
	CBase(void);
	virtual ~CBase(void);

	///////////////////////////////////////////////
	//	Function:	Accessors
	//
	//	Purpose	:	To get the specified type.
	///////////////////////////////////////////////
	float GetPosX(void)		{ return m_nPosX; }
	float GetPosY(void)		{ return m_nPosY; }
	float GetVelX(void)		{ return m_nVelX; }
	float GetVelY(void)		{ return m_nVelY; }
	int GetImageID(void)	{ return m_nImageID; }
	int GetWidth(void)		{ return m_nWidth; }
	int GetHeight(void)		{ return m_nHeight; }
	int GetType(void)		{ return m_nType; }
	
	///////////////////////////////////////////////
	//	Function:	Modifiers
	//
	//	Purpose	:	To set the specified type.
	///////////////////////////////////////////////
	void SetPosX(float nPosX)			{ m_nPosX = nPosX; }
	void SetPosY(float nPosY)			{ m_nPosY = nPosY; }
	void SetVelX(float nVelX)			{ m_nVelX = nVelX; }
	void SetVelY(float nVelY)			{ m_nVelY = nVelY; }
	void SetImageID(int nImageID)	{ m_nImageID = nImageID; }
	void SetWidth(int nWidth)		{  m_nWidth = nWidth; }
	void SetHeight(int nHeight)		{  m_nHeight = nHeight; }

	//	3 things a game does every frame
	//	Input
	//	Update
	//	NOTE:  Do Input at the top of Update
	virtual void Update(float fElapsedTime);

	//	Draw
	virtual void Render(void);

	virtual RECT GetRect();

	void AddRef(void)
	{
		m_uiRefCount++;
	}

	void Release(void)
	{
		m_uiRefCount--;

		if (m_uiRefCount == 0)
			delete this;
	}

	virtual bool CheckCollision(IBaseInterface * pBase );
};