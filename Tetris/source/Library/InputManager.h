#pragma once
#include <SFML/Window.hpp>
#include <list>
#include "Hashmap.h"
#include "World.h"

namespace Library
{
	class InputManager final
	{
	public:

		/**
		*Gets the current instance of the InputManager, or creates a new one if it does not exist
		*
		*@return the singleton InputManager instance
		*/
		static InputManager* Instance();

		/**
		*Destroys the singleton instance and deallocates all memory associated with this class
		*/
		static void Destroy();

		/**
		*Adds a key to our vector of keys, which we will continually poll for key events
		*
		*@param key = A string representation of the to add to our vector
		*/
		void AddKey(const std::string& key, std::uint32_t playerNumber);

		/**
		*Removes a key to our vector of keys
		*
		*@param key = A string representation of the to remove from our vector
		*/
		void RemoveKey(const std::string& key, std::uint32_t playerNumber); 

		/**
		*Iterates through of list of keys, seeing if any have had their state change. If they have, raise an event of type EventMessageAttributed
		*
		*@param state = the current state of the world. Used to obtain the current game time and enqueue any created events.
		*/
		void Update(WorldState& state);



	private:

		/**
		*Class constructor that initializes all data members
		*/
		InputManager();

		/**
		*Populates our key conversion hashmap manually. Called on construction.
		*/
		void PopulateKeyConversion();

		//Delete assignment and copy constructor
		InputManager(const InputManager& rhs) = delete;
		InputManager& operator=(const InputManager& rhs) = delete;

	private:
		std::list<std::pair<std::string, std::uint32_t>> mKeys; //Stores all the keys to poll.
		Hashmap<std::string, sf::Keyboard::Key> mKeyConversion; //Hashmap used to translate string keys to their SFML Key counterparts
		Hashmap<std::string, bool> mPressedLastFrame;
		static InputManager* sInstance;
	};
}