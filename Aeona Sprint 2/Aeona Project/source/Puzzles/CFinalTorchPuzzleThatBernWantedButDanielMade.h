#include "CTorchPuzzle.h"


class CFinalTorchPuzzleThatBernWantedButDanielMade : public CTorchPuzzle
{
	PointD torchPositions[4];

public:
	void Create(unsigned int uiArgCount, char* szEventToFire, char* szEventToListenTo, bool bSequential);
	void EventReceived(int ArgumentNumber, void* EventData);
};