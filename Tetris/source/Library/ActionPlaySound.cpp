#include "pch.h"
#include "ActionPlaySound.h"

using namespace std;
using namespace std::chrono;

namespace Library
{
	RTTI_DEFINITIONS(ActionPlaySound)

	/**
	*Class constructor that initializes all members
	*/
	ActionPlaySound::ActionPlaySound()
		: ActionPlayAudio(""), mBuffer(nullptr), mSound(nullptr), mFuture()
	{
	}

	/**
	*Class constructor that initializes all members
	*
	*@param initialName = the name of the string action prescribed attribute
	*/
	ActionPlaySound::ActionPlaySound(const std::string& initialName)
		: ActionPlayAudio(""), mBuffer(nullptr), mSound(nullptr), mFuture()
	{
	}

	/**
	*Waits for the currently playing sound to be finished, the deallocates the memory allocated by that sound
	*/
	void ActionPlaySound::WaitSoundEndAsync()
	{
		while (mSound->getStatus() != sf::Sound::Stopped)
		{
			this_thread::sleep_for(milliseconds(100));
		}
		delete mSound;
		delete mBuffer;
		mSound = nullptr;
		mBuffer = nullptr;
	}

	/**
	*Loads a sound from file and plays that sound
	*
	*@param curState = the state of the world
	*/
	void ActionPlaySound::Update(const WorldState& curState)
	{
		if (mBuffer == nullptr)
		{
			mBuffer = new sf::SoundBuffer();
			if (!mBuffer->loadFromFile(mFileName))
			{
				delete mBuffer;
				mBuffer = nullptr;
				return;
			}
			if (mSound == nullptr)
			{
				mSound = new sf::Sound();
				mSound->setBuffer(*mBuffer);
				mSound->play();
				mFuture = async(&ActionPlaySound::WaitSoundEndAsync, this);
			}
		}
	}

	/**
	*Stops all currently playing sounds and deallocates all memory allocated by this class
	*/
	ActionPlaySound::~ActionPlaySound()
	{
		if (mSound != nullptr)
		{
			mSound->stop();
			mFuture.get();
		}
	}
}
