#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

/*
 * 	Class representing a game manager. It's the class that handle the game entirerly and manage the states layer.
 *	
 *	Author : Etienne Andrieu
 */

#include <vector>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>

namespace tr
{

class GameState;

class GameManager
{
	public:

		void Init();											//Init and launch the window
		void Cleanup();											//Clear pending states and shutdown window

		void ChangeState(GameState * state);					//Change the current state (replace the last state of the stak)
		void PushState(GameState * state);						//Push a state above the current one
		void PopState();										//Pop the current state

		void HandleEvents();									//Call the handle event function on the current state
		void Update();											//Call the update function on the current state
		void Draw();											//Call the draw function on the current state

		bool Running() { return m_running; }					//Know if the window is running
		void Quit();											//Quit the infinty loop

		sf::RenderWindow * GetWindow() { return m_window; } 	//Get the reference on the window

	private:
		bool checkIni();

		std::vector<GameState *> m_states;						//Stak of states
		sf::RenderWindow * m_window;							//The window
		bool m_running;											//Status of the window.

		sf::VideoMode m_windowCaract;
		bool m_fullscreen;
		int m_antialiasingLevel;
		int m_maxFramerate;
		bool m_verticalSync;
		std::string m_lang;
};

}

#endif
