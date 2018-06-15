#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

/*
    Resource Manager. Handle every resource loaded.
    You have to passe by a (or more) xml file that indexes every resource.
    Can be upgraded with a scope system, TODO

    Author : Etienne Andrieu
*/

#define UINT unsigned int

#include "resource.hpp"
#include "resourcetexture.hpp"
#include "resourcesoundbuffer.hpp"
#include "resourcemusic.hpp"
#include "resourcefont.hpp"
#include "resourcetext.hpp"
#include "singleton.hpp"
#include "exceptions.hpp"
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "tinyxml2.hpp"

namespace tr
{

class ResourceManager : public tr::Singleton<ResourceManager>
{
	friend class Singleton<ResourceManager>;	//Set Singleton system

	public:
		Resource * FindResourceByID(const std::string & ID);								//Get the resource wanted
		Resource * FindResourceByID(const std::string & ID, const std::string & scope);		//Get the resource wanted in the scope targeted
		void ClearScope(const std::string & scopename);										//Empty the resources for a define scope
		void Clear();																		//Empty ALL the resources (careful with the use)
		void LoadFromFileXML(const std::string & filename);									//Load an XML file (in data folder) to parse resources (first scope)
		void LoadFromFileXML(const std::string & filename, const std::string & scopename);	//Load an XML file (in data folder) with a scope wanted to parse resources
		void PrintManager();
		UINT GetResourceCount() const { return m_resourceCount; }		
	protected:
	    UINT m_resourceCount; //Total number of resources unloaded and loaded
	    std::map<std::string, std::map<std::string, Resource *> * > m_resources; //Map of form <scope ID, Resource map>

	private:
		ResourceManager() : m_resourceCount(0) {};						//Private Constructor (only called once in Singleton)
		~ResourceManager() {};											//Private Destructor (only called once)

		void ParseXMLTree(tinyxml2::XMLNode * root, std::string path, std::map<std::string, Resource *> * dup);		//Recursive function to parse XML tree
		tr::Resource * LoadResource(const tinyxml2::XMLElement * element, const std::string & path); //Function to load resource
};

#define _GET_TEXTURE(key) ((tr::ResourceTexture *)(tr::ResourceManager::GetInstance()->FindResourceByID(key)))->GetTexture()
#define _GET_TEXTURE_SCOPE(key, scope) ((tr::ResourceTexture *)(tr::ResourceManager::GetInstance()->FindResourceByID(key, scope)))->GetTexture()

#define _GET_SOUNDBUFFER(key) ((tr::ResourceSoundBuffer *)(tr::ResourceManager::GetInstance()->FindResourceByID(key)))->GetSoundBuffer()
#define _GET_SOUNDBUFFER_SCOPE(key, scope) ((tr::ResourceSoundBuffer *)(tr::ResourceManager::GetInstance()->FindResourceByID(key, scope)))->GetSoundBuffer()

#define _GET_MUSIC(key) ((tr::ResourceMusic *)(tr::ResourceManager::GetInstance()->FindResourceByID(key)))->GetMusic()
#define _GET_MUSIC_SCOPE(key, scope) ((tr::ResourceMusic *)(tr::ResourceManager::GetInstance()->FindResourceByID(key, scope)))->GetMusic()

#define _GET_FONT(key) ((tr::ResourceFont *)(tr::ResourceManager::GetInstance()->FindResourceByID(key)))->GetFont()
#define _GET_FONT_SCOPE(key, scope) ((tr::ResourceFont *)(tr::ResourceManager::GetInstance()->FindResourceByID(key, scope)))->GetFont()

#define _GET_TEXT(key, key_text) ((tr::ResourceText *)(tr::ResourceManager::GetInstance()->FindResourceByID(key)))->GetText(key_text)
#define _GET_TEXT_SCOPE(key, scope, key_text) ((tr::ResourceText *)(tr::ResourceManager::GetInstance()->FindResourceByID(key, scope)))->GetText(key_text)

}
#endif