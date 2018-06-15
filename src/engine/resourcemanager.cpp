#include "resourcemanager.hpp"

tr::Resource * tr::ResourceManager::FindResourceByID(const std::string & ID) 
{
	for (std::map<std::string,std::map<std::string, tr::Resource *> * >::iterator it = this->m_resources.begin(); it != this->m_resources.end(); ++it)
		if (FindResourceByID(ID, it->first))
			return FindResourceByID(ID, it->first);
	throw tr::ResourceNotFoundException(ID.c_str());
}

tr::Resource * tr::ResourceManager::FindResourceByID(const std::string & ID, const std::string & scope)
{
	std::map<std::string,std::map<std::string, tr::Resource *> * >::iterator it = this->m_resources.find(scope);
	if (it == this->m_resources.end())
		throw tr::ScopeNotFoundException(scope.c_str());
	std::map<std::string, tr::Resource *>::iterator sub = it->second->find(ID);
	if (sub == it->second->end())
		throw tr::ResourceNotFoundException(ID.c_str());

	return sub->second; 
}

void tr::ResourceManager::LoadFromFileXML(const std::string & filename)
{
	//Opening xml document
	tinyxml2::XMLDocument doc;
	std::string root = "./data/";
	root += filename;
	doc.LoadFile(root.c_str());
	if (doc.Error()) //Error while pre parsing document
	{	
		std::cerr << doc.ErrorStr() << std::endl;
		return;
	}

	//PARSING
	std::string path = "./data/";	//Root path

	tinyxml2::XMLElement * scopeEl = doc.FirstChildElement("scope");		//ScopeElement need to exist and have a name
	if (scopeEl && scopeEl->Attribute("name") != NULL && !scopeEl->NoChildren())		
	{
		std::string scope = scopeEl->Attribute("name");

		//Remove existing scope if exist
		ClearScope(scope);

		//Create scope and map
		std::map<std::string, Resource *> * dup = new std::map<std::string, Resource *>();

		ParseXMLTree(scopeEl, path, dup); //Parse the XML Tree while loading resources
		if (dup->size() != 0) // If some resources still have been loaded
			this->m_resources.insert(std::pair<std::string, std::map<std::string, Resource *> * >(scope, dup)); //Insert the resource scope
		else
			delete dup;
	}
	else if (!scopeEl)
		std::cerr << "Error : " << filename << " There is no scope in this file." << std::endl;
	else if (scopeEl->NoChildren() && scopeEl->Attribute("name") != NULL)
		std::cerr << "Error : In " << filename << " scope " << scopeEl->Attribute("name") << " has no resources indexed!" << std::endl;
	else		
		std::cerr << "Error : " << filename << " - Unknow Error." << std::endl;
}

void tr::ResourceManager::LoadFromFileXML(const std::string & filename, const std::string & scopename)
{
	//Opening xml document
	tinyxml2::XMLDocument doc;
	std::string root = "./data/";
	root += filename;
	doc.LoadFile(root.c_str());
	if (doc.Error()) //Error while pre parsing document
	{	
		std::cerr << doc.ErrorStr() << std::endl;
		return;
	}

	//PARSING
	std::string path = "./data/";	//Root path

	//Search the good scope
	tinyxml2::XMLNode * scopeSearch = doc.FirstChild()->NextSibling();
	tinyxml2 ::XMLElement * scopeEl;
	while (scopeSearch != NULL)
	{
		scopeEl = scopeSearch->ToElement();
		if (scopeEl && strcmp(scopeEl->Value(), "scope") == 0 && strcmp(scopeEl->Attribute("name"), scopename.c_str()) == 0)
			break;
		else
			scopeSearch = scopeEl->NextSibling(); 
	}
	if (scopeSearch == NULL)
		scopeEl = NULL;

	if (scopeEl && !scopeEl->NoChildren())		
	{
		std::string scope = scopeEl->Attribute("name");

		//Remove existing scope if exist
		ClearScope(scope);
		//Create scope and map
		std::map<std::string, Resource *> * dup = new std::map<std::string, Resource *>();

		ParseXMLTree(scopeEl, path, dup); //Parse the XML Tree while loading resources
		if (dup->size() != 0) // If some resources still have been loaded
			this->m_resources.insert(std::pair<std::string, std::map<std::string, Resource *> * >(scope, dup)); //Insert the resource scope
		else
			delete dup;
	}
	else if (!scopeEl)
		std::cerr << "Error : " << filename << " - scopename " << scopename << " don't exist." << std::endl;
	else if (scopeEl->NoChildren())
		std::cerr << "Error : In " << filename << " scope " << scopename << " has no resources indexed!" << std::endl;
	else
		std::cerr << "Error : " << filename << " - Unknow Error from " << scopename << "." << std::endl;
}

