#ifndef RESOURCE_SOUNDBUFFER_HPP
#define RESOURCE_SOUNDBUFFER_HPP

/*
    Resource loading and storing a sf::SoundBuffer

    Author : Etienne Andrieu
*/

#include "resource.hpp"
#include <SFML/Audio.hpp>
#include <iostream>

namespace tr 
{

class ResourceSoundBuffer : public Resource
{
	public:
		ResourceSoundBuffer();
		ResourceSoundBuffer(std::string id, std::string filename);
		~ResourceSoundBuffer();

		void Load();
        void Unload();

		sf::SoundBuffer * GetSoundBuffer() {return m_soundBuffer;}
	private:
		sf::SoundBuffer * m_soundBuffer;
};

}
#endif