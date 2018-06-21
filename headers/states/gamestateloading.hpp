#ifndef GAMESTATELOADING_HPP
#define GAMESTATELOADING_HPP

#include "gamestate.hpp"
#include "gamestatemenu.hpp"
#include "resourcemanager.hpp"
#include <iostream>
#include <thread>

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

		void Loading();

	protected:
		GameStateLoading() { }

	private:
		static GameStateLoading m_state;

		sf::Sprite m_loadingSprite;
		sf::Text m_tipText;
		sf::Text m_statusText;
		std::thread m_loadingThread;
};

}

#endif