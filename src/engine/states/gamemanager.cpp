#include "gamemanager.hpp"
#include "gamestate.hpp"

void tr::GameManager::Init()
{ 
	m_window = new sf::RenderWindow(sf::VideoMode(200, 200), "SFML works!");
	m_running = true;
}

void tr::GameManager::Cleanup()
{
	while(!m_states.empty())
		PopState();
	delete m_window;
}

void tr::GameManager::ChangeState(GameState* state) 
{
	// cleanup the current state
	if (!m_states.empty()) {
		m_states.back()->Cleanup();
		m_states.pop_back();
	}

	// store and init the new state
	m_states.push_back(state);
	m_states.back()->Init();
}

void tr::GameManager::PushState(GameState* state)
{
	// pause current state
	if ( !m_states.empty() ) {
		m_states.back()->Pause();
	}

	// store and init the new state
	m_states.push_back(state);
	m_states.back()->Init();
}

void tr::GameManager::PopState()
{
	// cleanup the current state
	if ( !m_states.empty() ) {
		m_states.back()->Cleanup();
		m_states.pop_back();
	}

	// resume previous state
	if ( !m_states.empty() ) {
		m_states.back()->Resume();
	}
}


void tr::GameManager::HandleEvents() 
{
	// let the state handle events
	m_states.back()->HandleEvents(this);
}

void tr::GameManager::Update() 
{
	// let the state update the game
	m_states.back()->Update(this);
}

void tr::GameManager::Draw() 
{
	// let the state draw the screen
	m_states.back()->Draw(this);
}
