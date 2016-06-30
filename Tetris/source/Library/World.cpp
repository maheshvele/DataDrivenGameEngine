#include "pch.h"
#include "World.h"
#include "InputManager.h"

namespace Library
{
	RTTI_DEFINITIONS(World)

		//Constructor
		World::World() :
		mClock(), mCurState(), mQueue(nullptr), mInputManager(nullptr), mWindow(nullptr), mElapsedTime(), mActive(false)
	{
		mInputManager = InputManager::Instance();
		mEntityFactory = new EntityFactory();
		mActionListFactory = new ActionListFactory();
		mActionCreateActionFactory = new ActionCreateActionFactory();
		mActionDestroyActionFactory = new ActionDestroyActionFactory();
		mActionExpressionFactory = new ActionExpressionFactory();
		mActionIfFactory = new ActionIfFactory();
		mActionWhileFactory = new ActionWhileFactory();
		mReactionAttributedFactory = new ReactionAttributedFactory();
		mActionEventFactory = new ActionEventFactory();
		mActionCreateEntityFactory = new ActionCreateEntityFactory();
		mActionKeyListenFactory = new ActionKeyListenFactory();
		mActionAdoptFactory = new ActionAdoptFactory();
		mActionPlaySoundFactory = new ActionPlaySoundFactory();
		mActionPlayMusicFactory = new ActionPlayMusicFactory();

		//Attribute that contains the child scope of sectors
		InternalAttribute(Sectors, 1, Datum::TABLE, nullptr)
			Populate();
	}

	//Destructor
	World::~World()
	{
		InputManager::Destroy();
		delete mEntityFactory;
		delete mActionListFactory;
		delete mActionCreateActionFactory;
		delete mActionDestroyActionFactory;
		delete mActionExpressionFactory;
		delete mActionIfFactory;
		delete mActionWhileFactory;
		delete mReactionAttributedFactory;
		delete mActionEventFactory;
		delete mActionCreateEntityFactory;
		delete mActionKeyListenFactory;
		delete mActionAdoptFactory;
		delete mActionPlaySoundFactory;
		delete mActionPlayMusicFactory;
	}

	//Get the sectors child scope
	Scope* World::Sectors() const
	{
		return Find("Sectors")->Get<Scope*>();
	}

	//Set the name
	void World::SetName(const std::string& name)
	{
		mName = name;
	}

	//Get the name
	const std::string& World::Name() const
	{
		return mName;
	}

	//Create a new sector
	Scope* World::CreateSector(const std::string& name) const
	{
		Sector* newSector = new Sector(name);
		newSector->SetWorld(this->As<Scope>());
		return newSector;
	}

	//Update all the sectors
	void World::Update(WorldState& curState)
	{
		//Update the current world state
		SetWorldState(curState);

		mClock.UpdateGameTime(curState.GetGameTime());
		curState.SetWorld(this);

		Scope& curSectors = *Sectors();

		//Update and send out Input events
		mElapsedTime = mClock.GetSFElapsedTime();

		//Polls the InputManager at certain intervals.
		if (mElapsedTime >= .075)
		{
			mInputManager->Update(curState);
			mElapsedTime = 0;
			mClock.ResetSFClock();
		}

		//Updates all sectors in the World.
		for (std::uint32_t i = 0; i < curSectors.Size(); i++)
		{
			Scope* scope = curSectors[i].Get<Scope*>();
			if (scope != nullptr)
			{
				Sector* sector = scope->As<Sector>();
				if (sector != nullptr)
				{
					curState.SetSector(sector);
					sector->Update(curState);
				}
			}
		}

		//Update our EventQueue if we have one
		if (mQueue != nullptr)
		{
			mQueue->Update(curState.GetGameTime());
		}

	}

	//Setter for curState
	void World::SetWorldState(WorldState& state)
	{
		state.SetWorld(this);
		mCurState = state;
	}

	//Getter for curState
	WorldState& World::GetWorldState()
	{
		return mCurState;
	}

	//Getter for queue
	EventQueue* World::GetQueue() const
	{
		return mQueue;
	}

	//Setter for queue
	void World::SetQueue(EventQueue* q)
	{
		mQueue = q;
	}

	//Getter for window
	sf::RenderWindow* World::GetWindow()
	{
		return mWindow;
	}

	//Creates a window in the world (as opposed to setting the render window to one created already
	void World::CreateRenderWindow(const std::uint32_t width, const std::uint32_t height, const std::string& name)
	{
		mWindow = new sf::RenderWindow(sf::VideoMode(width, height), name);
	}

	///(Sets the render window that the world uses.
	void World::SetRenderWindow(sf::RenderWindow& window)
	{
		mWindow = &window;
	}

	/**
	*Checks whether the current world is active
	*
	*@return true if this world is active. False otherwise.
	*/
	bool World::IsActive()
	{
		return mActive;
	}

	/**
	*Sets our active variable
	*
	*@param state =  the state to set our active variable to
	*/
	void World::SetActive(bool state)
	{
		mActive = state;
	}
}