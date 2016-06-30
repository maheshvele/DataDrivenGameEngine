#include "pch.h"
#include "Event.h"
#include "EventMessageAttributed.h"
#include "World.h"
#include "ActionPlayAudio.h"

using namespace std;

namespace Library
{
	RTTI_DEFINITIONS(ActionPlayAudio)

	/**
	*Class constructor that initializes all members
	*/
	ActionPlayAudio::ActionPlayAudio()
		: Action(""), mFileName()
	{
		ExternalAttribute(FileName, Datum::STRING, 1, &mFileName)
		Populate();
	}

	/**
	*Class constructor that initializes all members
	*
	*@param initialName = the name of the string action prescribed attribute
	*/
	ActionPlayAudio::ActionPlayAudio(const std::string& initialName)
		: Action(initialName), mFileName()
	{
		ExternalAttribute(FileName, Datum::STRING, 1, &mFileName)
		Populate();
	}

	/**
	*Sets the filename to get to audio from
	*
	*@param fileName = the string file path of the music/sound
	*/
	void ActionPlayAudio::SetFileName(const std::string& fileName)
	{
		mFileName = fileName;
	}

	/**
	*Empty implementation of update
	*
	*@param curState = the current state of the world
	*/
	void ActionPlayAudio::Update(const WorldState& curState)
	{
	}


	/**
	*Creates an event of the specified type to enqueue in the world
	*
	*@param name = the subtype of event to create
	*/
	void CreateAudioEvent(const std::string& name, World* world)
	{
		if (world == nullptr)
		{
			return;
		}

		EventMessageAttributed message;// = new EventMessageAttributed;
		message.SetWorld(world);

		if (name == "Rotate")
		{
			message.SetSubtype("PlayRotate");
		}
		else if (name == "OnStart")
		{
			message.SetSubtype("PlayBGM");
		}
		else if (name == "MenuMenuOptionChange")
		{
			message.SetSubtype("PlayTouch");
		}
		else if (name=="ClearRow")
		{
			message.SetSubtype("PlayClearRow");
		}
		else if (name == "MoveUp")
		{
			message.SetSubtype("PlayMoveUp");
		}
		else if (name == "Touch")
		{
			message.SetSubtype("PlayTouch");
		}
		else if (name == "Win")
		{
			message.SetSubtype("PlayWin");
		}
		else if (name == "Splat")
		{
			message.SetSubtype("PlaySplat");
		}

		//Make an event out of the message and enqueue it in the world's queue
		std::shared_ptr<Event<EventMessageAttributed>> event = std::make_shared<Event<EventMessageAttributed>>(message);
		world->GetQueue()->Enqueue(event, world->GetWorldState().GetGameTime());
	}
}