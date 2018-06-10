#include "resourcetexture.hpp"

tr::ResourceTexture::ResourceTexture()
: tr::Resource("null_graphic", "null_graphic")
{
	m_type = RESOURCE_GRAPHIC;
	m_texture = NULL;
}

tr::ResourceTexture::ResourceTexture(std::string id, std::string filename)
: tr::Resource(id, filename)
{	
	m_type = RESOURCE_GRAPHIC;
	Load();	
}

tr::ResourceTexture::~ResourceTexture()
{
	if (m_texture)
		delete m_texture;
}

void tr::ResourceTexture::Load()
{
	m_texture = new sf::Texture();
	if (!m_texture->loadFromFile(m_filename)) 
	    m_loaded = false;
	else 
		m_loaded = true;
}

void tr::ResourceTexture::Unload()
{
	if (m_texture)
		delete m_texture;
	m_loaded = false;
}