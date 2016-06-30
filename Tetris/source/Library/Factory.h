#pragma once
#include <string>
#include "Hashmap.h"

namespace Library
{
	template <class AbstractProductT> class Factory
	{
	//Interface
	public:

		/**
		Default constructor
		*/
		Factory() = default;

		/**
		Virtual destructor
		*/
		virtual ~Factory() = 0;

		/**
		Function returns the name of the class the factory instantiates

		@return a string containing the name of the class instantiated
		*/
		virtual const std::string ClassName() const = 0;

	private:
		/**
		Return the address of a new concrete product associated with this concrete factory class

		@return a newly allocated instance of the concrete product
		*/
		virtual AbstractProductT* Create() = 0;

	//Manager
	public:
		/**
		Given a class name, return the associated concrete factory

		@param className a string containing the name of the class we want to find a factory for
		@return the Factory of the Abstract Product type. Return a null pointer if we don't have such a factory
		*/
		static Factory<AbstractProductT>* Find(const std::string& className);

		/**
		Given a class name, return a new object of that type. 

		@param className a string containing the name of the class we want to create an object of
		@return a new object of the type related to the provided class name
		*/
		static typename AbstractProductT* Create(const std::string& className);

		/**
		Get an iterator for the begin element of the hash map of factories

		@return an iterator for the begin element of the hash map of factories
		*/
		static typename Hashmap<std::string, Factory<AbstractProductT>*>::Iterator begin();

		/**
		Get an iterator for the end element of the hashmap of factories

		@return an iterator for the end element of the hash map of factories
		*/		
		static typename Hashmap<std::string, Factory<AbstractProductT>*>::Iterator end();
		
	protected:
		/**
		Given the address of a concrete factory, add it to the hash map for this abstract factory

		@param toAdd the factory to add to our hash map
		*/
		static void Add(Factory<AbstractProductT>* toAdd);

		/**
		Given the address of a concrete factory, remove it from the hash map of factories

		@param toRemove the factory to remove from our hash map
		*/
		static void Remove(Factory<AbstractProductT>* toRemove);

	//Member data
	private:
		static Hashmap<std::string, Factory<AbstractProductT>*> sFactoryTable;

	};

	//Declaration of our hashmap
	template <class AbstractProductT>
	Hashmap<std::string, Factory<AbstractProductT>*> Factory<AbstractProductT>::sFactoryTable(10);


	/**
	The following macro defines a concrete factory
	*/
#define ConcreteFactory(AbstractProductT, ConcreteProductT)						\
	class ConcreteProductT ## Factory final : public Factory<AbstractProductT>	\
	{																			\
	public:																		\
		ConcreteProductT ## Factory()	{ Add(this); }							\
		~ConcreteProductT ## Factory()	{ Remove(this); }						\
		const std::string ClassName(void) const override						\
		{																		\
			return # ConcreteProductT;											\
		}																		\
		AbstractProductT* Create() override										\
		{																		\
			return new ConcreteProductT();										\
		}																		\
	};

	/**
	The following macro defines a concrete factory in the case where we do not have access to the product to create
	without using the scope resolution operator.
	*/
#define ExternalConcreteFactory(AbstractProductT, ConcreteProductT, Namespace)								\
	class ConcreteProductT ## Factory final : public Factory<AbstractProductT>								\
	{																										\
	public:																									\
		ConcreteProductT ## Factory()	{ Add(this); }														\
		~ConcreteProductT ## Factory()	{ Remove(this); }													\
		const std::string ClassName(void) const override													\
		{																									\
			return # ConcreteProductT;																		\
		}																									\
		AbstractProductT* Create() override																	\
		{																									\
			return new Namespace::ConcreteProductT();														\
		}																									\
	};

}

#include "Factory.inl"