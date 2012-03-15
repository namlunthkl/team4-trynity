////////////////////////////////////////////////////////////////////////
//    File Name				:	"CMap.cpp"
//
//    Author Name			:	Daniel Lima
//    Creation Date			:	02/06 - 9:40 PM
//    Purpose				:	To contain all information needed to
//								render a map to the screen and functions
//								to load a map from an xml file exported
//								from the tile editor
////////////////////////////////////////////////////////////////////////

// Precompiled header
#include "StdAfx.h"

// Include header file
#include "CMap.h"


#include "../tinyxml/tinyxml.h"
#include "../Messaging/CStringTable.h"
#include "CWorldEngine.h"

#include "../Game Objects/IBaseInterface.h"
#include "../Messaging/CEventSystem.h"

#include "../Input Manager/CInputManager.h"
#include "../States/CGameplayState.h"
#include "../Camera/CCameraControl.h"
#include "../Messaging/CMessageSystem.h"

#define GAMEPLAY CGameplayState::GetInstance()
#define CAMERA CCameraControl::GetInstance()

// Constructor
// Sets all parameters to 0/NULL values
CMap::CMap(void)
{
	SetPosX(0);
	SetPosY(0);
	SetWidth(0);
	SetHeight(0);
	SetTileset(NULL);
	m_uiObjectLayer = 0;
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Load map information from a xml file
//	Parameters	:	Location of the xml file to load
//	Return		:	False if load failed, true if succeeded
////////////////////////////////////////////////////////////////////////
bool CMap::Load(char const * const szFilename, CStringTable* pStringTable)
{
	// Create XML doc
	TiXmlDocument doc;
	// Try to load the file, and if it fails, return false
	if(!doc.LoadFile(szFilename))
		return false;

	// Get a pointer to the root
	TiXmlElement* pRoot = doc.RootElement();
	// If that wasn't created properly too, get out of here
	if(!pRoot)
		return false;


	// Get the ids of the possible strings we'll have to check for
	// so we don't need to do strcmps
	unsigned char ucEnemyID = pStringTable->LoadStringOnTable("Enemy");
	unsigned char ucChestID = pStringTable->LoadStringOnTable("Chest");

	// Temporary variables to store the data we'll read
	const char* szTileset = "";
	int nWidth = 0;
	int nHeight = 0;
	int nPosX = 0;
	int nPosY = 0;
	int nObjectLayer = 0;
	int nTileType = 0;
	int nTilePosX = 0;
	int nTilePosY = 0;
	const char* szEvent = "";

	// Get the Tileset ID
	szTileset = pRoot->Attribute("tileset");
	unsigned char ucTilesetID = pStringTable->LoadStringOnTable(szTileset);
	CTileset* pTileset = CWorldEngine::GetInstance()->GetTileset(ucTilesetID);
	SetTileset(pTileset);

	// Get the Map Element
	TiXmlElement* pMap = pRoot->FirstChildElement("Map");
	// If it failed return false...
	if(!pMap)
		return false;

	// Read all the data from the tileset file
	pMap->Attribute("width", &nWidth);
	pMap->Attribute("height", &nHeight);
	pMap->Attribute("posX", &nPosX);
	pMap->Attribute("posY", &nPosY);
	pMap->Attribute("objectlayer", &nObjectLayer);

	// Set the map members
	SetWidth(nWidth);
	SetHeight(nHeight);
	SetPosX(nPosX);
	SetPosY(nPosY);
	m_uiObjectLayer = nObjectLayer;

	// First Layer in the map
	TiXmlElement* pLayer = pMap->FirstChildElement("Layer");
	// If it failed return false...
	if(!pLayer)
		return false;

	// Load all the layers
	while(pLayer)
	{
		// Create the layer
		CLayer tempLayer;

		// Get the Tile element
		TiXmlElement* pTile = pLayer->FirstChildElement("Tile");
		unsigned int TileIndex = 0;

		// Load all the tiles
		while(pTile)
		{
			// Read all the data for the tile here
			pTile->Attribute("PosX", &nTilePosX);
			pTile->Attribute("PosY", &nTilePosY);
			pTile->Attribute("Type", &nTileType);
			szEvent = pTile->Attribute("Event");

			// I like making weird code sometimes =D
			if(szEvent[0] == 'N')
				if(szEvent[1] == 'P')
					if(szEvent[2] == 'C')
						if(szEvent[3] == '.')
						{
							CMessageSystem::GetInstance()->SendMsg(new CCreateNPCMessage(szEvent + 4,
							GetPosX() + (TileIndex % GetWidth()) * GetTileset()->GetTileWidth(),
							GetPosY() + (TileIndex / GetHeight()) * GetTileset()->GetTileHeight()));
						}

			// Load the event in the string table and get its ID
			unsigned char ucEventID = pStringTable->LoadStringOnTable(szEvent);

			if(nTileType == 0)
			{
				if(ucEventID == ucEnemyID)
				{
					CMessageSystem::GetInstance()->SendMsg(new CCreateEnemyMessage(
						GetPosX() + (TileIndex % GetWidth()) * GetTileset()->GetTileWidth(),
						GetPosY() + (TileIndex / GetHeight()) * GetTileset()->GetTileHeight(),
						pStringTable->GetString(GetTileset()->GetID())));
					ucEventID = pStringTable->GetStringIndex("");
				}
				else if(ucEventID == ucChestID)
				{
					CMessageSystem::GetInstance()->SendMsg(new CCreateChestMessage(
						GetPosX() + (TileIndex % GetWidth()) * GetTileset()->GetTileWidth(),
						GetPosY() + (TileIndex / GetHeight()) * GetTileset()->GetTileHeight(),
						CCreateChestMessage::CHEST_POTION));
					ucEventID = pStringTable->GetStringIndex("");
				}
			}

			// Create the tile
			CTile tempTile((unsigned char)nTilePosX, (unsigned char)nTilePosY,
				(unsigned char)nTileType, ucEventID);

			// Push the tile to the layer
			tempLayer.PushTile(tempTile);

			// Move on to the next Tile (sibling)
			pTile = pTile->NextSiblingElement("Tile");
			TileIndex++;
		}

		// Push the layer to the list
		m_vLayers.push_back(tempLayer);

		// Move on to the next Layer (sibling)
		pLayer = pLayer->NextSiblingElement("Layer");
	}

	GAME->RenderLoadingScreen( GAME->IncrementAndReturnAmountLoaded(), 0);

	// Success!
	return true;
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Draw the map's tiles that are inside the window's
//					space
////////////////////////////////////////////////////////////////////////
void CMap::RenderLayer(unsigned int uiIndexLayer, int nCullingMode)
{
	// Indexes we'll need for looping
	unsigned int uiIndexWidth	= 0;		// Loop through the map width / columns
	unsigned int uiIndexHeight	= 0;		// Loop through the map height / lines
	unsigned int uiIndexTile	= 0;		// Keep track of the tile we're looking in the array

	// For each layer, loop through all the tiles
	for(uiIndexTile = 0; uiIndexTile < m_vLayers[uiIndexLayer].GetSize(); ++uiIndexTile)
	{
		// Get a pointer to the current tile - for better readability
		CTile* tileCurrent = m_vLayers[uiIndexLayer].GetTile(uiIndexTile);

		// Get position to draw;
		int nTileWorldPosX = GetPosX() + GetTileset()->GetTileWidth() * uiIndexWidth;
		int nTileWorldPosY = GetPosY() + GetTileset()->GetTileHeight() * uiIndexHeight;

		bool bRender = false;
		switch(nCullingMode)
		{
		case CULLING_NONE:
			bRender = true;
			break;
		case CULLING_HALF_SCREEN:
			if(nTileWorldPosX  + CAMERA->GetPositionX() > 0 && nTileWorldPosX + GetTileset()->GetTileWidth()  + CAMERA->GetPositionX() < GAME->GetScreenWidth()
				&& nTileWorldPosY + CAMERA->GetPositionY() > 0 && nTileWorldPosY+ GetTileset()->GetTileHeight()  + CAMERA->GetPositionY() < GAME->GetScreenHeight())
				bRender = true;
			break;
		case CULLING_SCREEN:
			if(nTileWorldPosX + GetTileset()->GetTileWidth() + CAMERA->GetPositionX() >= 0 && (nTileWorldPosX + CAMERA->GetPositionX()) <= GAME->GetScreenWidth()
				&& nTileWorldPosY + GetTileset()->GetTileHeight() + CAMERA->GetPositionY() >= 0 && (nTileWorldPosY + CAMERA->GetPositionY()) <= GAME->GetScreenHeight())
				bRender = true;
			break;
		}

		if(bRender)
		{
			// Get the source rect of that tile
			RECT rectSource = GetTileSourceRect(tileCurrent);

			// Draw the tile using texture manager
			TEX_MNG->Draw(GetTileset()->GetImageID(), nTileWorldPosX, nTileWorldPosY, 1.0f, 1.0f, &rectSource);
		}

		// Since we're reading line by line, from left to right, we need
		// to increase the width index every time we draw a tile
		++uiIndexWidth;

		// Once we reach the end of a line, though, we need to reset the
		// width index and increase the height index
		if((int)uiIndexWidth >= GetWidth())
		{
			// Reset width index
			uiIndexWidth = 0;

			// Increase height index
			++uiIndexHeight;
		}
	}
}

void CMap::RenderFirstLayers(int nCullingMode)
{
	if(m_uiObjectLayer >= m_vLayers.size()) return;

	unsigned int uiIndexLayer	= 0;		// Loop through layers
	
	// First loop through all the layers
	for(uiIndexLayer = 0; uiIndexLayer <= m_uiObjectLayer; ++uiIndexLayer)
	{
		// Call render on those
		RenderLayer(uiIndexLayer, nCullingMode);
	}
}
void CMap::RenderLastLayers(int nCullingMode)
{
	unsigned int uiIndexLayer	= 0;		// Loop through layers
	
	// First loop through all the layers
	for(uiIndexLayer = m_uiObjectLayer + 1; uiIndexLayer < m_vLayers.size(); ++uiIndexLayer)
	{
		// Call render on those
		RenderLayer(uiIndexLayer, nCullingMode);
	}
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Check collisions against all tiles on screen
//	Parameters	:	pBase - Object that we're checking collisions with
//	Return		:	True if collided, false otherwise
////////////////////////////////////////////////////////////////////////
bool CMap::CheckCollisions(IBaseInterface* pBase, CStringTable* pStringTable,
	RectD* CollisionRect, unsigned int uiObjType)
{
	bool bCollided = false;					// Basically what will be returned
	CBaseObject* pObject = nullptr;
	RectD ObjCollisionRect;
	unsigned int ObjType;
	if(pBase)
	{
		pObject = (CBaseObject*)pBase;
		ObjCollisionRect = pObject->GetCollisionRect();
		ObjType = pObject->GetType();
	}
	else
	{
		ObjCollisionRect = *CollisionRect;
		ObjType = uiObjType;
	}

	// Indexes we'll need for looping
	unsigned int uiIndexLayer	= 0;		// Loop through layers
	unsigned int uiIndexWidth	= 0;		// Loop through the map width / columns
	unsigned int uiIndexHeight	= 0;		// Loop through the map height / lines
	unsigned int uiIndexTile	= 0;		// Keep track of the tile we're looking in the array

	// Layer 0
	// Loop through all the tiles, checking collisions
	// Object Layer
	// Loop through all the tiles, checking events
	unsigned char cNullEventID = pStringTable->GetStringIndex("");
	unsigned char cNullEventID2 = pStringTable->GetStringIndex("none");

	for(int i=0; i < 2; ++i)
	{
		for(uiIndexTile = 0; uiIndexTile < m_vLayers[uiIndexLayer].GetSize(); ++uiIndexTile)
		{
			// Get a pointer to the current tile - for better readability
			CTile* tileCurrent = m_vLayers[uiIndexLayer].GetTile(uiIndexTile);
			
			// Get the tile collision rect
			RECT rectTileCollision;
			rectTileCollision.left = GetPosX() + GetTileset()->GetTileWidth() * uiIndexWidth;
			rectTileCollision.top = GetPosY() + GetTileset()->GetTileHeight() * uiIndexHeight;
			rectTileCollision.right = rectTileCollision.left + GetTileset()->GetTileWidth();
			rectTileCollision.bottom = rectTileCollision.top + GetTileset()->GetTileHeight();

			RECT rectIntersection;

			// If Base's collision rect intersects with this tile's collision rect...
			if(IntersectRect(&rectIntersection, &rectTileCollision, &ObjCollisionRect.GetWindowsRECT())) 
			{
				// If we're looping through layer 0, collision layer, handle collision
				if(uiIndexLayer != m_uiObjectLayer)
				{
					// ...we know that pBase collided with this tile
					bCollided = true;

					double dRectWidth = rectIntersection.right - rectIntersection.left;
					double dRectHeight = rectIntersection.bottom - rectIntersection.top;
					double dAnmHeight = ObjCollisionRect.bottom - ObjCollisionRect.top;
					double dAnmWidth = ObjCollisionRect.right - ObjCollisionRect.left;
					double dTilePosX = (rectTileCollision.right + rectTileCollision.left) / 2;
					double dTilePosY = (rectTileCollision.bottom + rectTileCollision.top) / 2;

					// Check if the tile is collidable
					if(TestBit(tileCurrent->GetInfo(), BIT_TILE_COLLISION))
					{
						if(pObject)
						{
							if(dRectWidth > dRectHeight)
							{
								// Top/Down Collision
								if(ObjCollisionRect.top < rectTileCollision.top)
								{
									if(pObject->GetVelY() > 0)
										pObject->SetPosY(rectIntersection.top + pObject->GetAnchorPoint().y - dAnmHeight);
								}
								else if(ObjCollisionRect.bottom > rectTileCollision.bottom)
								{
									if(pObject->GetVelY() < 0)
										pObject->SetPosY(rectIntersection.bottom + pObject->GetAnchorPoint().y);
								}
							}
							if(dRectHeight > dRectWidth)
							{
								// Side Collision
								if(ObjCollisionRect.left < rectTileCollision.left)
								{
									if(pObject->GetVelX() > 0)
										pObject->SetPosX(rectIntersection.left + pObject->GetAnchorPoint().x - dAnmWidth);
								}
								else if(ObjCollisionRect.right > rectTileCollision.right)
								{
									if(pObject->GetVelX() < 0)
										pObject->SetPosX(rectIntersection.right + pObject->GetAnchorPoint().x);
								}
							}
						}
					}
				}
				// Else let's just check the event
				else
				{
					// If this tile has an event...
					if(tileCurrent->GetEventID() != cNullEventID &&
						tileCurrent->GetEventID() != cNullEventID2)
					//if(strcmp(pStringTable->GetString(tileCurrent->GetEventID()), "none") != 0 &&
					//	strcmp(pStringTable->GetString(tileCurrent->GetEventID()), "") != 0)
					{
						char nConditionsMet = 0;
						Byte byteTemp = tileCurrent->GetInfo();
						TurnBitOff(byteTemp, 0);
						char nConditionsNeeded = GetNumberOfBitsOn(byteTemp);

						// If this tile should send an event in any collision
						if(TestBit(tileCurrent->GetInfo(), BIT_EVENT_ANY_COLLISION))
							nConditionsMet++;
						// If this tile should send an event only when colliding with player
						if(TestBit(tileCurrent->GetInfo(), BIT_EVENT_PLAYER_COLLISION))
							// Check if pBase is the player and if it is, send event
							if(ObjType == IBaseInterface::TYPE_CHAR_PLAYER)
								nConditionsMet++;
						if(TestBit(tileCurrent->GetInfo(), BIT_EVENT_ACTION_BUTTON))
							if(CInputManager::GetInstance()->GetPressedA())
								nConditionsMet++;
						if(TestBit(tileCurrent->GetInfo(), BIT_EVENT_BASIC_ATTACK))
							if(ObjType == IBaseInterface::TYPE_WEAPON_DAGGER)
								nConditionsMet++;
						if(TestBit(tileCurrent->GetInfo(), BIT_EVENT_FIRE_BLADE))
							if(ObjType == IBaseInterface::TYPE_WEAPON_SWORD)
								nConditionsMet++;
						if(TestBit(tileCurrent->GetInfo(), BIT_EVENT_EARTH_HAMMER))
							if(ObjType == IBaseInterface::TYPE_WEAPON_HAMMER)
								nConditionsMet++;
						if(TestBit(tileCurrent->GetInfo(), BIT_EVENT_AIR_CROSSBOW))
							if(ObjType == IBaseInterface::TYPE_WEAPON_ARROW)
								nConditionsMet++;

						if(nConditionsMet == nConditionsNeeded)
						{
							TileInfo* eventInfo = new TileInfo(uiIndexWidth, uiIndexHeight, tileCurrent, this);
							CEventSystem::GetInstance()->SendEvent(pStringTable->GetString(tileCurrent->GetEventID()), eventInfo);
						}
					}
					// Continue checking
				}
			}

			// Since we're reading line by line, from left to right, we need
			// to increase the width index every time we draw a tile
			++uiIndexWidth;

			// Once we reach the end of a line, though, we need to reset the
			// width index and increase the height index
			if((int)uiIndexWidth >= GetWidth())
			{
				// Reset width index
				uiIndexWidth = 0;

				// Increase height index
				++uiIndexHeight;
			}
		}

		// Once we're done loading a layer, we should reset the width and height
		// indexes, so that the next layer is rendered above this one
		uiIndexWidth = 0;
		uiIndexHeight = 0;
		uiIndexLayer = m_uiObjectLayer;
	}

	// Return if collided or not
	return bCollided;
}

////////////////////////////////////////////////////////////////////////
//	Purpose		:	Get the source RECT of a tile in a tileset
//	Parameters	:	Tile to use
//	Return		:	The source RECT
////////////////////////////////////////////////////////////////////////
RECT CMap::GetTileSourceRect(CTile* tileCurrent)
{
	RECT rectSource;
	rectSource.left = tileCurrent->GetPosX() * GetTileset()->GetTileWidth();
	rectSource.top = tileCurrent->GetPosY() * GetTileset()->GetTileHeight();
	rectSource.right = rectSource.left + GetTileset()->GetTileWidth();
	rectSource.bottom = rectSource.top + GetTileset()->GetTileHeight();

	return rectSource;
}

void CMap::TurnOffCollisionOnTile(unsigned int uiX, unsigned int uiY)
{
	int tileIndex =  uiY * GetWidth() + uiX;

	Byte info = m_vLayers[0].GetTile(tileIndex)->GetInfo();
	TurnBitOff(info, BIT_TILE_COLLISION);
	m_vLayers[0].GetTile(tileIndex)->SetInfo(info);
}