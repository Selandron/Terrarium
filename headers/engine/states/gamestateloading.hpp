#ifndef GAMESTATELOADING_HPP
#define GAMESTATELOADING_HPP

#include "gamestate.hpp"
#include "gamestatemenu.hpp"
#include <iostream>

namespace tr
{
class GameStateLoading : public tr::GameState
{
	public:
		void Init();
		void Cleanup();

		void Pause();
		void Resume();

		void HandleEvents(GameManager * game);
		void Update(GameManager * game);
		void Draw(GameManager * game);

		static GameStateLoading * Instance() {
			return &m_state;
		}

	protected:
		GameStateLoading() { }

	private:
		static GameStateLoading m_state;

};

}

#endif