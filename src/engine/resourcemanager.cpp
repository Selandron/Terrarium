#include "resourcemanager.hpp"

tr::Resource * tr::ResourceManager::FindResourceByID(std::string ID)
{
	for (std::map<std::string,std::map<std::string, tr::Resource *> * >::iterator it = this->m_resources.begin(); it != this->m_resources.end(); ++it)
		if (FindResourceByID(ID, it->first))
			return FindResourceByID(ID, it->first);
	return NULL;
}

tr::Resource * tr::ResourceManager::FindResourceByID(std::string ID, std::string scope)
{
	std::map<std::string,std::map<std::string, tr::Resource *> * >::iterator it = this->m_resources.find(scope);
	if (it == this->m_resources.end())
		return NULL;
	std::map<std::string, tr::Resource *>::iterator sub = it->second->find(ID);
	if (sub == it->second->end())
		return NULL;

	return sub->second; 
}

bool tr::ResourceManager::LoadFromFileXML(std::string filename)
{
	//Opening xml document
	tinyxml2::XMLDocument doc;
	std::string root = "./data/";
	root += filename;
	doc.LoadFile(root.c_str());
	if (doc.Error()) //Error while pre parsing document
	{	
		std::cerr << doc.ErrorStr() << std::endl;
		return false;
	}

	//PARSING
	std::string path = "./data/";	//Root path

	tinyxml2::XMLElement * scopeEl = doc.FirstChildElement("scope");		//ScopeElement need to exist and have a name
	if (scopeEl && scopeEl->Attribute("name") != NULL)		
	{
		std::string scope = scopeEl->Attribute("name");

		//Remove existing scope if exist
		ClearScope(scope);

		//Create scope and map
		std::map<std::string, Resource *> * dup = new std::map<std::string, Resource *>();

		if (!ParseXMLTree(scopeEl, path, dup))
			return false;

		this->m_resources.insert(std::pair<std::string, std::map<std::string, Resource *> * >(scope, dup));
	}
	else if (scopeEl->NoChildren())	//Error No children
	{
		std::cerr << "Error : " << filename << " has no resources indexed!" << std::endl;
		return true;
	} 
	else							//Error No scope
	{
		std::cerr << "Error : " << filename << " has no scope name!" << std::endl;
		return true;
	}
	return true;
}

bool tr::ResourceManager::LoadFromFileXML(std::string filename, std::string scopename)
{
	//Opening xml document
	tinyxml2::XMLDocument doc;
	std::string root = "./data/";
	root += filename;
	doc.LoadFile(root.c_str());
	if (doc.Error()) //Error while pre parsing document
	{	
		std::cerr << doc.ErrorStr() << std::endl;
		return false;
	}

	//PARSING
	std::string path = "./data/";	//Root path

	tinyxml2::XMLElement * scopeEl = doc.FirstChildElement("scope");		
	while (!(scopeEl && strcmp(scopeEl->Value(), "scope") == 0 && strcmp(scopeEl->Attribute("name"), scopename.c_str()) == 0)) //Find the good scope
		scopeEl = scopeEl->NextSibling()->ToElement();
	if (scopeEl && strcmp(scopeEl->Value(), "scope") == 0 && strcmp(scopeEl->Attribute("name"), scopename.c_str()) == 0)		
	{
		std::string scope = scopeEl->Attribute("name");

		//Remove existing scope if exist
		ClearScope(scope);
		//Create scope and map
		std::map<std::string, Resource *> * dup = new std::map<std::string, Resource *>();

		if (!ParseXMLTree(scopeEl, path, dup))
			return false;

		this->m_resources.insert(std::pair<std::string, std::map<std::string, Resource *> * >(scope, dup));
	}
	else if (scopeEl->NoChildren())	//Error No children
	{
		std::cerr << "Error : " << filename << " has no resources indexed!" << std::endl;
		return true;
	}
	else							//Error No scope
	{
		std::cerr << "Error : " << filename << " - scopename " << scopename << "not found" << std::endl;
		return true;
	}
	return true;
}

