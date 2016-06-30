#include "Factory.h"

namespace Library
{

	//Default implementation for virtual destructor
	template <class AbstractProductT>
	Factory<AbstractProductT>::~Factory()
	{
	}

	//Find a factory in the hashmap
	template <class AbstractProductT>
	Factory<AbstractProductT>* Factory<AbstractProductT>::Find(const std::string& className)
	{
		Hashmap<std::string, Factory<AbstractProductT>*>::Iterator i = sFactoryTable.Find(className);
		if (i == sFactoryTable.end())
		{
			return nullptr;
		}
		else
		{
			return (*i).second;
		}
	}

	//Create a concrete product from a factory based on its name
	template <class AbstractProductT>
	typename AbstractProductT* Factory<AbstractProductT>::Create(const std::string& className)
	{
		Hashmap<std::string, Factory<AbstractProductT>*>::Iterator i = sFactoryTable.Find(className);
		if (i == sFactoryTable.end())
		{
			return nullptr;
		}
		else
		{
			return (*i).second->Create();
		}
	}

	//Add a new factory to the factory map
	template <class AbstractProductT>
	void Factory<AbstractProductT>::Add(Factory<AbstractProductT>* toAdd)
	{
		sFactoryTable.Insert(std::pair<std::string, Factory<AbstractProductT>*>(toAdd->ClassName(), toAdd));
	}

	//Remove a factory from the factory map
	template <class AbstractProductT>
	void Factory<AbstractProductT>::Remove(Factory<AbstractProductT>* toRemove)
	{
		sFactoryTable.Remove(toRemove->ClassName());
	}

	//Get the begin element of the factory map
	template <class AbstractProductT>
	typename Hashmap<std::string, Factory<AbstractProductT>*>::Iterator Factory<AbstractProductT>::begin()
	{
		return sFactoryTable.begin();
	}

	//Get the end element of the factory map
	template <class AbstractProductT>
	typename Hashmap<std::string, Factory<AbstractProductT>*>::Iterator Factory<AbstractProductT>::end()
	{
		return sFactoryTable.end();
	}

}