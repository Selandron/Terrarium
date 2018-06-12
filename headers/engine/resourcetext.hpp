#ifndef RESOURCE_TEXT_HPP
#define RESOURCE_TEXT_HPP

/*
    Resource loading and storing a pile of string

    Author : Etienne Andrieu
*/

#include "resource.hpp"
#include <iostream>
#include <string>

namespace tr 
{

class ResourceText : public Resource
{
	public:
		ResourceText();
		ResourceText(std::string id, std::string filename);
		~ResourceText();

		void Load();
        void Unload();

		std::string * GetString() {return m_string;}
	private:
		std::string * m_string;
};

}
#endif