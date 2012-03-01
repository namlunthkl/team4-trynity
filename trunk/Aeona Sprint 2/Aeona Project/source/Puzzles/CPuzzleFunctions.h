#ifndef C_PUZZLE_FUNCTIONS_H_
#define C_PUZZLE_FUNCTIONS_H_

#include "../Messaging/CEvent.h"
#include "../Tile Mapping/CMap.h"

#include <vector>
using std::vector;


void PuzzleA_Torches_HandleEvent(CEvent* pEvent, CPuzzle* pPuzzle)
{
	unsigned int i;
	string EventName = "";
	int EventNumber = 0;

	for(i = 0; i < pEvent->GetEventID().size(); ++i)
	{
		if(pEvent->GetEventID()[i] == '.')
			break;

		EventName += pEvent->GetEventID()[i];
	}

	EventNumber = pEvent->GetEventID()[i++];

	if(pEvent->GetEventID() == "LightTorch")
	{
		CMap::TileInfo* eventInfo = (CMap::TileInfo*)pEvent->GetParam();
		vector<int> vnArgs = *pPuzzle->GetArguments();

		int PosX = eventInfo->Map->GetPosX() + eventInfo->Map->GetTileset()->GetTileWidth() * eventInfo->sMapPosX;
		int PosY = eventInfo->Map->GetPosY() + eventInfo->Map->GetTileset()->GetTileHeight() * eventInfo->sMapPosY;
	}
}


#endif // C_PUZZLE_FUNCTIONS_H_