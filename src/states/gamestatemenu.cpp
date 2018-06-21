#include "gamestatemenu.hpp"
#include "gamemanager.hpp"
#include "gamestate.hpp"

tr::GameStateMenu tr::GameStateMenu::m_state;

void tr::GameStateMenu::Init()
{

}

void tr::GameStateMenu::Cleanup()
{
	
}

void tr::GameStateMenu::Pause()
{

}

void tr::GameStateMenu::Resume()
{
	
}

void tr::GameStateMenu::HandleEvents(tr::GameManager * game)
{
	sf::RenderWindow * window = game->GetWindow();

	sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            game->Quit();
        if (event.type == sf::Event::KeyPressed)
		{
		    if (event.key.code == sf::Keyboard::A)
		        game->PopState();
		    else if (event.key.code == sf::Keyboard::Escape)
		        game->Quit();
		}
    }
}

void tr::GameStateMenu::Update(tr::GameManager * game)
{
	sf::RenderWindow * window = game->GetWindow();
	window->clear();
}

void tr::GameStateMenu::Draw(tr::GameManager * game)
{
	sf::RenderWindow * window = game->GetWindow();
	window->display();
	std::cout << "Menu state" << std::endl;
}