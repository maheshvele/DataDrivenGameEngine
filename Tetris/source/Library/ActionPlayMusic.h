#pragma once
#include "ActionPlayAudio.h"
#include <SFML/Audio.hpp>
#include <future>
#include <mutex>

namespace Library
{
	class ActionPlayMusic : public ActionPlayAudio
	{
		RTTI_DECLARATIONS(ActionPlayMusic, ActionPlayAudio)

	public:

		/**
		*Class constructor that initializes all members
		*/
		ActionPlayMusic();

		/**
		*Class constructor that initializes all members
		*
		*@param initialName = the name of the string action prescribed attribute
		*/
		ActionPlayMusic(const std::string& initialName);

		/**
		*Waits for the currently playing music to be finished, the deallocates the memory allocated by that music
		*/
		void WaitMusicEndAsync();

		/**
		*Loads music from file and plays that music
		*
		*@param curState = the state of the world
		*/
		virtual void Update(const WorldState& curState);

		/**
		*Stops all currently playing sounds and deallocates all memory allocated by this class
		*/
		virtual ~ActionPlayMusic() override;

		static void DestroyMusic();

		/**
		*Delete copy and assignment
		*/
		ActionPlayMusic(const ActionPlayMusic& rhs) = delete;
		ActionPlayMusic& operator=(const ActionPlayMusic& rhs) = delete;
	
	private:

		/**
		*Gets a random song from our directory to play (Returns the string name pertaining to that file)
		*
		*@param = string corresponding to the name of the next music file to play
		*/
		std::string GetNextBackgroundMusicFile();

	private:
		static bool mIsKeepPlaying;
		static sf::Music* mMusic;
		static std::future<void> mFuture;
		std::vector<std::string> mMusicFiles;
		static std::mutex mMutex;
	};

	ConcreteActionFactory(ActionPlayMusic);
}