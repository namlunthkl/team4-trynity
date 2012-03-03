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
	vector<int>* Args = pPuzzle->GetArguments();

	for(i = 0; i < pEvent->GetEventID().size(); ++i)
	{
		if(pEvent->GetEventID()[i] == '.')
			break;

		EventName += pEvent->GetEventID()[i];
	}

	EventNumber = atoi(pEvent->GetEventID().c_str() + (i+1));

	if(EventName == "TorchLit")
	{
		CMap::TileInfo* eventInfo = (CMap::TileInfo*)pEvent->GetParam();

		int PosX = eventInfo->Map->GetPosX() + eventInfo->Map->GetTileset()->GetTileWidth() * eventInfo->sMapPosX;
		int PosY = eventInfo->Map->GetPosY() + eventInfo->Map->GetTileset()->GetTileHeight() * eventInfo->sMapPosY;

		if(EventNumber < Args->size())
		{
			if((*Args)[EventNumber] == 1)
			{
				(*Args)[EventNumber] = 0;
			}
			else
			{
				(*Args)[EventNumber] = 1;

				if(pPuzzle->GetParticle(EventNumber))
				{
					pPuzzle->GetParticle(EventNumber)->emitter.EmitterPosX = PosX;
					pPuzzle->GetParticle(EventNumber)->emitter.EmitterPosY = PosY;
					pPuzzle->GetParticle(EventNumber)->Fire();
				}
			}
		}


		for(unsigned int i=0; i < (*Args).size(); ++i)
		{
			if((*Args)[i] == 0)
				break;

			if((*Args)[i] == 1 && i == (*Args).size() - 1)
				CEventSystem::GetInstance()->SendEvent(pPuzzle->GetEvent());
		}
	}
}

void PuzzleA_Torched_Update(CPuzzle* pPuzzle)
{


}


#endif // C_PUZZLE_FUNCTIONS_H_