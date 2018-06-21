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
	return ((sub == it->second->end()) ? NULL : sub->second);
}

void tr::ResourceManager::LoadFromFileXML(const std::string & filename)
{
	//Opening XML document
	tinyxml2::XMLDocument doc;
	std::string root = "./data/";
	root += filename;
	doc.LoadFile(root.c_str());
	if (doc.Error()) //Error while pre-parsing document
	{	
		std::cerr << doc.ErrorStr() << std::endl;
		return;
	}

	tinyxml2::XMLElement * scopeEl = doc.FirstChildElement("scope"); //Get the first scope name
	if (scopeEl && scopeEl->Attribute("name") != NULL && !scopeEl->NoChildren())		
	{
		std::string scope = scopeEl->Attribute("name");
		LoadFromFileXML(filename, scope);	//Call for the generic function
	}
	else if (!scopeEl)	//Handles errors
		std::cerr << "Error : " << filename << " There is no scope in this file." << std::endl;
	else if (scopeEl->NoChildren() && scopeEl->Attribute("name") != NULL)
		std::cerr << "Error : In " << filename << " scope " << scopeEl->Attribute("name") << " has no resources indexed!" << std::endl;
	else		
		std::cerr << "Error : " << filename << " - Unknow Error." << std::endl;
}

void tr::ResourceManager::LoadFromFileXML(const std::string & filename, const std::string & scopename)
{
	//Opening XML document
	tinyxml2::XMLDocument doc;
	std::string root = "./data/";
	root += filename;
	doc.LoadFile(root.c_str());
	if (doc.Error()) //Error while pre-parsing document
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

	if (scopeEl && !scopeEl->NoChildren()) //If we have a good scope	
	{
		std::string scope = scopeEl->Attribute("name");
		ClearScope(scope); //Remove existing scope if exist
		ParseXMLTree(scopeEl, path); //Parse the XML Tree while creating Resources
		LoadPendingResources(scope);  //Load the pending Resources stored
	}
	else if (!scopeEl)	//Handle errors
		std::cerr << "Error : " << filename << " - scope name " << scopename << " don't exist." << std::endl;
	else if (scopeEl->NoChildren())
		std::cerr << "Error : In " << filename << " scope " << scopename << " has no resources indexed!" << std::endl;
	else
		std::cerr << "Error : " << filename << " - Unknown Error from " << scopename << "." << std::endl;
}

