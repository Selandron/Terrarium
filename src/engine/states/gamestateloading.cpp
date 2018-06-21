#include "gamestateloading.hpp"

tr::GameStateLoading tr::GameStateLoading::m_state;

void tr::GameStateLoading::Init()
{

}

void tr::GameStateLoading::Cleanup()
{
	
}

void tr::GameStateLoading::Pause()
{

}

void tr::GameStateLoading::Resume()
{
	
}

void tr::GameStateLoading::HandleEvents(tr::GameManager * game)
{
	sf::RenderWindow * window = game->GetWindow();

	sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            game->Quit();
        if (event.type == sf::Event::KeyPressed)
		{
		    if (event.key.code == sf::Keyboard::Escape)
		    {
		        game->PushState(GameStateMenu::Instance());
		    }
		}
    }
}

void tr::GameStateLoading::Update(tr::GameManager * game)
{
	sf::RenderWindow * window = game->GetWindow();
	window->clear();
}

void tr::GameStateLoading::Draw(tr::GameManager * game)
{
	sf::RenderWindow * window = game->GetWindow();
	window->display();
	std::cout << "Loading state" << std::endl;
}