#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include <vector>
#include <SFML/Graphics.hpp>

namespace tr
{

class GameState;

class GameManager
{
	public:

		void Init();
		void Cleanup();

		void ChangeState(GameState * state);
		void PushState(GameState * state);
		void PopState();

		void HandleEvents();
		void Update();
		void Draw();

		bool Running() { return m_running; }
		void Quit() { m_running = false; }

		sf::RenderWindow * GetWindow() { return m_window; }

	private:
		//Stack of States
		std::vector<GameState *> m_states;

		sf::RenderWindow * m_window;

		bool m_running;
};

}

#endif