void tr::ResourceManager::ParseXMLTree(tinyxml2::XMLNode * root, std::string path)
{
	tinyxml2::XMLNode * childNode = root->FirstChildElement();
	while (childNode)	//While the root node have childs
	{
		if (strcmp(childNode->Value(), "file") == 0)	//If its a file
		{
			tinyxml2::XMLElement * element = childNode->ToElement();
			if (element && element->Attribute("key") && element->Attribute("type") && element->GetText()) //Has enough attributes
			{									
				std::string key = element->Attribute("key");
				try
				{
					tr::Resource * t = CreateResource(element, path);	//Create of the Resource	
					m_listOfPendingResources.push_back(t);	//Store the Resource for loading
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
			ParseXMLTree(childNode, newPath); //Parse the XML Tree while creating resources
		}
		childNode = childNode->NextSibling();
	}
}

tr::Resource * tr::ResourceManager::CreateResource(const tinyxml2::XMLElement * element, const std::string & path)
{
	std::string key = element->Attribute("key"); //Get all parameters needed
	std::string file = element->GetText();
	file = path  + file;
	RESOURCE_TYPE type = (RESOURCE_TYPE)element->IntAttribute("type");
	Resource * r;

	switch(type) //Create the good type of resource
	{
		case RESOURCE_TYPE::RESOURCE_GRAPHIC: 
			r = new ResourceTexture(key, file);
			break;
		case RESOURCE_TYPE::RESOURCE_SOUNDBUFFER:
			r = new ResourceSoundBuffer(key, file);
			break;
		case RESOURCE_TYPE::RESOURCE_MUSIC:
			r = new ResourceMusic(key, file);
			break;
		case RESOURCE_TYPE::RESOURCE_FONT:
			r = new ResourceFont(key, file);
			break;
		case RESOURCE_TYPE::RESOURCE_TEXT:
			r = new ResourceText(key, file);
			break;
		default:
			throw tr::ResourceNotLoadException(file.c_str());
	}

	if (r)
		return r;
	else
		throw tr::ResourceNotLoadException(file.c_str());
}

bool sortByType(tr::Resource *& r1, tr::Resource *& r2) { return ((int)r1->GetResourceType() < (int)r2->GetResourceType()); } //Function used to sorts Resources by their types

void tr::ResourceManager::LoadPendingResources(std::string & scope)
{ 
	std::sort(m_listOfPendingResources.begin(), m_listOfPendingResources.end(), sortByType); //Sort the resources to load by their types
	std::map<std::string, Resource *> * dup = new std::map<std::string, Resource *>();
	for (unsigned int i = 0; i < m_listOfPendingResources.size(); ++i)	//Load each resources
	{
		try
		{
			Resource * r = m_listOfPendingResources[i];
			if (r)
			{
				r->Load();
				if (!r->IsLoaded())
				{
					delete r;
					throw tr::ResourceNotLoadException(r->GetFilename().c_str());
				}
				dup->insert(std::pair<std::string, tr::Resource *>(r->GetResourceID(), r)); //Insert the resource
				this->m_resourceCount++;
				float progress = (float)(i) / (float)m_listOfPendingResources.size(); //Display progress
			    int barWidth = 40;
			    std::cout << "[";
			    int pos = barWidth * progress;
			    for (int i = 0; i < barWidth; ++i) {
			        if (i < pos) std::cout << "=";
			        else if (i == pos) std::cout << ">";
			        else std::cout << " ";
			    }
			    std::cout << "] " << int(progress * 100.0) << " %\r";
			    std::cout.flush();
			}
		}
		catch (ResourceNotLoadException & e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	m_listOfPendingResources.clear(); //Clear the list of pending resources

	float progress = 1.0; //Display max bar progress
	int barWidth = 40;
	std::cout << "[";
	int pos = barWidth * progress;
	for (int i = 0; i < barWidth; ++i) {
		if (i < pos) std::cout << "=";
		else if (i == pos) std::cout << ">";
		else std::cout << " ";
	}
	std::cout << "] " << int(progress * 100.0) << " %\r";
	std::cout.flush();
	std::cout << std::endl;

	if (dup->size() != 0) // If some resources still have been loaded
		this->m_resources.insert(std::pair<std::string, std::map<std::string, Resource *> * >(scope, dup)); //Insert the resource scope
	else
		delete dup;
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
			delete sub->second;
		this->m_resourceCount--;
	}
	resourcesMap->clear();
	delete resourcesMap;
	this->m_resources.erase(it); //Remove in first map the entry 
}

void tr::ResourceManager::PrintManager()
{
	if (this->m_resources.size() == 0)
		std::cout << "No resources" << std::endl;
	for (std::map<std::string,std::map<std::string, tr::Resource *> * >::iterator it = this->m_resources.begin(); it != this->m_resources.end(); it++)
	{
		std::cout << "Scope : " << it->first << std::endl;
		std::map<std::string, tr::Resource *> * resourcesMap = it->second;
		std::vector<tr::Resource * > listResources;
		for (std::map<std::string, tr::Resource *>::iterator sub = resourcesMap->begin(); sub != resourcesMap->end(); ++sub)
			listResources.push_back(sub->second);
		std::sort(listResources.begin(), listResources.end(), sortByType);
		for (std::vector<tr::Resource *>::iterator sub = listResources.begin(); sub != listResources.end(); sub++)
		{
			Resource * r = *sub;
			std::cout << "\t-- Key : " << r->GetResourceID() << " -- Target : " << r->GetFilename() << " -- Type : ";
			switch (r->GetResourceType())
			{
				case RESOURCE_TYPE::RESOURCE_GRAPHIC:
					std::cout << "GRAPHIC" << std::endl;
					break;
				case RESOURCE_TYPE::RESOURCE_SOUNDBUFFER:
					std::cout << "SOUNDBUFFER" << std::endl;
					break;
				case RESOURCE_TYPE::RESOURCE_MUSIC:
					std::cout << "MUSIC" << std::endl;
					break;
				case RESOURCE_TYPE::RESOURCE_FONT:
					std::cout << "FONT" << std::endl;
					break;
				case RESOURCE_TYPE::RESOURCE_TEXT:
					std::cout << "TEXT" << std::endl;
					break;
				case RESOURCE_TYPE::RESOURCE_MOVIE:
					std::cout << "MOVIE" << std::endl;
					break;
				default:
					std::cout << "NULL" << std::endl;
					break;
			}
		}
	}
}