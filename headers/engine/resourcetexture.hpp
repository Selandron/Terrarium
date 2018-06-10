#ifndef RESOURCETEXTURE_HPP
#define RESOURCETEXTURE_HPP

/*
    Resource loading and storing a sf::Texture.

    Author : Etienne Andrieu
*/

#include "resource.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace tr 
{

class ResourceTexture : public Resource
{
	public:
		ResourceTexture();
		ResourceTexture(std::string id, std::string filename);
		~ResourceTexture();

		void Load();
        void Unload();

		sf::Texture * GetTexture() {return m_texture;}
	private:
		sf::Texture * m_texture;
};

}
#endif