bool tr::ResourceManager::ParseXMLTree(tinyxml2::XMLNode * root, std::string path, std::map<std::string, Resource *> * dup)
{
	tinyxml2::XMLNode * childNode = root->FirstChildElement();
	while (childNode)	//Parse all type of resources
	{
		if (strcmp(childNode->Value(), "file") == 0)	//If its a file
		{
			tinyxml2::XMLElement * element = childNode->ToElement();
			if (element && element->Attribute("key") && element->Attribute("type") && element->GetText()) //Has enougth attributes
			{									
				std::string key = element->Attribute("key");
				tr::Resource * t = LoadResource(element, path);	//Load of the Resource								
				if (!t || !t->IsLoaded())
					return false;
				dup->insert(std::pair<std::string, tr::Resource *>(key, t));
				this->m_resourceCount++;
			}
		}
		else 											//If not, recursive loading
		{
			std::string newPath = path;
			newPath += childNode->Value();
			newPath += "/";
			if (!ParseXMLTree(childNode, newPath, dup))
				return false;
		}

		childNode = childNode->NextSibling();
	}
	return true;
}

tr::Resource * tr::ResourceManager::LoadResource(tinyxml2::XMLElement * element, std::string path)
{
	std::string key = element->Attribute("key");
	std::string file = element->GetText();
	file = path  + file;
	RESOURCE_TYPE type = (RESOURCE_TYPE)element->IntAttribute("type");

	switch(type)
	{
		case RESOURCE_TYPE::RESOURCE_GRAPHIC:
			ResourceTexture * t;
			t = new ResourceTexture(key, file);
			if(t)
				t->Load();
			return t;
			break;

		case RESOURCE_TYPE::RESOURCE_SOUNDBUFFER:
			ResourceSoundBuffer * a;
			a = new ResourceSoundBuffer(key, file);
			if(a)
				a->Load();
			return a;
			break;

		case RESOURCE_TYPE::RESOURCE_MUSIC:
			ResourceMusic * m;
			m = new ResourceMusic(key, file);
			if(m)
				m->Load();
			return m;
			break;

		case RESOURCE_TYPE::RESOURCE_FONT:
			ResourceFont * f;
			f = new ResourceFont(key, file);
			if(f)
				f->Load();
			return f;
			break;

		default:
			return NULL;
	}

	return NULL;
}

void tr::ResourceManager::Clear()
{
	for (std::map<std::string,std::map<std::string, tr::Resource *> * >::iterator it = this->m_resources.begin(); it != this->m_resources.end(); ++it)
		ClearScope(it->first);
	this->m_resources.clear();
	this->m_resourceCount = 0;
}

void tr::ResourceManager::ClearScope(std::string scope)
{
	std::map<std::string,std::map<std::string, tr::Resource *> * >::iterator it = this->m_resources.find(scope); 	//Iterator on the map

	if (it == this->m_resources.end()) //If not found, OK
		return;

	//If found, remove all in sub map (free memory)
	std::map<std::string, tr::Resource *> * resourcesMap = it->second;
	for (std::map<std::string, tr::Resource *>::iterator sub = resourcesMap->begin(); sub != resourcesMap->end(); ++sub)
	{
		if (sub->second)
		{
			sub->second->Unload();
			delete sub->second;
		}
		this->m_resourceCount--;
	}
	resourcesMap->clear();
	delete resourcesMap;
	//Remove in first map the entry 
	this->m_resources.erase(it);
}

void tr::ResourceManager::PrintManager()
{
	for (std::map<std::string,std::map<std::string, tr::Resource *> * >::iterator it = this->m_resources.begin(); it != this->m_resources.end(); it++)
	{
		std::cout << "Scope : " << it->first << std::endl;
		std::map<std::string, tr::Resource *> * resourcesMap = it->second;
		for (std::map<std::string, tr::Resource *>::iterator sub = resourcesMap->begin(); sub != resourcesMap->end(); ++sub)
			std::cout << "-- Key : " << sub->first << " -- Target : " << (int)sub->second << " -- Type : " << sub->second->GetResourceType() << std::endl;  
	}
}