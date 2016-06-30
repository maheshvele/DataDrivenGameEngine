#pragma once
#include "Attributed.h"
#include "Sector.h"
#include "Entity.h"
#include "WorldState.h"
#include "Factory.h"
#include "GameClock.h"
#include "ActionList.h"
#include "ActionCreateAction.h"
#include "ActionDestroyAction.h" 
#include "ActionExpression.h"
#include "ActionIf.h"
#include "ActionWhile.h"
#include "ReactionAttributed.h"
#include "ActionEvent.h"
#include "EventQueue.h"
#include "ActionCreateEntity.h"
#include "ActionKeyListen.h"
#include "ActionAdopt.h"
#include "ActionPlaySound.h"
#include "ActionPlayMusic.h"
#include <SFML/Graphics.hpp>

namespace Library
{
	class InputManager;

	class World final : public Attributed
	{

		RTTI_DECLARATIONS(World, Attributed)

	public:
		/**
		Constructor
		*/
		World();

		/**
		Disallow copies of worlds
		*/
		World(const World& rhs) = delete;

		/**
		Disallow copies of worlds
		*/
		World& operator=(const World& rhs) = delete;

		/**
		Destructor
		*/
		virtual ~World();

		/**
		Returns a string with the name of the world (stored as an external attribute)

		@return the current name of our world
		*/
		const std::string& Name() const;

		/**
		Set the name of the world 

		@param newName the string to set our world's name to
		*/
		void SetName(const std::string& newName);

		/**
		Return a reference to the scope* that contains the sectors

		@return the address of the scope that contains the sectors
		*/
		Scope* Sectors() const;

		/**
		Instantiate a new sector, adopt it into the world (using sector::setWorld) and return the address of the new sector

		@param name A sector cannot exist in our world without a name. This is the name provided for it.
		@return the address of the newly instantiated sector
		*/
		Scope* CreateSector(const std::string& name) const;

		/**
		Iterate through contained sectors and calls their update methods. Pass in a WorldState that's seeded with a GameTime instance

		@param curState the current state
		*/
		void Update(WorldState& curState);

		/**
		Setter for current world state

		@param state the new worldState object to set us to
		*/
		void SetWorldState(WorldState& state);

		/**
		Getter for current world state

		@return the current world state
		*/
		WorldState& GetWorldState();

		/**
		Getter for current event queue
		
		@return the current event queue
		*/
		EventQueue* GetQueue() const;

		/**
		Setter for the current event queue

		@param q the new event queue address
		*/
		void SetQueue(EventQueue* q);

		/*
		Returns a reference to the window
		*/
		sf::RenderWindow* GetWindow();

		void SetRenderWindow(sf::RenderWindow& window);

		/*
		Will configure and initialize the window
		*/
		void CreateRenderWindow(const std::uint32_t width, const std::uint32_t height, const std::string& name);

		/**
		*Checks whether the current world is active
		*
		*@return true if this world is active. False otherwise.
		*/
		bool IsActive();

		/**
		*Sets our active variable
		*
		*@param state =  the state to set our active variable to
		*/
		void SetActive(bool state);



	private:

		/**
		Store the name of the world
		*/
		std::string mName;

		/**
		Entity concrete factory declaration
		*/
		ConcreteFactory(Scope, Entity)
		EntityFactory* mEntityFactory;
		
		/**
		Action factory for action lists
		*/
		ConcreteActionFactory(ActionList)
		ActionListFactory* mActionListFactory;

		/**
		Action factory for creation actions
		*/
		ConcreteActionFactory(ActionCreateAction)
		ActionCreateActionFactory* mActionCreateActionFactory;

		/**
		Action factory for destroy actions
		*/
		ConcreteActionFactory(ActionDestroyAction)
		ActionDestroyActionFactory* mActionDestroyActionFactory;

		/**
		Action factory for expressions
		*/
		ConcreteActionFactory(ActionExpression)
		ActionExpressionFactory* mActionExpressionFactory;
		
		/**
		Action factor for if-statements
		*/
		ConcreteActionFactory(ActionIf)
		ActionIfFactory* mActionIfFactory;

		/**
		Action factor for while-statements
		*/
		ConcreteActionFactory(ActionWhile)
		ActionWhileFactory* mActionWhileFactory;

		/**
		Action factory for ReactionAttributed
		*/
		ConcreteActionFactory(ReactionAttributed)
		ReactionAttributedFactory* mReactionAttributedFactory;

		/**
		Action factory for ActionEvent
		*/
		ConcreteActionFactory(ActionEvent)
		ActionEventFactory* mActionEventFactory;
		
		/**
		Action factory for ActionCreateEntity
		*/
		ConcreteActionFactory(ActionCreateEntity)
		ActionCreateEntityFactory* mActionCreateEntityFactory;

		/**
		Action factory for ActionKeyListen
		*/
		ConcreteActionFactory(ActionKeyListen)
		ActionKeyListenFactory* mActionKeyListenFactory;

		/**
		Action factory for ActionAdopt
		*/
		ConcreteActionFactory(ActionAdopt)
		ActionAdoptFactory* mActionAdoptFactory;

		/**
		Action factory for ActionPlaySound
		*/
		ConcreteActionFactory(ActionPlaySound)
		ActionPlaySoundFactory* mActionPlaySoundFactory;

		/**
		Action factory for ActionPlayAudio
		*/
		ConcreteActionFactory(ActionPlayMusic)
		ActionPlayMusicFactory* mActionPlayMusicFactory;

		/**
		Game clock
		*/
		GameClock mClock;

		/**
		The current state of the world
		*/
		WorldState mCurState;

		/**
		The current event queue
		*/
		EventQueue* mQueue;

		/**
		The singleton instance of the InputManager
		*/
		InputManager* mInputManager;

		/**
		Window that will render everything
		*/
		sf::RenderWindow* mWindow;

		bool mActive;
		float mElapsedTime;
	};
}