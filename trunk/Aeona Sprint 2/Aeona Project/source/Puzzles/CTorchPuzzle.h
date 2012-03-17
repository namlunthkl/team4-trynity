#ifndef C_TORCH_PUZZLE_H_
#define C_TORCH_PUZZLE_H_

#include "CPuzzle.h"

class CTorchPuzzle : public IBasePuzzle
{
protected:
	vector<ParticleWeapon*> m_vParticle;
	int m_sndFireSound;
	PointD m_ptLastLitTorchPosition;
	bool m_bPlaySound;
public:
	CTorchPuzzle(void){};
	void Create(unsigned int uiArgCount, char* szEventToFire, char* szEventToListenTo, bool bSequential);
	void Update(float fElapsedTime);
	void Render(void);
	void Destroy(void);
	void EventReceived(int ArgumentNumber, void* EventData);
};

#endif // C_TORCH_PUZZLE_H_



