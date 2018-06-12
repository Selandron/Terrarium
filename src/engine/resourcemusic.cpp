#include "resourcemusic.hpp"

tr::ResourceMusic::ResourceMusic()
: tr::Resource("null_music", "null_music")
{
	m_type = RESOURCE_MUSIC;
	m_music = NULL;
}

tr::ResourceMusic::ResourceMusic(std::string id, std::string filename)
: tr::Resource(id, filename)
{	
	m_type = RESOURCE_MUSIC;
	Load();	
}

tr::ResourceMusic::~ResourceMusic()
{
	if (m_music)
		delete m_music;
}

void tr::ResourceMusic::Load()
{
	m_music = new sf::Music();
	if (!m_music->openFromFile(m_filename)) 
	    m_loaded = false;
	else 
		m_loaded = true;
}

void tr::ResourceMusic::Unload()
{
	if (m_music)
		delete m_music;
	m_loaded = false;
}