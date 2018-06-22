#include "gamestateloading.hpp"

tr::GameStateLoading tr::GameStateLoading::m_state;

void tr::GameStateLoading::Init(GameManager* game)
{
	tr::ResourceManager * resMan = tr::ResourceManager::GetInstance();
	resMan->LoadFromFileXML("index.xml", "loading_scope");

	m_windowSize = game->GetSize();

	m_endLoad = false;
	m_loadingSprite.setTexture(*_GET_TEXTURE_SCOPE("loading_screen_1", "loading_scope"));
	m_loadingSprite.scale(m_windowSize.x / m_loadingSprite.getLocalBounds().width, m_windowSize.y / m_loadingSprite.getLocalBounds().height);
	m_tipText.setFont(*_GET_FONT_SCOPE("arial", "loading_scope"));
	std::string target = "tip" + std::to_string(std::rand() % 50 + 1);
	m_tipText.setColor(sf::Color::Yellow);
	m_tipText.setString(*_GET_TEXT_SCOPE("loading_tips", "loading_scope", target));

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

    m_mutex.lock();
    if (m_endLoad)
    	game->ChangeState(tr::GameStateMenu::Instance());
    m_mutex.unlock();
}

void tr::GameStateLoading::Update(tr::GameManager * game)
{
	sf::RenderWindow * window = game->GetWindow();
	window->clear();
}

void tr::GameStateLoading::Draw(tr::GameManager * game)
{
	sf::RenderWindow * window = game->GetWindow();
	window->draw(m_loadingSprite);
	window->draw(m_tipText);
	window->display();
}

void tr::GameStateLoading::Loading()
{
	tr::ResourceManager * resMan = tr::ResourceManager::GetInstance();
	resMan->LoadFromFileXML("index.xml");
	m_mutex.lock();
	//m_endLoad = true;
    m_mutex.unlock();
}