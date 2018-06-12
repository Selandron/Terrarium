#include "resourcetext.hpp"

tr::ResourceText::ResourceText()
: tr::Resource("null_string", "null_string")
{
	m_type = RESOURCE_TEXT;
	m_string = NULL;
}

tr::ResourceText::ResourceText(std::string id, std::string filename)
: tr::Resource(id, filename)
{	
	m_type = RESOURCE_TEXT;
	Load();	
}

tr::ResourceText::~ResourceText()
{
	if (m_string)
		delete m_string;
}

void tr::ResourceText::Load()
{
	if (!m_string) 
	    m_loaded = false;
	else 
		m_loaded = true;
}

void tr::ResourceText::Unload()
{
	if (m_string)
		delete m_string;
	m_loaded = false;
}