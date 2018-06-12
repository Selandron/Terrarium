#ifndef RESOURCE_FONT_HPP
#define RESOURCE_FONT_HPP

/*
    Resource loading and storing a sf::Font

    Author : Etienne Andrieu
*/

#include "resource.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace tr 
{

class ResourceFont : public Resource
{
	public:
		ResourceFont();
		ResourceFont(std::string id, std::string filename);
		~ResourceFont();

		void Load();
        void Unload();

		sf::Font * GetFont() {return m_font;}
	private:
		sf::Font * m_font;
};

}
#endif