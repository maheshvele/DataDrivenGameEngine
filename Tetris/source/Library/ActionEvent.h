#pragma once
#include "Action.h"
#include "EventQueue.h"
#include "EventMessageAttributed.h"

namespace Library
{
	class ActionEvent : public Action
	{
		RTTI_DECLARATIONS(ActionEvent, Action)
	public:
		/**
		Default Constructor
		*/
		ActionEvent();

		/**
		Constructor with a name

		@param name initial name
		*/
		explicit ActionEvent(const std::string& name);

		/**
		Constructor with a name and subtype

		@param name initial name
		@param type subtype
		*/
		ActionEvent(const std::string& name, std::string* type);

		/**
		Constructor with a name and multiple subtypes

		@param name initial name
		@param types array of subtypes
		@param num number of subtypes
		*/
		ActionEvent(const std::string& name, std::string* type, std::uint32_t num);

		/**
		Destructor
		*/
		virtual ~ActionEvent();

		/**
		Creates an event with an attributed message, setting its world and subtype and 
		copying all auxiliary parameters into the message. Finally, it adds the event
		into our event queue with the given delay.

		@param curState the current world state
		*/
		virtual void Update(const WorldState& curState);

		/**
		Check our subtype. Optionally, an index can be provided if we have multiple subtypes

		@param index optional index parameter to use in the case of an array of subtypes
		@return the current string value of the subtype
		*/
		const std::string& GetSubtype(std::uint32_t index = 0) const;

		/**
		Setter for subtype

		@param type the new string to set our subtype to
		@param index the index to set the subtype to
		*/
		void SetSubtype(const std::string& type, std::uint32_t index = 0);

		/**
		Getter for delay

		@return our delay
		*/
		float GetDelay() const;

		/**
		Setter for delay

		@peram delay to set
		*/
		void SetDelay(const float& delay);

		/**
		Getter for current event queue

		@return the current event queue address
		*/
		EventQueue* GetQueue() const;

		/**
		Setter for current event queue

		@param queue the current event queue address
		*/
		void SetQueue(EventQueue* queue);

		/**
		Add a new argument to the arguments list at a given index

		@param arg datum containing the data of the given type
		@param name the name to insert with
		*/
		void AddArgument(const Datum& arg, const std::string& name);

		/**
		Getter for arguments scope

		@return the scope which contains our args
		*/
		Scope* GetArguments();


	private:
		/**
		Pointer to the current queue
		*/
		EventQueue* mCurQueue;
	};
}