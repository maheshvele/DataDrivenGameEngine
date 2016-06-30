#pragma once
#include "Action.h"

namespace Library
{
	class ActionPlayAudio : public Action
	{
		RTTI_DECLARATIONS(ActionPlayAudio, Action)

	public:

		/**
		*Class constructor that initializes all members
		*/
		ActionPlayAudio();

		/**
		*Class constructor that initializes all members
		*
		*@param initialName = the name of the string action prescribed attribute
		*/
		ActionPlayAudio(const std::string& initialName);

		/**
		*Sets the filename to get to audio from
		*
		*@param fileName = the string file path of the music/sound
		*/
		void SetFileName(const std::string& fileName);

		/**
		*Empty implementation of update
		*
		*@param curState = the current state of the world
		*/
		virtual void Update(const WorldState& curState);

		/**
		*Deallocates all memory allocated by this class
		*/
		virtual ~ActionPlayAudio() override = default;

		/**
		*Delete copy and assignment
		*/
		ActionPlayAudio(const ActionPlayAudio& rhs) = delete;
		ActionPlayAudio& operator=(const ActionPlayAudio& rhs) = delete;

	protected:
		std::string mFileName;
		
	};
	
	/**
	*Creates an event of the specified type to enqueue in the world
	*
	*@param name = the subtype of event to create
	*/
	void CreateAudioEvent(const std::string& name, World* world);
	
	ConcreteActionFactory(ActionPlayAudio);
}