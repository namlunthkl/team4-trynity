#pragma once
#include "IGameState.h"
#include "AB_EmitterManager.h"
#include "SGD Wrappers\CSGD_TextureManager.h"


class TestingState : public IGameState 
{
private:

	TestingState( void );
	TestingState( const TestingState& );
	TestingState& operator=( const TestingState& );
	~TestingState(void);

	EmitterManager*  m_EM;
	
	RECT m_rVisualizer;
	int m_nVisualizerID;

public:
	RECT GetVisualizer(){return m_rVisualizer;}
	void SetVisualizer(int left, int top, int bottom, int right)
	{
		m_rVisualizer.left = left;
		m_rVisualizer.top = top;
		m_rVisualizer.bottom = bottom;
		m_rVisualizer.right = right;
	}
	void InitVizualizer(void)
	{
		// VizualIzer
		m_EM->GetEmitter(8)->m_pData->SetEmitterPositionX( m_rVisualizer.left + ((float)( CSGD_TextureManager::GetInstance()->GetTextureWidth(m_nVisualizerID) * 0.75f) / 2.0f) + 2 );
		m_EM->GetEmitter(8)->m_pData->SetEmitterPositionY( m_rVisualizer.top + ((float)( CSGD_TextureManager::GetInstance()->GetTextureHeight(m_nVisualizerID) * 0.75f) / 2.0f) - 10 );
	}
	static TestingState* GetInstance( void );

	void Enter(void);
	bool Input(void);
	void Update(void);
	void Render(void);
	void Exit(void);
};