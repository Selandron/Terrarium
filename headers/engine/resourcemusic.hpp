#ifndef RESOURCE_MUSIC_HPP
#define RESOURCE_MUSIC_HPP

/*
    Resource loading and storing a sf::Music

    Author : Etienne Andrieu
*/

#include "resource.hpp"
#include <SFML/Audio.hpp>
#include <iostream>

namespace tr 
{

class ResourceMusic : public Resource
{
	public:
		ResourceMusic();
		ResourceMusic(std::string id, std::string filename);
		~ResourceMusic();

		void Load();
        void Unload();

		sf::Music * GetMusic() {return m_music;}
	private:
		sf::Music * m_music;
};

}
#endif