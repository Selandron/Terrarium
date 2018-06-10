#ifndef SINGLETON_HPP
#define SINGLETON_HPP

/*
	Template Singleton thread-safe based on this tutorial : https://come-david.developpez.com/tutoriels/dps/?page=Singleton

	Author : Etienne Andrieu
*/

#include <SFML/System.hpp>

namespace tr
{

template <typename T> class Singleton
{
	protected:
		// Constructor/Destructor
		Singleton () { }
		~Singleton () { }

	public:
		// Public Inteface
		static T *GetInstance ()
		{
			if (NULL == _singleton)
			{
				sf::Mutex mutex;
				mutex.lock();
				if (NULL == _singleton)
				{
					_singleton = static_cast<T*>(operator new(sizeof(T)));
					new (_singleton) T;
				}
				mutex.unlock();
			}

			return _singleton;
		}

		static void Kill ()
		{
			if (NULL != _singleton)
			{
				delete _singleton;
				_singleton = NULL;
			}
		}

	private:
		// Unique instance
		static T *_singleton;
};

template <typename T> T *Singleton<T>::_singleton = NULL;

}
#endif