#include "gamemanager.hpp"
#include "gamestate.hpp"

void tr::GameManager::Init()
{ 
	m_running = checkIni();
	if (m_running)
	{
		sf::ContextSettings settings(0, 0, m_antialiasingLevel);
		if (m_fullscreen)
			m_window = new sf::RenderWindow(m_windowCaract, "Terrarium - A Terraria bad rip-off", sf::Style::Fullscreen, settings);
		else
			m_window = new sf::RenderWindow(m_windowCaract, "Terrarium - A Terraria bad rip-off", sf::Style::Default, settings);
		m_window->setVerticalSyncEnabled(m_verticalSync);
		if (m_maxFramerate != 0)
		m_window->setFramerateLimit(m_maxFramerate);
	}
	
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

bool tr::GameManager::checkIni()
{
	std::ifstream infile("config.ini");
	if (!infile)
	{
		m_windowCaract = sf::VideoMode(800, 600, 32);
		m_fullscreen = false;
		m_antialiasingLevel = 0;
		m_maxFramerate = 60;
		m_verticalSync = false;
		m_lang = "EN";
		std::ofstream outfile("config.ini");
		if (!outfile)
			return false;
		outfile << "fullscreen = false" << std::endl << "width = 800" << std::endl << "height = 600" << std::endl << "dpp = 32" << std::endl << "antialiasing = 0" << std::endl << "frameratemax = 60" << std::endl << "verticalsync = false" << std::endl << "lang = EN";
		outfile.close();
		return true;
	}

	std::string line, variable, equal;
	//Fullscreen
	std::getline(infile, line);
	std::istringstream iss(line);
	std::string variableBool;
	if(!(iss >> variable >> equal >> variableBool) || variable.compare("fullscreen") !=  0 || equal.compare("=") != 0 || (variableBool.compare("true") != 0 && variableBool.compare("false") != 0))
		return false;
	m_fullscreen = (variableBool.compare("true") == 0) ? true : false;

	//Caract window
	std::getline(infile, line);
	iss.clear();
	iss.str(line);
	int width, height, dpp;
	if(!(iss >> variable >> equal >> width) || variable.compare("width") != 0 || equal.compare("=") != 0)
		return false;
	m_windowCaract.width = width;
	std::getline(infile, line);
	iss.str(line);
	iss.clear();
	if(!(iss >> variable >> equal >> height) || variable.compare("height") != 0 || equal.compare("=") != 0)
		return false;
	m_windowCaract.height = height;
	std::getline(infile, line);
	iss.str(line);
	iss.clear();
	if(!(iss >> variable >> equal >> dpp) || variable.compare("dpp") != 0 || equal.compare("=") != 0)
		return false;
	m_windowCaract.bitsPerPixel = dpp;

	//Antialiasing
	int antialiasing;
	std::getline(infile, line);
	iss.str(line);
	iss.clear();
	if(!(iss >> variable >> equal >> antialiasing) || variable.compare("antialiasing") != 0 || equal.compare("=") != 0)
		return false;
	m_antialiasingLevel = antialiasing;

	//Max framarate
	int framerate;
	std::getline(infile, line);
	iss.str(line);
	iss.clear();
	if(!(iss >> variable >> equal >> framerate) || variable.compare("frameratemax") != 0 || equal.compare("=") != 0)
		return false;
	m_maxFramerate = framerate;

	//Vertical sync
	std::getline(infile, line);
	iss.str(line);
	iss.clear();
	if(!(iss >> variable >> equal >> variableBool) || variable.compare("verticalsync") != 0 || equal.compare("=") != 0 || (variableBool.compare("true") != 0 && variableBool.compare("false") != 0))
		return false;
	m_verticalSync = (variableBool.compare("true") == 0) ? true : false;

	//Lang
	std::string lang;
	std::getline(infile, line);
	iss.str(line);
	iss.clear();
	if(!(iss >> variable >> equal >> lang) || variable.compare("lang") != 0 || equal.compare("=") != 0)
		return false;
	m_lang = lang;

	//Test on variables
	std::vector<sf::VideoMode> listVideoMode = sf::VideoMode::getFullscreenModes();
	bool found = false;
	for (std::vector<sf::VideoMode>::iterator i = listVideoMode.begin(); i != listVideoMode.end(); ++i)
		if (*i == m_windowCaract)
		{
			found = true;
			break;
		}
	if (!found)
		return false;

	if (m_antialiasingLevel < 0 || m_antialiasingLevel > 10)
		return false;

	if (m_maxFramerate < 0) 
		return false;

	if (m_maxFramerate != 0 && m_verticalSync == true)
		m_verticalSync = false;

	//###############TEST SUR LA LANGUE A FAIRE#################

	return true;
}