#pragma once
#include "Reaction.h"
#include "EventMessageAttributed.h"
#include "Event.h"

namespace Library
{
	class ReactionAttributed : public Reaction
	{
		RTTI_DECLARATIONS(ReactionAttributed, Reaction)
	public:
		/**
		Default constructor
		*/
		ReactionAttributed();

		/**
		Constructor with a name

		@param name the value to initailzie the name attribute with
		*/
		explicit ReactionAttributed(const std::string& name);

		/**
		Constructor with a name and initial subtype value

		@param name the value to initailzie the name attribute with
		@param type the value to initialize the type attribute with
		*/
		ReactionAttributed(const std::string& name, std::string* type);

		/**
		Constructor with a name and multiple subtypes

		@param name the value to initailzie the name attribute with
		@param types an array of values to initailzie the type attribute with
		@param size the number of subtypes that this object will have
		*/
		ReactionAttributed(const std::string& name, std::string** types, std::uint32_t size);

		/**
		Virtual destructor
		*/
		virtual ~ReactionAttributed();

		/**
		Accept only attributed events. If the eveny subtype matches the reaction subtype,
		this copies the arguments attribute into the ReactionAttributed instance

		@param publisher the event publisher who is notifying us
		*/
		virtual void Notify(EventPublisher* publisher);

		/**
		Check our subtype. Optionally, an index can be provided if we have multiple subtypes

		@param index optional index parameter to use in the case of an array of subtypes
		@return the current string value of the subtype
		*/
		const std::string& GetSubtype(std::uint32_t index = 0) const;

		/**
		Add a new subtype to the end of our subtype list

		@param type the new subtype to add
		*/
		void AddSubtype(const std::string& type);

		/**
		Set a subtype at a specific index

		@param type the new subtype to add
		@param index the index at which to insert the new subtype (default to zero)
		*/
		void SetSubtype(const std::string& type, std::uint32_t index = 0);
	};
}