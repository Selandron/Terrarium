#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <iostream> 
#include <sstream> 
#include <exception> 

namespace tr
{
  
/*
 *		Exception thrown when a Ressource is not loaded and should have been loaded
 */
class ResourceNotLoadException : public std::exception 
{ 
	public: 
	    ResourceNotLoadException(const char * filename) 
	    { 
	        std::ostringstream oss; 
	        oss << "Ressource " << filename << " not loaded."; 
	        this->msg = oss.str(); 
	    } 
	  
	    virtual ~ResourceNotLoadException() throw() 
	    { 
	  
	    } 
	  
	    virtual const char * what() const throw() 
	    { 
	        return this->msg.c_str(); 
	    } 
	  
	private: 
	    std::string msg; 
};

/*
 *		Exception thrown when a Ressource is not found in the resource map
 */
class ResourceNotFoundException : public std::exception 
{ 
	public: 
	    ResourceNotFoundException(const char * key) 
	    { 
	        std::ostringstream oss; 
	        oss << "Ressource " << key << " not found."; 
	        this->msg = oss.str(); 
	    } 
	  
	    virtual ~ResourceNotFoundException() throw() 
	    { 
	  
	    } 
	  
	    virtual const char * what() const throw() 
	    { 
	        return this->msg.c_str(); 
	    } 
	  
	private: 
	    std::string msg; 
}; 

/*
 *		Exception thrown when a scope is not found in the resource map
 */
class ScopeNotFoundException : public std::exception 
{ 
	public: 
	    ScopeNotFoundException(const char * key) 
	    { 
	        std::ostringstream oss; 
	        oss << "Scope " << key << " not found."; 
	        this->msg = oss.str(); 
	    } 
	  
	    virtual ~ScopeNotFoundException() throw() 
	    { 
	  
	    } 
	  
	    virtual const char * what() const throw() 
	    { 
	        return this->msg.c_str(); 
	    } 
	  
	private: 
	    std::string msg; 
}; 

}
#endif