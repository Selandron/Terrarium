#include "resourcesoundbuffer.hpp"

tr::ResourceSoundBuffer::ResourceSoundBuffer()
: tr::Resource("null_soundbuffer", "null_soundbuffer")
{
	m_type = RESOURCE_SOUNDBUFFER;
	m_soundBuffer = NULL;
}

tr::ResourceSoundBuffer::ResourceSoundBuffer(std::string id, std::string filename)
: tr::Resource(id, filename)
{	
	m_type = RESOURCE_SOUNDBUFFER;
	Load();	
}

tr::ResourceSoundBuffer::~ResourceSoundBuffer()
{
	if (m_soundBuffer)
		delete m_soundBuffer;
}

void tr::ResourceSoundBuffer::Load()
{
	m_soundBuffer = new sf::SoundBuffer();
	if (!m_soundBuffer->loadFromFile(m_filename)) 
	    m_loaded = false;
	else 
		m_loaded = true;
}

void tr::ResourceSoundBuffer::Unload()
{
	if (m_soundBuffer)
		delete m_soundBuffer;
	m_loaded = false;
}