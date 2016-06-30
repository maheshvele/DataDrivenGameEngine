#pragma once
#include "ActionPlayAudio.h"
#include <SFML/Audio.hpp>
#include <future>

namespace Library
{
	class ActionPlaySound : public ActionPlayAudio
	{
		RTTI_DECLARATIONS(ActionPlaySound, ActionPlayAudio)
	public:
		
		/**
		*Class constructor that initializes all members
		*/
		ActionPlaySound();

		/**
		*Class constructor that initializes all members
		*
		*@param initialName = the name of the string action prescribed attribute
		*/
		ActionPlaySound(const std::string& initialName);
		
		/**
		*Waits for the currently playing sound to be finished, the deallocates the memory allocated by that sound
		*/
		void WaitSoundEndAsync();

		/**
		*Loads a sound from file and plays that sound
		*
		*@param curState = the state of the world
		*/
		virtual void Update(const WorldState& curState);

		/**
		*Stops all currently playing sounds and deallocates all memory allocated by this class
		*/
		virtual ~ActionPlaySound() override;

		/**
		*Delete copy and assignment
		*/
		ActionPlaySound(const ActionPlaySound& rhs) = delete;
		ActionPlaySound& operator=(const ActionPlaySound& rhs) = delete;

	private:
		sf::SoundBuffer* mBuffer;
		sf::Sound* mSound;
		std::future<void> mFuture;

	};

	ConcreteActionFactory(ActionPlaySound);
}