void tr::ResourceManager::ParseXMLTree(tinyxml2::XMLNode * root, std::string path, std::map<std::string, Resource *> * dup)
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
				try
				{
					tr::Resource * t = LoadResource(element, path);	//Load of the Resource	
					dup->insert(std::pair<std::string, tr::Resource *>(key, t));
					this->m_resourceCount++;							
				}
				catch (tr::ResourceNotLoadException & e)
				{
					std::cout << e.what() << std::endl;
				}
			}
		}
		else 											//If not, recursive loading
		{
			std::string newPath = path;
			newPath += childNode->Value();
			newPath += "/";
			ParseXMLTree(childNode, newPath, dup); //Parse the XML Tree while loading resources
		}

		childNode = childNode->NextSibling();
	}
}

tr::Resource * tr::ResourceManager::LoadResource(const tinyxml2::XMLElement * element, const std::string & path)
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
			{
				t->Load();
				if(!t->IsLoaded())
					throw tr::ResourceNotLoadException(file.c_str());
			}
			else
				throw tr::ResourceNotLoadException(file.c_str());
			return t;

		case RESOURCE_TYPE::RESOURCE_SOUNDBUFFER:
			ResourceSoundBuffer * a;
			a = new ResourceSoundBuffer(key, file);
			if(a)
			{
				a->Load();
				if(!a->IsLoaded())
					throw tr::ResourceNotLoadException(file.c_str());
			}
			else
				throw tr::ResourceNotLoadException(file.c_str());
			return a;

		case RESOURCE_TYPE::RESOURCE_MUSIC:
			ResourceMusic * m;
			m = new ResourceMusic(key, file);
			if(m)
			{
				m->Load();
				if(!m->IsLoaded())
					throw tr::ResourceNotLoadException(file.c_str());
			}
			else
				throw tr::ResourceNotLoadException(file.c_str());
			return m;

		case RESOURCE_TYPE::RESOURCE_FONT:
			ResourceFont * f;
			f = new ResourceFont(key, file);
			if(f)
			{
				f->Load();
				if(!f->IsLoaded())
					throw tr::ResourceNotLoadException(file.c_str());
			}
			else
				throw tr::ResourceNotLoadException(file.c_str());
			return f;

		case RESOURCE_TYPE::RESOURCE_TEXT:
			ResourceText * e;
			e = new ResourceText(key, file);
			if(e)
			{
				e->Load();
				if(!e->IsLoaded())
					throw tr::ResourceNotLoadException(file.c_str());
			}
			else
				throw tr::ResourceNotLoadException(file.c_str());
			return e;

		default:
			throw tr::ResourceNotLoadException(file.c_str());
	}
	throw tr::ResourceNotLoadException(file.c_str());
}

void tr::ResourceManager::Clear()
{
	for (std::map<std::string,std::map<std::string, tr::Resource *> * >::iterator it = this->m_resources.begin(); it != this->m_resources.end(); ++it)
		ClearScope(it->first);
	this->m_resources.clear();
	this->m_resourceCount = 0;
}

void tr::ResourceManager::ClearScope(const std::string & scope)
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