#include "pch.h"
#include "ActionPlayMusic.h"
#include <time.h>
#include <filesystem>

using namespace std;
using namespace std::chrono;
using namespace std::tr2::sys;

namespace Library
{
	RTTI_DEFINITIONS(ActionPlayMusic)

	//Static memeber initialization
	bool ActionPlayMusic::mIsKeepPlaying = true;
	sf::Music* ActionPlayMusic::mMusic = nullptr;
	std::future<void> ActionPlayMusic::mFuture;
	std::mutex ActionPlayMusic::mMutex;


	/**
	*Class constructor that initializes all members
	*/
	ActionPlayMusic::ActionPlayMusic()
	: ActionPlayAudio("")
	{
	}

	/**
	*Class constructor that initializes all members
	*
	*@param initialName = the name of the string action prescribed attribute
	*/
	ActionPlayMusic::ActionPlayMusic(const std::string& initialName)
		: ActionPlayAudio(initialName)
	{
	}

	/**
	*Loads music from file and plays that music
	*
	*@param curState = the state of the world
	*/
	void ActionPlayMusic::Update(const WorldState& curState)
	{
		if (mMusic == nullptr)
		{
			mMusic = new sf::Music();			
		}
		mIsKeepPlaying = true;
		mFuture = async(&ActionPlayMusic::WaitMusicEndAsync, this);
	}

	/**
	*Waits for the currently playing music to be finished, the deallocates the memory allocated by that music
	*/
	void ActionPlayMusic::WaitMusicEndAsync()
	{
		while (mIsKeepPlaying)
		{
			string fileName;
			if (mFileName == "BGM")
			{
				//get the filePath
				fileName = "content/audio/music/";

				//get the name of the backgroundMusic file
				fileName += GetNextBackgroundMusicFile();
			}
			else
			{
				fileName = "content/audio/BGMWin.wav";
				{
					lock_guard<mutex> l(mMutex);
					mIsKeepPlaying = false;
				}
			}

			if (!mMusic->openFromFile(fileName))
			{
				delete mMusic;
				mMusic = nullptr;
				return;
			}

			mMusic->play();

			while (mMusic->getStatus() != sf::Music::Stopped)
			{
				//sf::sleep(sf::milliseconds(100));
				this_thread::sleep_for(seconds(1));
			}
		}
	}

	/**
	*Stops all currently playing sounds and deallocates all memory allocated by this class
	*/
	ActionPlayMusic::~ActionPlayMusic()
	{
		if (mMusic != nullptr)
		{
			{
				lock_guard<mutex> l(mMutex);
				mIsKeepPlaying = false;
			}
			mMusic->stop();
			mFuture.get();
			delete mMusic;
			mMusic = nullptr;
		}
	}

	void ActionPlayMusic::DestroyMusic()
	{
		if (mMusic != nullptr)
		{
			{
				lock_guard<mutex> l(mMutex);
				mIsKeepPlaying = false;
			}
			mMusic->stop();
			mFuture.get();
		}
		mIsKeepPlaying = true;
	}

	/**
	*Gets a random song from our directory to play (Returns the string name pertaining to that file)
	*
	*@param = string corresponding to the name of the next music file to play
	*/
	std::string ActionPlayMusic::GetNextBackgroundMusicFile()
	{
		if (mMusicFiles.empty())
		{
			//populate the music files
			path currentPath = current_path<path>();
			std::string currentPathString = currentPath;
			currentPathString += "\\content\\audio\\music";

			for (directory_iterator it(currentPathString); it != directory_iterator(); ++it)
			{
				if (is_regular_file(it->status()))
				{
					mMusicFiles.push_back(it->path().leaf());
				}
			}
		}

		//Randomly pick a song
		int numFiles = mMusicFiles.size();
		srand((unsigned int)time(nullptr));

		int fileIndex = rand() % (numFiles - 2);
		std::string nextSong = mMusicFiles[fileIndex];

		//move the element that is picked to the end of the vector
		std::swap(mMusicFiles[fileIndex], mMusicFiles[numFiles - 1]);

		return nextSong;
	}
}