#include "resourcefont.hpp"

tr::ResourceFont::ResourceFont()
: tr::Resource("null_font", "null_font")
{
	m_type = RESOURCE_FONT;
	m_font = NULL;
}

tr::ResourceFont::ResourceFont(std::string id, std::string filename)
: tr::Resource(id, filename)
{	
	m_type = RESOURCE_FONT;
}

tr::ResourceFont::~ResourceFont()
{
	Unload();
}

void tr::ResourceFont::Load()
{
	m_font = new sf::Font();
	if (!m_font->loadFromFile(m_filename)) 
	    m_loaded = false;
	else 
		m_loaded = true;
}

void tr::ResourceFont::Unload()
{
	if (m_font)
		delete m_font;
	m_loaded = false;
}