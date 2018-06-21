#include "gamestateloading.hpp"

tr::GameStateLoading tr::GameStateLoading::m_state;

void tr::GameStateLoading::Init()
{
	tr::ResourceManager * resMan = tr::ResourceManager::GetInstance();
	resMan->LoadFromFileXML("index.xml", "loading_scope");

	m_loadingThread = std::thread(&GameStateLoading::Loading, this);
	m_loadingThread.detach();
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
}

void tr::GameStateLoading::Loading()
{
	tr::ResourceManager * resMan = tr::ResourceManager::GetInstance();
	resMan->LoadFromFileXML("index.xml");
}