#pragma once
#include "Attributed.h"
#include <memory>

namespace Library
{
	//Forward declare world
	class World;

	class EventMessageAttributed : public Attributed
	{
	public:
		/**
		Default constructor
		*/
		EventMessageAttributed();

		/**
		Destructor
		*/
		~EventMessageAttributed();

		/**
		Getter for subtype

		@return the string value of our current subtype
		*/
		const std::string& GetSubtype() const;

		/**
		Setter for subtype

		@param type the new type to set us to
		*/
		void SetSubtype(const std::string& type);

		/**
		Getter for world

		@return the address of the current world that we're in
		*/
		World* GetWorld() const;

		/**
		Setter for world

		@param the new world to set us to
		*/
		void SetWorld(World* world);

		/**
		Const get arguments

		@return the address of the arguments perscribed attribute
		*/
		Scope* GetArguments() const;

	private:
		/**
		The current subtype that we're identified as
		*/
		std::string mSubtype;

		/**
		The current world that we're being processed in
		*/
		World* mWorld;
	};
}