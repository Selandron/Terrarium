#ifndef GAMESTATEMENU_HPP
#define GAMESTATEMENU_HPP

#include "gamestate.hpp"
#include <iostream>

namespace tr
{
class GameStateMenu : public tr::GameState
{
	public:
		void Init();
		void Cleanup();

		void Pause();
		void Resume();

		void HandleEvents(GameManager * game);
		void Update(GameManager * game);
		void Draw(GameManager * game);

		static GameStateMenu * Instance() {
			return &m_state;
		}

	protected:
		GameStateMenu() { }

	private:
		static GameStateMenu m_state;

};

}

#endif