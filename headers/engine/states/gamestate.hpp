#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "gamemanager.hpp"

namespace tr
{

	class GameState
	{
	public:
		virtual void Init() = 0;
		virtual void Cleanup() = 0;

		virtual void Pause() = 0;
		virtual void Resume() = 0;

		virtual void HandleEvents(GameManager* game) = 0;
		virtual void Update(GameManager* game) = 0;
		virtual void Draw(GameManager* game) = 0;

		void ChangeState(GameManager* game, GameState* state) {
			game->ChangeState(state);
		}

	protected:
		GameState() { }
	};

}

#endif