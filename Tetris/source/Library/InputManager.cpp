#include "pch.h"
#include "EventMessageAttributed.h"
#include "InputManager.h"
#include "World.h"

namespace Library
{

	//Static member initialization
	InputManager* InputManager::sInstance = nullptr;


	/**
	*Gets the current instance of the InputManager, or creates a new one if it does not exist
	*
	*@return the singleton InputManager instance
	*/
	InputManager* InputManager::Instance()
	{
		if (sInstance == nullptr)
		{
			sInstance = new InputManager;
		}

		return sInstance;
	}

	/**
	*Destroys the singleton instance and deallocates all memory associated with this class
	*/
	void InputManager::Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
			sInstance = nullptr;
		}
	}

	/**
	*Class constructor that initializes all data members
	*/
	InputManager::InputManager() :mKeys(), mKeyConversion(), mPressedLastFrame()
	{
		PopulateKeyConversion();
	}

	/**
	*Adds a key to our vector of keys, which we will continually poll for key events
	*
	*@param key = A string representation of the to add to our vector
	*/
	void InputManager::AddKey(const std::string& key, std::uint32_t playerNumber)
	{
		//Only add the key if it is not already in the list
		for (auto& it : mKeys)
		{
			if (it.first == key)
			{
				return;
			}
		}

		//Only add the key if it is a valid key on the keyboard.
		if (mKeyConversion.Find(key) != mKeyConversion.end())
		{
			mKeys.push_back(std::pair<std::string, std::uint32_t>(key, playerNumber));

		}
	}
	/**
	*Removes a key to our vector of keys
	*
	*@param key = A string representation of the to remove from our vector
	*/
	void InputManager::RemoveKey(const std::string& key, std::uint32_t playerNumber)
	{
		mKeys.remove(std::pair<std::string, std::uint32_t>(key, playerNumber));
	}

	/**
	*Iterates through of list of keys, seeing if any have had their state change. If they have, raise an event of type EventMessageAttributed
	*
	*@param state = the current state of the world. Used to obtain the current game time and enqueue any created events.
	*/
	void InputManager::Update(WorldState& state)
	{
		if (state.GetWorld() == nullptr)
		{
			throw std::exception("The containing world cannot be nullptr.");
		}

		//For every key, if that key is pressed, throw a keyboard event with the relevant information
		for (auto& it : mKeys)
		{
			if (sf::Keyboard::isKeyPressed(mKeyConversion[it.first]))
			{
				//Log the key that was pressed
				mPressedLastFrame[it.first] = true;

				//Create a message, set its subtype, world, and give it an auxillary "Key" attribute containing the key that was pressed (as a string);
				EventMessageAttributed message;
				message.SetWorld(state.GetWorld());
				message.SetSubtype("Keyboard");
				Datum& datum = message.Append("Key");
				datum.SetType(Datum::DatumType::STRING);
				datum.Set(it.first);

				Datum& datum2 = message.Append("Player");
				datum2.SetType(Datum::DatumType::INTEGER);
				datum2.Set((int)it.second);

				//Make an event out of the message and enqueue it in the world's queue
				std::shared_ptr<Event<EventMessageAttributed>> event = std::make_shared<Event<EventMessageAttributed>>(message);
				state.GetWorld()->GetQueue()->Enqueue(event, state.GetGameTime());
			}
			else
			{
				//Send out a key released event
				if (mPressedLastFrame[it.first] == true)
				{
					mPressedLastFrame[it.first] = false;
					EventMessageAttributed message;
					message.SetWorld(state.GetWorld());
					message.SetSubtype("KeyboardRelease");
					Datum& datum = message.Append("Key");
					datum.SetType(Datum::DatumType::STRING);
					datum.Set(it.first);

					Datum& datum2 = message.Append("Player");
					datum2.SetType(Datum::DatumType::INTEGER);
					datum2.Set((int)it.second);

					//Make an event out of the message and enqueue it in the world's queue
					std::shared_ptr<Event<EventMessageAttributed>> event = std::make_shared<Event<EventMessageAttributed>>(message);
					state.GetWorld()->GetQueue()->Enqueue(event, state.GetGameTime());

				}
			}
		}

	}

	/**
	*Populates our key conversion hashmap manually. Called on construction.
	*/
	void InputManager::PopulateKeyConversion()
	{
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("Unknown", sf::Keyboard::Key::Unknown));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("A", sf::Keyboard::Key::A));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("B", sf::Keyboard::Key::B));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("C", sf::Keyboard::Key::C));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("D", sf::Keyboard::Key::D));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("E", sf::Keyboard::Key::E));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("F", sf::Keyboard::Key::F));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("G", sf::Keyboard::Key::G));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("H", sf::Keyboard::Key::H));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("I", sf::Keyboard::Key::I));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("J", sf::Keyboard::Key::J));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("K", sf::Keyboard::Key::K));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("L", sf::Keyboard::Key::L));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("M", sf::Keyboard::Key::M));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("N", sf::Keyboard::Key::N));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("O", sf::Keyboard::Key::O));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("P", sf::Keyboard::Key::P));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("Q", sf::Keyboard::Key::Q));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("R", sf::Keyboard::Key::R));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("S", sf::Keyboard::Key::S));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("T", sf::Keyboard::Key::T));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("U", sf::Keyboard::Key::U));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("V", sf::Keyboard::Key::V));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("W", sf::Keyboard::Key::W));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("x", sf::Keyboard::Key::X));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("Y", sf::Keyboard::Key::Y));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("Z", sf::Keyboard::Key::Z));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("0", sf::Keyboard::Key::Num0));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("1", sf::Keyboard::Key::Num1));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("2", sf::Keyboard::Key::Num2));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("3", sf::Keyboard::Key::Num3));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("4", sf::Keyboard::Key::Num4));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("5", sf::Keyboard::Key::Num5));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("6", sf::Keyboard::Key::Num6));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("7", sf::Keyboard::Key::Num7));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("8", sf::Keyboard::Key::Num8));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("9", sf::Keyboard::Key::Num9));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("Escape", sf::Keyboard::Key::Escape));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("LControl", sf::Keyboard::Key::LControl));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("LShift", sf::Keyboard::Key::LShift));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("LAlt", sf::Keyboard::Key::LAlt));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("LSystem", sf::Keyboard::Key::LSystem));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("RControl", sf::Keyboard::Key::RControl));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("RShift", sf::Keyboard::Key::RShift));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("RAlt", sf::Keyboard::Key::RAlt));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("RSystem", sf::Keyboard::Key::RSystem));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("Menu", sf::Keyboard::Key::Menu));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("[", sf::Keyboard::Key::LBracket));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("]", sf::Keyboard::Key::RBracket));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>(";", sf::Keyboard::Key::SemiColon));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>(",", sf::Keyboard::Key::Comma));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>(".", sf::Keyboard::Key::Period));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("\"", sf::Keyboard::Key::Quote));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("//", sf::Keyboard::Key::Slash));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("\\", sf::Keyboard::Key::BackSlash));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("~", sf::Keyboard::Key::Tilde));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("=", sf::Keyboard::Key::Equal));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("-", sf::Keyboard::Key::Dash));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("Space", sf::Keyboard::Key::Space));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("Return", sf::Keyboard::Key::Return));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("BackSpace", sf::Keyboard::Key::BackSpace));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("Tab", sf::Keyboard::Key::Tab));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("PageUp", sf::Keyboard::Key::PageUp));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("PageDown", sf::Keyboard::Key::PageDown));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("End", sf::Keyboard::Key::End));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("Home", sf::Keyboard::Key::Home));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("Insert", sf::Keyboard::Key::Insert));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("Delete", sf::Keyboard::Key::Delete));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("+", sf::Keyboard::Key::Add));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("-", sf::Keyboard::Key::Subtract));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("*", sf::Keyboard::Key::Multiply));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("//", sf::Keyboard::Key::Divide));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("Left", sf::Keyboard::Key::Left));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("Right", sf::Keyboard::Key::Right));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("Up", sf::Keyboard::Key::Up));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("Down", sf::Keyboard::Key::Down));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("Numpad0", sf::Keyboard::Key::Numpad0));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("Numpad1", sf::Keyboard::Key::Numpad1));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("Numpad2", sf::Keyboard::Key::Numpad2));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("Numpad3", sf::Keyboard::Key::Numpad3));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("Numpad4", sf::Keyboard::Key::Numpad4));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("Numpad5", sf::Keyboard::Key::Numpad5));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("Numpad6", sf::Keyboard::Key::Numpad6));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("Numpad7", sf::Keyboard::Key::Numpad7));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("Numpad8", sf::Keyboard::Key::Numpad8));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("Numpad9", sf::Keyboard::Key::Numpad9));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("F1", sf::Keyboard::Key::F1));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("F2", sf::Keyboard::Key::F2));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("F3", sf::Keyboard::Key::F3));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("F4", sf::Keyboard::Key::F4));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("F5", sf::Keyboard::Key::F5));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("F6", sf::Keyboard::Key::F6));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("F7", sf::Keyboard::Key::F7));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("F8", sf::Keyboard::Key::F8));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("F9", sf::Keyboard::Key::F9));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("F10", sf::Keyboard::Key::F10));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("F11", sf::Keyboard::Key::F11));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("F12", sf::Keyboard::Key::F12));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("F13", sf::Keyboard::Key::F13));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("F14", sf::Keyboard::Key::F14));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("F15", sf::Keyboard::Key::F15));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("Pause", sf::Keyboard::Key::Pause));
		mKeyConversion.Insert(std::pair<std::string, sf::Keyboard::Key>("KeyCount", sf::Keyboard::Key::KeyCount));
	}

}