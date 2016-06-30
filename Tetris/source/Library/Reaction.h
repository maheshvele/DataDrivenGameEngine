#pragma once
#include "ActionList.h"
#include "EventSubscriber.h"

namespace Library
{
	class Reaction : public ActionList, public EventSubscriber
	{
		RTTI_DECLARATIONS(Reaction, ActionList)
	public:
		/**
		Default constructor
		*/
		Reaction();

		/**
		Constructor with a name

		@param name the name to initialize this reaction with
		*/
		explicit Reaction(const std::string& name);

		/**
		Virtaul destructor
		*/
		virtual ~Reaction();

		/**
		Pure virtual method that acccepts the address of an EventPublisher. Concrete handlers will use the lightweight RTTI interface to verify the actual event type

		@param publisher the address of a publisher
		*/
		virtual void Notify(EventPublisher* publisher) = 0;

		/**
		Does nothing. Used to supress calls to ActionList::Update

		@param curState Unused. Only needed to match the signature that we're overriding
		*/
		void Update(const WorldState& curState) override;

	};
}