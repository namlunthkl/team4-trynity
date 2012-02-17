#pragma once

class IGameState
{
private:

public:
	virtual ~IGameState(void) = 0{};
	virtual void Enter(void) = 0; // Enters the Game State
	virtual bool Input(void) = 0; // Input
	virtual void Update(void) = 0; // Update
	virtual void Render(void) = 0; // Draw
	virtual void Exit(void) = 0; // Leaves the Game State
};