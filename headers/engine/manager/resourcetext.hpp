#ifndef RESOURCE_TEXT_HPP
#define RESOURCE_TEXT_HPP

/*
    Resource loading and storing a pile of string

    Author : Etienne Andrieu
*/

#include "resource.hpp"
#include "tinyxml2.hpp"
#include <iostream>
#include <string>
#include <map>

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

		std::string * GetText(std::string key);
	private:
		std::map<std::string, std::string *> * m_resources;
};

}
#endif