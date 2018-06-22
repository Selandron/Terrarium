#ifndef GAMESTATE_H
#define GAMESTATE_H

/*
 * 	Abstract class representing a game state, a layer of the state system
 *	
 *	Author : Etienne Andrieu
 */

#include "gamemanager.hpp"

namespace tr
{

class GameState
{
	public:
		virtual void Init(GameManager* game) = 0;				//Init the state
		virtual void Cleanup() = 0;								//Cleanup the memory in the state

		virtual void Pause() = 0;								//Pause the state
		virtual void Resume() = 0;								//Resume the state

		virtual void HandleEvents(GameManager* game) = 0;		//Handle the poll event
		virtual void Update(GameManager* game) = 0;				//update what to display
		virtual void Draw(GameManager* game) = 0;				//Call to draw

		void ChangeState(GameManager* game, GameState* state) {	//Call another state
			game->ChangeState(state);
		}

	protected:
		GameState() { }
};

}

#endif