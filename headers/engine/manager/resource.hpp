#ifndef RESOURCE_HPP
#define RESOURCE_HPP

/*
    Virtual class representing a Resource. Can be any type of resource listed in RESOURCE_TYPE,
    but every type need to be implemented in a child class, and 

    Author : Etienne Andrieu
*/

#include <string>

namespace tr
{

typedef enum
{
    RESOURCE_NULL = 0,
    RESOURCE_GRAPHIC = 1,
    RESOURCE_MOVIE = 2,
    RESOURCE_SOUNDBUFFER = 3,
    RESOURCE_MUSIC = 4,
    RESOURCE_TEXT = 5,
    RESOURCE_FONT = 6,
}RESOURCE_TYPE; //Define every type of resource possible

class Resource
{
    public:
        Resource() : m_resourceID("null"), m_filename("null"), m_type(RESOURCE_NULL), m_loaded(false) {}        //Constructor
        Resource(std::string id, std::string filename) : m_resourceID(id), m_filename(filename), m_type(RESOURCE_NULL), m_loaded(false) {}        //Constructor
        virtual ~Resource() {}                                                                                  //Destructor
        virtual void Load() = 0;                                                                                //Loading function (need to be implemented)
        virtual void Unload() = 0;                                                                              //Unload function (need to be implemented)

        //Accessors and mutators (careful, only changing ID will no unload resource)
        void SetResourceID(std::string ID) { m_resourceID = ID; }
        std::string GetResourceID() const { return m_resourceID; }

        void SetFilename(std::string filename) { m_loaded = false; m_filename = filename; }
        std::string GetFilename() const { return m_filename; }

        void SetResourceType(RESOURCE_TYPE type) { m_loaded = false; m_type = type; }
        RESOURCE_TYPE GetResourceType() const { return m_type; }

        bool IsLoaded() const { return m_loaded; }

    protected:
        std::string m_resourceID;
        std::string m_filename;
        RESOURCE_TYPE m_type;
        bool m_loaded;
    private:
};

}
#endif